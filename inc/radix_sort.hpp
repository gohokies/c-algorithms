#ifndef _RADIX_SORT_HPP_
#define _RADIX_SORT_HPP_

#pragma once

#include <cstdint>
#include <cstring>
#include <iterator>
#include <algorithm>

#include "insertion_sort.hpp"

namespace algorithms
{

constexpr size_t kRadixBin = 1 << 8;
constexpr const int16_t kMSB16 = 0x8000;
constexpr const int32_t kMSB32 = 0x80000000;
constexpr const int64_t kMSB64 = 0x8000000000000000LL;
constexpr size_t kShifts16[2] = {8, 0};
constexpr size_t kShifts32[4] = {24, 16, 8, 0};
constexpr size_t kShifts64[8] = {56, 48, 40, 32, 24, 16, 8, 0};
constexpr uint8_t kOrderMasks[2] = {static_cast<uint8_t>(0xFF), 0};

///////////////////////////////////////////////////
// General C++ template base
// byte by byte comparison
///////////////////////////////////////////////////
template<typename T, bool ascend>
class RadixTraitsBase
{
public:
    virtual bool isAscending() { return ascend; }
    virtual size_t getDigitCount() { return sizeof(T); }
    virtual size_t getGroupSize() { return 0; }
    virtual uint8_t getDigit(const T &x, size_t k) = 0;
    virtual bool compare(const T &x, const T &y)
    {
        return ascend ? (x < y) : (y < x);
    }
};

template<typename T, bool ascend>
class RadixTraits : public RadixTraitsBase<T, ascend>
{
};

///////////////////////////////////////////////////
// Template class for unsigned integer types
///////////////////////////////////////////////////
template <typename T, bool ascend>
class RadixTraitsUnsignedInteger : public RadixTraitsBase<T, ascend>
{
public:
    virtual uint8_t getDigit(const T &x, size_t k) override
    {
        return static_cast<uint8_t>((x >> ((sizeof(T) - 1 - k) * 8)) & 0xFF) ^ kOrderMasks[ascend];
    }
};

///////////////////////////////////////////////////
// Specialization for unsigned integer types
///////////////////////////////////////////////////

template<> class RadixTraits<uint8_t, true> : public RadixTraitsUnsignedInteger<uint8_t, true> {};
template<> class RadixTraits<uint8_t, false> : public RadixTraitsUnsignedInteger<uint8_t, false> {};

template<> class RadixTraits<uint16_t, true> : public RadixTraitsUnsignedInteger<uint16_t, true>{};
template<> class RadixTraits<uint16_t, false> : public RadixTraitsUnsignedInteger<uint16_t, false>{};

template<> class RadixTraits<uint32_t, true> : public RadixTraitsUnsignedInteger<uint32_t, true>
{
public:
    virtual uint8_t getDigit(const uint32_t &x, size_t k) override
    {
        return static_cast<uint8_t>((x >> kShifts32[k]) & 0xFF);
    }
};

template<> class RadixTraits<uint32_t, false> : public RadixTraitsUnsignedInteger<uint32_t, false>
{
public:
    virtual uint8_t getDigit(const uint32_t &x, size_t k) override
    {
        return static_cast<uint8_t>((x >> kShifts32[k]) & 0xFF) ^ 0xFF;
    }
};

template<> class RadixTraits<uint64_t, true> : public RadixTraitsUnsignedInteger<uint64_t, true>
{
public:
    virtual uint8_t getDigit(const uint64_t &x, size_t k) override
    {
        return static_cast<uint8_t>((x >> kShifts64[k]) & 0xFF);
    }
};

template<> class RadixTraits<uint64_t, false> : public RadixTraitsUnsignedInteger<uint64_t, false>
{
public:
    virtual uint8_t getDigit(const uint64_t &x, size_t k) override
    {
        return static_cast<uint8_t>((x >> kShifts64[k]) & 0xFF) ^ 0xFF;
    }
};

///////////////////////////////////////////////////
// Template class for unsigned integer types
///////////////////////////////////////////////////
template <typename T, bool ascend>
class RadixTraitsSignedInteger : public RadixTraitsBase<T, ascend>
{
protected:
    static constexpr const T kMSB = T(0x80) << ((sizeof(T) - 1) * 8);
public:
    virtual uint8_t getDigit(const T &x, size_t k) override
    {
        return static_cast<uint8_t>(((x ^ kMSB) >> (sizeof(T) - 1 - k) * 8) & 0xFF) ^ kOrderMasks[ascend];
    }
};

/////////////////////////////////////////////////////
// RadixTraits Specialization for signed intger types
/////////////////////////////////////////////////////
template<> class RadixTraits<int8_t, true> : public RadixTraitsSignedInteger<int8_t, true>{};
template<> class RadixTraits<int8_t, false> : public RadixTraitsSignedInteger<int8_t, false>{};

template<> class RadixTraits<int16_t, true> : public RadixTraitsSignedInteger<int16_t, true>{};
template<> class RadixTraits<int16_t, false> : public RadixTraitsSignedInteger<int16_t, false>{};

template<> class RadixTraits<int32_t, true> : public RadixTraitsSignedInteger<int32_t, true>{};
template<> class RadixTraits<int32_t, false> : public RadixTraitsSignedInteger<int32_t, false>{};

template<> class RadixTraits<int64_t, true> : public RadixTraitsSignedInteger<int64_t, true>{};
template<> class RadixTraits<int64_t, false> : public RadixTraitsSignedInteger<int64_t, false>{};

///////////////////////////////////////////////////
// Specialization for floating point types
///////////////////////////////////////////////////
template<typename FT, int ascend, typename UT>
class RadixTraitsFloat : public RadixTraitsBase<FT, ascend>
{
protected:
    static constexpr UT kMSB = UT(0x80) << ((sizeof(UT) - 1) * 8);
public:
    virtual uint8_t getDigit(const FT &x, size_t k) override
    {
        UT u2[2];

        // Branchless digit calculation
        const UT u = *reinterpret_cast<const UT*>(&x);
        u2[0] = u | (kMSB);
        u2[1] = u ^ UT(-1);

        bool isNegative = (u & kMSB) == kMSB;
        return static_cast<uint8_t>(u2[isNegative] >> ((sizeof(UT) - 1 - k) * 8)) & 0xFF ^ kOrderMasks[ascend];
    }
};

template<> class RadixTraits<float, true> : public RadixTraitsFloat<float, true, uint32_t>{};

template<> class RadixTraits<float, false> : public RadixTraitsFloat<float, false, uint32_t>{};

template<> class RadixTraits<double, true> : public RadixTraitsFloat<double, true, uint64_t>{};

template<> class RadixTraits<double, false> : public RadixTraitsFloat<double, false, uint64_t>{};

/////////////////////////////////////////////////////////
// Radix traits template for null-terminated string types
/////////////////////////////////////////////////////////
template<typename StringT, bool ascend, typename CharT>
class RadixTraitsString : public RadixTraitsBase<StringT, ascend>
{
public:
    virtual size_t getDigitCount() override { return 0; }

    virtual size_t getGroupSize() override{ return sizeof(CharT); }

    virtual uint8_t getDigit(const StringT &x, size_t k) override
    {
        CharT ch = x[k / sizeof(CharT)];
        return static_cast<uint8_t>((ch >> (sizeof(CharT) - 1 - (k % sizeof(CharT))) * 8) & 0xFF) ^ kOrderMasks[ascend]; 
    }
};

///////////////////////////////////////////////////
// Specialization for null-terminated string types
/////////////////////////////////////////////////// 
typedef char * STR;
typedef char const * CSTR;

template<>
class RadixTraits<STR, true> : public RadixTraitsString<STR, true, char>
{
public:
    virtual bool compare(const STR &x, const STR &y) override { return strcmp(x, y) < 0; }
};

template<>
class RadixTraits<STR, false> : public RadixTraitsString<STR, false, char>
{
public:
    virtual bool compare(const STR &x, const STR &y) override { return strcmp(y, x) < 0; }
};

template<>
class RadixTraits<CSTR, true> : public RadixTraitsString<CSTR, true, char>
{
public:
    virtual bool compare(const CSTR &x, const CSTR &y) override { return strcmp(x, y) < 0; }
};

template<>
class RadixTraits<CSTR, false> : public RadixTraitsString<CSTR, false, char>
{
public:
    virtual bool compare(const CSTR &x, const CSTR &y) override { return strcmp(y, x) < 0; }
};

typedef wchar_t * WSTR;
typedef wchar_t const * CWSTR;

template<>
class RadixTraits<WSTR, true> : public RadixTraitsString<WSTR, true, wchar_t>
{
public:
    virtual bool compare(const WSTR &x, const WSTR &y) override { return wcscmp(x, y) < 0; }
};

template<>
class RadixTraits<WSTR, false> : public RadixTraitsString<WSTR, false, wchar_t>
{
public:
    virtual bool compare(const WSTR &x, const WSTR &y) override { return wcscmp(y, x) < 0; }
};

template<>
class RadixTraits<CWSTR, true> : public RadixTraitsString<CWSTR, true, wchar_t>
{
public:
    virtual bool compare(const CWSTR &x, const CWSTR &y) override { return wcscmp(x, y) < 0; }
};

template<>
class RadixTraits<CWSTR, false> : public RadixTraitsString<CWSTR, false, wchar_t>
{
public:
    virtual bool compare(const CWSTR &x, const CWSTR &y) override { return wcscmp(y, x) < 0; }
};

///////////////////////////////////////////////////
// Specialization for std::string and std::wstring
///////////////////////////////////////////////////
template<>
class RadixTraits<std::string, true> : public RadixTraitsString<std::string, true, char>{};

template<>
class RadixTraits<std::string, false> : public RadixTraitsString<std::string, false, char>{};

template<>
class RadixTraits<std::wstring, true> : public RadixTraitsString<std::wstring, true, wchar_t>{};

template<>
class RadixTraits<std::wstring, false> : public RadixTraitsString<std::wstring, false, wchar_t>{};

////////////////////////////////////////////
//  Radix sort implementation details
////////////////////////////////////////////
template<typename RandomIt, typename Traits>
void _radix_sort_(RandomIt begin, RandomIt end, Traits traits, size_t kthDigit, bool leftMost)
{
    typedef typename std::iterator_traits<RandomIt>::value_type T;

    auto countOfItems = end - begin;

    // If no need to sort, return.
    if (countOfItems < 2) return;

    // Switch to insertion sort threshold.
    if (countOfItems <= kInsertSortThreshold)
    {
        auto func = [&traits](T const &lhs, T const &rhs){ return traits.compare(lhs, rhs); };
        if (leftMost)
            insertion_sort(begin, end, func);
        else
            insertion_sort_unguarded(begin, end, func);
        return;
    }

    // Count items for each bin.
    size_t count[kRadixBin] = {0};
    for (RandomIt it = begin; it < end; ++it)
    {
        int digit = traits.getDigit(*it, kthDigit);
        ++count[digit];
    }

    // Set store location for each bin. 
    RandomIt pos[kRadixBin + 1];
    pos[0] = begin;
    RandomIt it = begin;
    for (int i = 1; i < kRadixBin; ++i)
    {
        it += count[i - 1];
        pos[i] = it;
    }
    pos[kRadixBin] = end;

    RandomIt e = begin;
    for (int i = 0; i < kRadixBin; ++i)
    {
        e += count[i];
        while (pos[i] != e)
        {
            T tmp = std::move(*pos[i]);
            int bin = traits.getDigit(tmp, kthDigit);
            if (bin != i)
            {
                do
                {
                    std::swap(tmp, *pos[bin]);
                    ++pos[bin];
                }
                while ((bin = traits.getDigit(tmp, kthDigit)) != i);
            }
            *pos[i] = std::move(tmp);
            ++pos[i];
        }
    }

    kthDigit++;
    size_t fixedSize = traits.getDigitCount();
    if (fixedSize == 0)
    {
        size_t s = 0;
        size_t e = kRadixBin;
        RandomIt it = begin;
        
        // Not a fixed size type, T must be a null-terminated type
        if (kthDigit % traits.getGroupSize() == 0)
        {
            s = traits.isAscending() ? 1 : 0;
            e = traits.isAscending() ? kRadixBin : kRadixBin - 1;
            it += (traits.isAscending() ? count[0] : 0);
        }

        for (size_t i = s; i < e; ++i)
        {
            _radix_sort_(it, it + count[i], traits, kthDigit, leftMost);
            it += count[i];
            leftMost = leftMost && (count[i] == 0);
        }
    }
    else
    {
        if (kthDigit < fixedSize)
        {
            RandomIt it = begin;
            for (size_t i = 0; i < kRadixBin; ++i)
            {
                _radix_sort_(it, it + count[i], traits, kthDigit, leftMost);
                it += count[i];
                leftMost = leftMost && (count[i] == 0);
            }
        }
    }
}

template<class RandomIt, class Traits>
void radix_sort(RandomIt begin, RandomIt end, const Traits &traits)
{
    _radix_sort_(begin, end, traits, 0, true);
}

template<class RandomIt>
void radix_sort(RandomIt begin, RandomIt end)
{
    typedef typename std::iterator_traits<RandomIt>::value_type T;

    RadixTraits<T, true> traits;
    _radix_sort_(begin, end, traits, 0, true);
};

} //namespace

#endif