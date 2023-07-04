#include "sortcommon.h"
#include "sortutils.h"

#include "radixsort.h"
#include "insertionsort.h"

static const size_t kRadixBin = 1 << 8;
static const int8_t kMSB8 = 0x80;
static const int16_t kMSB16 = 0x8000;
static const int32_t kMSB32 = 0x80000000;
static const int64_t kMSB64 = 0x8000000000000000LL;
static const size_t kShifts16[2] = {8, 0};
static const size_t kShifts32[4] = {24, 16, 8, 0};
static const size_t kShifts64[8] = {56, 48, 40, 32, 24, 16, 8, 0};
static const uint8_t kOrderMasks[2] = {0xFF, 0};

static inline uint8_t radix_func_uint8(void* elem, size_t kth)
{
    assert(kth == 0);
    return *(uint8_t*)elem;
}

static inline uint8_t radix_func_int8(void* elem, size_t kth)
{
    assert(kth == 0);
    
    int8_t x = *(int8_t*)elem;
    return (uint8_t)(x ^ kMSB8);
}

static inline uint8_t radix_func_uint16(void* elem, size_t kth)
{
    assert(kth < sizeof(uint16_t));
    uint16_t x = *(uint16_t*)elem; 
    return (uint8_t)((x >> kShifts16[kth]) & 0xFF);
}

static inline uint8_t radix_func_int16(void* elem, size_t kth)
{
    assert(kth < sizeof(int16_t));
    int16_t x = *(int16_t*)elem;
    return (uint8_t)(((x ^ kMSB16) >> kShifts16[kth]) & 0xFF);
}

static inline uint8_t radix_func_uint32(void* elem, size_t kth)
{
    assert(kth < sizeof(uint32_t));
    uint32_t x = *(uint32_t*)elem; 
    return (uint8_t)((x >> kShifts32[kth]) & 0xFF);
}

static inline uint8_t radix_func_int32(void* elem, size_t kth)
{
    assert(kth < sizeof(int32_t));
    int32_t x = *(int32_t*)elem;
    return (uint8_t)(((x ^ kMSB32) >> kShifts32[kth]) & 0xFF);
}

static inline uint8_t radix_func_uint64(void* elem, size_t kth)
{
    assert(kth < sizeof(uint64_t));
    uint64_t x = *(uint64_t*)elem; 
    return (uint8_t)((x >> kShifts64[kth]) & 0xFF);
}

static inline uint8_t radix_func_int64(void* elem, size_t kth)
{
    assert(kth < sizeof(int64_t));
    int64_t x = *(int64_t*)elem;
    return (uint8_t)(((x ^ kMSB64) >> kShifts64[kth]) & 0xFF);
}

static inline uint8_t radix_func_float(void* elem, size_t kth)
{
    assert(kth < sizeof(float));
    uint32_t u2[2];

    const uint32_t u= *(uint32_t*)elem;
    u2[0] = u | kMSB32;
    u2[1] = u ^ 0xFFFFFFFF;

    int isNegative = (u & kMSB32) ? 1 : 0;
    return (uint8_t)((u2[isNegative] >> kShifts32[kth]) & 0xFF);
}

static inline uint8_t radix_func_double(void* elem, size_t kth)
{
    assert(kth < sizeof(double));
    uint64_t u2[2];

    const uint64_t u= *(uint64_t*)elem;
    u2[0] = u | kMSB64;
    u2[1] = u ^ 0xFFFFFFFFFFFFFFFFLL;

    int isNegative = (u & kMSB64) ? 1 : 0;
    return (uint8_t)((u2[isNegative] >> kShifts64[kth]) & 0xFF);
}

/*
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
*/

static inline bool compare_uint32(const void* lhs, const void* rhs)
{
    return *((uint32_t*)lhs) < *((uint32_t*)rhs);
}

static inline bool compare_int32(const void* lhs, const void* rhs)
{
    return *((int32_t*)lhs) < *((int32_t*)rhs);
}

static inline bool compare_uint64(const void* lhs, const void* rhs)
{
    return *((uint64_t*)lhs) < *((uint64_t*)rhs);
}

static inline bool compare_int64(const void* lhs, const void* rhs)
{
    return *((int64_t*)lhs) < *((int64_t*)rhs);
}

static inline bool compare_float(const void* lhs, const void* rhs)
{
    return *((float*)lhs) < *((float*)rhs);
}

static inline bool compare_double(const void* lhs, const void* rhs)
{
    return *((double*)lhs) < *((double*)rhs);
}

static CompareFunc get_compare_func(RadixType type)
{
    static CompareFunc funcs[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        compare_uint32,
        compare_int32,
        compare_uint64,
        compare_int64,
        compare_float,
        compare_double,
        NULL,
        NULL
    };

    return funcs[type];
}

static RadixKey get_radix_key(RadixType type)
{
    RadixKey key = { 0, 0, NULL };
    switch(type)
    {
        case t_uint8: key.fixed_key_size = sizeof(uint8_t); key.get_digit = radix_func_uint8; break;
        case t_int8: key.fixed_key_size = sizeof(int8_t); key.get_digit = radix_func_int8; break;
        case t_uint16: key.fixed_key_size = sizeof(uint16_t); key.get_digit = radix_func_uint16; break;
        case t_int16: key.fixed_key_size = sizeof(int16_t); key.get_digit = radix_func_int16; break;
        case t_uint32: key.fixed_key_size = sizeof(uint32_t); key.get_digit = radix_func_uint32; break;
        case t_int32: key.fixed_key_size = sizeof(uint32_t); key.get_digit = radix_func_int32; break;
        case t_uint64: key.fixed_key_size = sizeof(uint64_t); key.get_digit = radix_func_uint64; break;
        case t_int64: key.fixed_key_size = sizeof(int64_t); key.get_digit = radix_func_int64; break;
        case t_float: key.fixed_key_size = sizeof(float); key.get_digit = radix_func_float; break;
        case t_double: key.fixed_key_size = sizeof(double); key.get_digit = radix_func_double; break;
        default: break;
    }

    return key;
}

static int _radix_sort(struct SortContext* context, void* base, size_t nitems, size_t sizeElem, RadixKey* key, size_t kth)
{
    static const size_t kInsertSortThreshold = 16;

    // If no need to sort, return.
    if (nitems < 2) return 0;

    // Switch to insertion sort threshold.
    if (nitems <= kInsertSortThreshold)
    {
        return insertion_sort(base, nitems, sizeElem, context->compare);
    }

    // Count items for each bin.
    size_t count[kRadixBin];
    uint8_t* pEnd = (uint8_t*)base + nitems * sizeElem;

    memset(count, 0, sizeof(count));
    for (uint8_t* pBase = (uint8_t*)base; pBase < pEnd; pBase += sizeElem)
    {
        uint8_t digit = key->get_digit(pBase, kth);
        ++count[digit];
    }

    // Set store location for each bin. 
    uint8_t* pos[kRadixBin + 1];
    pos[0] = (uint8_t*)base;
    uint8_t* it = pos[0];
    for (size_t i = 1; i < kRadixBin; ++i)
    {
        it += count[i - 1] * sizeElem;
        pos[i] = it;
    }
    pos[kRadixBin] = it;

    uint8_t* e = (uint8_t*)base;
    for (int i = 0; i < kRadixBin; ++i)
    {
        e += count[i] * sizeElem;
        while (pos[i] != e)
        {
            memcpy(context->buffer, pos[i], sizeElem);
            int bin = key->get_digit(context->buffer, kth);
            if (bin != i)
            {
                do
                {
                    adv_swap(context->buffer, pos[bin], sizeElem, context->swaptype);
                    pos[bin] += sizeElem;
                }
                while ((bin = key->get_digit(context->buffer, kth)) != i);
            }
            memcpy(pos[i], context->buffer, sizeElem);
            pos[i] += sizeElem;
        }
    }

    kth++;
    size_t fixedSize = key->fixed_key_size;
    if (fixedSize == 0)
    {
        size_t s = 0;
        size_t e = kRadixBin;
        uint8_t* it = (uint8_t*)base;
        
        // Not a fixed size type, T must be a null-terminated type
        if (kth % key->digits_in_group == 0)
        {
            s = 1;
            e = kRadixBin;
            it += count[0] * sizeElem;
//            s = traits.isAscending() ? 1 : 0;
//            e = traits.isAscending() ? kRadixBin : kRadixBin - 1;
//            it += (traits.isAscending() ? count[0] : 0);
        }

        for (size_t i = s; i < e; ++i)
        {
            _radix_sort(context, it, count[i], sizeElem, key, kth);
            it += count[i] * sizeElem;
//            leftMost = leftMost && (count[i] == 0);
        }
    }
    else
    {
        if (kth < fixedSize)
        {
            uint8_t* it = (uint8_t*)base;
            for (size_t i = 0; i < kRadixBin; ++i)
            {
                _radix_sort(context, it, count[i], sizeElem, key, kth);
                it += count[i] * sizeElem;
//                leftMost = leftMost && (count[i] == 0);
            }
        }
    }
}

int radix_sort_type_array(void* base, size_t nitems, size_t sizeElem, RadixType type)
{
    RadixKey key = get_radix_key(type);

    return radix_sort(base, nitems, sizeElem, &key, get_compare_func(type));
}

int radix_sort(void *base, size_t nitems, size_t sizeElem, RadixKey* key, CompareFunc compare)
{
    int res = 0;
    uint8_t buffer[256];

    struct SortContext context;
    size_t vbase = (size_t)base;

    // If no need to sort, early return.
    if (nitems < 2) return 0;

    context.compare = compare;
    context.swaptype = (vbase % sizeof(size_t) == 0 && sizeElem % sizeof(size_t) == 0) ? Align : Raw;
    context.buffer = buffer;
    if (sizeElem > sizeof(buffer))
    {
        context.buffer = malloc(sizeElem);
        if (context.buffer == NULL) return -1;
    }

    res = _radix_sort(&context, base, nitems, sizeElem, key, 0);

    if (context.buffer != buffer) free(context.buffer);

    return res;
}