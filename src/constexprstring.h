/* Copyright (C) 2021 Jan Lanik - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the Apache license version 2.0.
 *
 * See http://www.apache.org/licenses/
 */

#include <cstddef>
#include <cstdint>

///
/// Contains constexpr implementation of functions from <cstring>
///
/// The following functions are a ommited
/// (1) Functions that modify it's arguments.
/// (2) Functions that have a side effect ()
/// (3) Functions that use locale (strcoll)
///

namespace constexprstring {

namespace detail {
constexpr int strcmp_impl(const char *lhs, const char *rhs,
                          std::size_t const count = -1) {
    constexpr int LEFT_LOWER{-1};
    constexpr int LEFT_GREATER{1};
    constexpr int BOTH_EQUAL{0};

    for (size_t i{}; i <= count; ++i) {
        if ('\0' == *lhs) {
            if ('\0' == *rhs) {
                // both empty
                return BOTH_EQUAL;
            } else {
                // lhs is a prefix of rhs
                return LEFT_LOWER;
            }
        } else {
            if ('\0' == *rhs) {
                // rhs is a prefix of lhs
                return LEFT_GREATER;
            } else {
                int const diff =
                    (static_cast<int>(static_cast<unsigned char>(*lhs)) -
                     static_cast<int>(static_cast<unsigned char>(*rhs)));
                if (diff > 0) {
                    return LEFT_GREATER;
                } else if (diff < 0) {
                    return LEFT_LOWER;
                } else {
                    // Equal until now - need to look at the next symbol.
                    ++lhs;
                    ++rhs;
                    continue;
                }
            }
        }
    }
    return BOTH_EQUAL;
}

class CharSet {
  public:
    constexpr CharSet() = default;
    constexpr CharSet(char const *str) {
        for (char const *it = str; *it != '\0'; ++it) {
            set(*it);
        }
    }
    constexpr void set(char symbol) {
        auto const val = static_cast<unsigned char>(symbol);
        size_t const word_idx = val / 64;
        std::uint64_t const mask = std::uint64_t{1} << (val % 64);
        charset_[word_idx] |= mask;
    }
    constexpr bool isSet(char symbol) const {
        auto const val = static_cast<unsigned char>(symbol);
        size_t const word_idx = val / 64;
        std::uint64_t const mask = std::uint64_t{1} << (val % 64);
        return charset_[word_idx] & mask;
    }

  private:
    std::uint64_t charset_[4]{};
};
} // namespace detail

constexpr std::size_t strlen(const char *str) {
    std::size_t cnt{};
    for (char const *it = str; *it != '\0'; ++it) {
        ++cnt;
    }
    return cnt;
}

///
/// @return -1 if lhs is lexicographically lower than rhs,
///   0 if lhs and rhs are the same and 1 if lhs is greater than rhs.
///
/// This definition is a bit narower than in std::strcmp(), where other positive
/// and negative values are also allowed.
constexpr int strcmp(const char *lhs, const char *rhs) {
    return detail::strcmp_impl(lhs, rhs);
}

constexpr int strncmp(const char *lhs, const char *rhs, std::size_t count) {
    return detail::strcmp_impl(lhs, rhs, count);
}

constexpr const char *strchr(const char *str, int ch) {
    for (; *str != '\0'; ++str) {
        if (ch == static_cast<int>(*str)) {
            return str;
        }
    }
    if (ch == '\0') {
        return str;
    }
    return nullptr;
}

constexpr const char *strrchr(const char *str, int ch) {
    char const *last_position{nullptr};
    for (; *str != '\0'; ++str) {
        if (ch == static_cast<int>(*str)) {
            last_position = str;
        }
    }
    if (ch == '\0') {
        return str;
    }
    return last_position;
}

constexpr size_t strspn(const char *dest, const char *src) {
    detail::CharSet charset{src};
    size_t cnt{};
    for (char const *it = dest; *it != '\0'; ++it) {
        if (!charset.isSet(*it)) {
            break;
        }
        ++cnt;
    }
    return cnt;
}

constexpr size_t strcspn(const char *dest, const char *src) {
    detail::CharSet charset{src};
    size_t cnt{};
    for (char const *it = dest; *it != '\0'; ++it) {
        if (charset.isSet(*it)) {
            break;
        }
        ++cnt;
    }
    return cnt;
}

} // namespace constexprstring
