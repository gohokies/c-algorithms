param(
    [String]$Arch="",
    [String]$Platform="",
    [String][ValidateSet("", "Debug", "Release")]$Config="",
    [String]$Generator=""
    )

. $PSScriptRoot/utilities.ps1 
. $PSScriptRoot/Builder.ps1

# Setting up build parameters

$TargetPlatform = $Platform.ToString().ToLower()
if ($TargetPlatform -eq ""){ $TargetPlatform = GetHostOS }

$TargetArch = $Arch.ToString().ToLower()
if ($TargetArch -eq ""){ $TargetArch = GetHostArch }

if($TargetPlatform -eq "linux"){
    $builder = [LinuxBuilder]::new($TargetArch, $Config, $Generator)   
}
elseif($TargetPlatform -eq "osx"){
    $builder = [MacOSBuilder]::new($TargetArch, $Config, $Generator)   
}
elseif($TargetPlatform -eq "windows"){
    $builder = [WindowsBuilder]::new($TargetArch, $Config, $Generator)   
}

$builder.PrepareBuildSetings()

$builder.SetupBuild()
$builder.Build()
