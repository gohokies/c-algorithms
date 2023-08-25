. $PSScriptRoot/utilities.ps1

class Builder
{
    [String]$TargetPlatform
    [String]$TargetArch
    [String]$TargetConfig
    [String]$TargetGenerator

    [String]$TargetTriplet
    [String]$RootDir
    [String]$BuildDir
    [String[]]$BuildParams

    [Boolean]$MultiConfig
    [Switch]$BuildPython = $False
    [Switch]$BuildDotnet = $False
    [Switch]$BuildJava = $False
    
    # Constructor
    Builder([String]$Platform, [String]$Arch, [String]$Config, [string]$Generator)
    {
        $this.TargetPlatform = $Platform.ToString().ToLower()
        $this.TargetArch = $Arch.ToString().ToLower()
        $this.TargetConfig = $Config
        $this.TargetGenerator = $Generator

        $this.MultiConfig = $False
        $this.RootDir = Resolve-Path "$PSScriptRoot/.."
        if ($this.TargetArch -eq ""){ $this.TargetArch = GetHostArch }
    }

    [void] PrepareBuildSetings()
    {
        $Arch = $this.TargetArch
        $Platform = $this.TargetPlatform
        $Triplet = "$Arch-$Platform"
        $this.TargetTriplet = $Triplet

        $Config = $this.TargetConfig
        $Root = $this.RootDir
        $this.BuildDir = "$Root/build/$Triplet"
    
        $this.BuildParams = @("-S", $this.RootDir, "-B", $this.BuildDir)

        $vcpkgToolChainFile = "$Root/vcpkg/scripts/buildsystems/vcpkg.cmake"
        $this.BuildParams += @("-DCMAKE_TOOLCHAIN_FILE=$vcpkgToolChainFile")
    }

    [void] SetupBuild()
    {  
        # Start building section
        Write-Host "Setting up dependencies for $($this.TargetTriplet)"
        $vcpkgScript = Join-Path $this.RootDir "scripts/vcpkg.ps1"
        . $vcpkgScript -TargetTriplet $this.TargetTriplet

        $Triplet = $this.TargetTriplet
        Write-Host "Setting up build for $Triplet ..."
        Write-Host "cmake $($this.BuildParams)"
        & cmake $this.BuildParams | Write-Host
    }

    [void] Build()
    {  
        # Start building section
        if ($this.MultiConfig){
            $Config = $this.TargetConfig
            if ($Config -eq "") { $Config = "Debug" }
            Write-Host "MultiConfig: cmake --build $($this.BuildDir) --config $Config"
            & cmake --build $this.BuildDir --config $Config | Write-Host
        }
        else{
            Write-Host "SingleConfig: cmake --build $($this.BuildDir)"
            & cmake --build $this.BuildDir | Write-Host
        }
    }
}

class LinuxBuilder : Builder
{   
    # Constructor
    LinuxBuilder([String]$Arch, [String]$Config, [String]$Generator) : base("linux", $Arch, $Config, $Generator)
    {
        if (-Not ($Arch -eq "" -Or $Arch -ieq "x64" -Or $Arch -ieq "arm64" -Or $Arch -ieq "arm")){
            throw "Invalid target architecture"
        }

        if (-Not ($Generator -eq "" -Or $Generator -eq "Unix Makefiles" -Or $Generator -eq "Ninja" -Or $Generator -eq "Ninja Multi-Config")){
            throw "invalid generator"
        }
    }

    [void] PrepareBuildSetings()
    {
        ([Builder]$this).PrepareBuildSetings()
    
        $Triplet = $this.TargetTriplet    
        $this.BuildParams +=@("-DVCPKG_TARGET_TRIPLET=$Triplet")            

        $Dir = $this.RootDir
        $Arch = $this.TargetArch
        $this.BuildParams +=@("-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=$Dir/cmake/toolchains/$Arch-linux-gnu.cmake")            

        $Generator = $this.TargetGenerator
        if ($Generator -eq ""){ $Generator = "Ninja Multi-Config" }
        $this.BuildParams += @("-G", $Generator)

        if ($Generator -eq "Ninja Multi-Config")
        {
            $this.MultiConfig = $True
        }

        $Config = $this.TargetConfig
        if (-Not $Config -eq ""){ $this.BuildParams += @("-DCMAKE_BUILD_TYPE=$Config") }
    }
}

class MacOSBuilder : Builder
{   
    # Constructor
    MacOSBuilder([String]$Arch, [String]$Config, [String]$Generator) : base("osx", $Arch, $Config, $Generator)
    {
        if (-Not ($Arch -eq "" -Or $Arch -ieq "x64" -Or $this.TargetArch -ieq "arm64")){
            throw "Invalid target architecture"
        }

        if (-Not ($Generator -eq "" -Or $Generator -eq "Xcode" -Or $Generator -eq "Ninja")){
            throw "invalid generator"
        }
    }

    [void] PrepareBuildSetings()
    {
        ([Builder]$this).PrepareBuildSetings()

        if ($this.TargetArch -ieq "x64"){ $this.BuildParams += @("-DCMAKE_OSX_ARCHITECTURES=x86_64") }
        if ($this.TargetArch -ieq "arm64"){ $this.BuildParams += @("-DCMAKE_OSX_ARCHITECTURES=arm64") }
        
        $Triplet = $this.TargetTriplet
        $this.BuildParams += @("-DVCPKG_TARGET_TRIPLET=$Triplet")

        $Generator = $this.TargetGenerator
        if ($Generator -eq ""){ $Generator = "Xcode" }
        $this.BuildParams += @("-G", $Generator)

        $Config = $this.TargetConfig
        
        if ($Generator -eq "Xcode"){
            $this.MultiConfig = $True
            if (-Not $Config -eq ""){ $this.BuildParams += @("-DCMAKE_CONFIGURATION_TYPES=$Config") }   
        }
        else{
            if (-Not $Config -eq ""){ $this.BuildParams += @("-DCMAKE_BUILD_TYPE=$Config") }    
        }
    }
}

class WindowsBuilder : Builder
{
    # Constructor
    WindowsBuilder([String]$Arch, [String]$Config, [String]$Generator) : base("windows", $Arch, $Config, $Generator)
    {
        # Use default Visual Studio generator 
        $Generators = @("Visual Studio 16 2019", "Visual Studio 17 2022")
        $Archs = @("x64", "x86", "arm64")

        if (-Not ($Arch -eq "" -Or $Arch -in $Archs)){
            throw "Invalid target architecture"
        }

        if (-Not ($Generator -eq "" -Or $Generator -in $Generators)){
            throw "Invalid Generator"
        }
    }

    [void] PrepareBuildSetings()
    {
        ([Builder]$this).PrepareBuildSetings()
        
        $this.MultiConfig = $True

        $Generator = $this.TargetGenerator
        if (-Not $Generator -eq "") { $this.BuildParams += @("-G", $Generator) }

        $this.BuildParams += @("-DCMAKE_CONFIGURATION_TYPES=Debug;Release;RelWithDebInfo;MinSizeRel")

        $Arch = $this.TargetArch
        if ($Arch -ieq "x86"){ $Arch = "Win32" }
        $this.BuildParams += @("-A", $Arch)
    }
}