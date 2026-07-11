#pragma once

#include <cstddef>
#include <cstdint>

class FNV1A
{
public:
    [[nodiscard]]
    static constexpr std::uint32_t Hash(const char* str) noexcept
    {
        std::uint32_t hash = OffsetBasis;

        while (*str)
        {
            hash ^= static_cast<std::uint8_t>(*str++);
            hash *= Prime;
        }

        return hash;
    }

    [[nodiscard]]
    static consteval std::uint32_t HashConst(const char* str) noexcept
    {
        return Hash(str);
    }

    [[nodiscard]]
    static constexpr std::uint32_t HashLen(const char* str, std::size_t len) noexcept
    {
        std::uint32_t hash = OffsetBasis;

        for (std::size_t i = 0; i < len; ++i)
        {
            hash ^= static_cast<std::uint8_t>(str[i]);
            hash *= Prime;
        }

        return hash;
    }

private:
    static inline constexpr std::uint32_t Prime = 0x01000193u;
    static inline constexpr std::uint32_t OffsetBasis = 0x811C9DC5u;
};