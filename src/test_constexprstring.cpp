/* Copyright (C) 2021 Jan Lanik - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the Apache license version 2.0.
 *
 * See http://www.apache.org/licenses/
 */

#include "constexprstring.h"

#include <gtest/gtest.h>

#include <cstring>
#include <random>

namespace cxs = constexprstring;

namespace {
int sign(int val) {
    if (val > 0) {
        return 1;
    } else if (val < 0) {
        return -1;
    } else {
        return 0;
    }
}

unsigned char random_symbol() {
    static std::default_random_engine gen;
    static std::uniform_int_distribution<unsigned char> distr;
    return distr(gen);
}

} // namespace

// c++14 compatibility
TEST(CPP14Compatibility, Check) { EXPECT_LE(201402L, __cplusplus); }

// strlen
TEST(StrlenTest, Empty) {
    constexpr const char *str = "";
    static_assert(cxs::strlen(str) == 0ULL, "Test Failure");
    EXPECT_EQ(0ULL, cxs::strlen(str));
    EXPECT_EQ(std::strlen(str), cxs::strlen(str));
}
TEST(StrlenTest, NonEmpty) {
    constexpr const char *str = "HelloWorld!";
    static_assert(cxs::strlen(str) == 11ULL, "Test Failure");
    EXPECT_EQ(11ULL, cxs::strlen(str));
    EXPECT_EQ(std::strlen(str), cxs::strlen(str));
}

// strcmp
TEST(StrCmpTest, Empty) {
    constexpr const char *str_empty1 = "";
    constexpr const char *str_empty2 = "";
    constexpr const char *str_nonempty = "HelloWorld!";
    static_assert(cxs::strcmp(str_empty1, str_empty2) == 0, "Test Failure");
    EXPECT_EQ(0, cxs::strcmp(str_empty1, str_empty2));
    EXPECT_EQ(sign(std::strcmp(str_empty1, str_empty2)),
              cxs::strcmp(str_empty1, str_empty2));

    static_assert(-1 == cxs::strcmp(str_empty1, str_nonempty), "Test Failure");
    EXPECT_EQ(-1, cxs::strcmp(str_empty1, str_nonempty));
    EXPECT_EQ(sign(std::strcmp(str_empty1, str_nonempty)),
              cxs::strcmp(str_empty1, str_nonempty));

    static_assert(1 == cxs::strcmp(str_nonempty, str_empty1), "Test Failure");
    EXPECT_EQ(1, cxs::strcmp(str_nonempty, str_empty1));
    EXPECT_EQ(sign(std::strcmp(str_nonempty, str_empty1)),
              cxs::strcmp(str_nonempty, str_empty1));
}

TEST(StrCmpTest, OneCharSame) {
    constexpr const char *str1 = "H";
    constexpr const char *str2 = "H";
    static_assert(0 == cxs::strcmp(str1, str2), "Test Failure");
    EXPECT_EQ(0, cxs::strcmp(str1, str2));
    EXPECT_EQ(sign(std::strcmp(str1, str2)), cxs::strcmp(str1, str2));
}
TEST(StrCmpTest, OneCharDifferent) {
    constexpr const char *str1 = "H";
    constexpr const char *str2 = "X";
    static_assert(-1 == cxs::strcmp(str1, str2), "Test Failure");
    EXPECT_EQ(-1, cxs::strcmp(str1, str2));
    static_assert(1 == cxs::strcmp(str2, str1), "Test Failure");
    EXPECT_EQ(1, cxs::strcmp(str2, str1));
}

TEST(StrCmpTest, Same) {
    constexpr const char *str1 = "Hi There!";
    constexpr const char *str2 = "Hi There!";
    static_assert(0 == cxs::strcmp(str1, str2), "Test Failute");
    EXPECT_EQ(0, cxs::strcmp(str1, str2));
    EXPECT_EQ(sign(std::strcmp(str1, str2)), cxs::strcmp(str1, str2));
}

TEST(StrCmpTest, Prefix) {
    constexpr const char *str1 = "Hi";
    constexpr const char *str2 = "Hi There!";
    static_assert(-1 == cxs::strcmp(str1, str2), "Test Failute");
    EXPECT_EQ(-1, cxs::strcmp(str1, str2));
    EXPECT_EQ(sign(std::strcmp(str1, str2)), cxs::strcmp(str1, str2));
    static_assert(1 == cxs::strcmp(str2, str1), "Test Failute");
    EXPECT_EQ(1, cxs::strcmp(str2, str1));
    EXPECT_EQ(sign(std::strcmp(str2, str1)), cxs::strcmp(str2, str1));
}

TEST(StrCmpTest, DifferentFirstChar) {
    constexpr const char *str1 = "Atralala";
    constexpr const char *str2 = "Ftralala";
    static_assert(-1 == cxs::strcmp(str1, str2), "Test Failute");
    EXPECT_EQ(-1, cxs::strcmp(str1, str2));
    EXPECT_EQ(sign(std::strcmp(str1, str2)), cxs::strcmp(str1, str2));
    static_assert(1 == cxs::strcmp(str2, str1), "Test Failute");
    EXPECT_EQ(1, cxs::strcmp(str2, str1));
    EXPECT_EQ(sign(std::strcmp(str2, str1)), cxs::strcmp(str2, str1));
}

TEST(StrCmpTest, DifferentLaterChar) {
    constexpr const char *str1 = "tralaAla";
    constexpr const char *str2 = "tralaUla";
    static_assert(-1 == cxs::strcmp(str1, str2), "Test Failute");
    EXPECT_EQ(-1, cxs::strcmp(str1, str2));
    EXPECT_EQ(std::strcmp(str1, str2), cxs::strcmp(str1, str2));
    static_assert(1 == cxs::strcmp(str2, str1), "Test Failute");
    EXPECT_EQ(1, cxs::strcmp(str2, str1));
    EXPECT_EQ(sign(std::strcmp(str2, str1)), cxs::strcmp(str2, str1));
}

// strncmp
TEST(StrnCmpTest, Offsets) {
    constexpr const char *str1 = "tralaAla";
    constexpr const char *str2 = "tralaXla";
    static_assert(0 == cxs::strncmp(str1, str2, 0), "Test Failure");
    static_assert(0 == cxs::strncmp(str1, str2, 1), "Test Failure");
    static_assert(0 == cxs::strncmp(str1, str2, 4), "Test Failure");
    static_assert(-1 == cxs::strncmp(str1, str2, 6), "Test Failure");
    static_assert(-1 == cxs::strncmp(str1, str2, 7), "Test Failure");
    EXPECT_EQ(sign(std::strncmp(str1, str2, 0)), cxs::strncmp(str1, str2, 0));
    EXPECT_EQ(sign(std::strncmp(str1, str2, 1)), cxs::strncmp(str1, str2, 1));
    EXPECT_EQ(sign(std::strncmp(str1, str2, 4)), cxs::strncmp(str1, str2, 4));
    EXPECT_EQ(sign(std::strncmp(str1, str2, 6)), cxs::strncmp(str1, str2, 6));
    EXPECT_EQ(sign(std::strncmp(str1, str2, 7)), cxs::strncmp(str1, str2, 7));
}
TEST(StrnCmpTest, Regression1) {
    constexpr const char *str1 = "ababauit";
    constexpr const char *str2 = "aba";
    EXPECT_EQ(cxs::strncmp(str1, str2, 3), 0);
}

// strchr
TEST(StrChrTest, Empty) {
    constexpr char const *str = "";
    static_assert(nullptr == cxs::strchr(str, 'A'));
    EXPECT_EQ(nullptr, cxs::strchr(str, '?'));
}
TEST(StrChrTest, NonEmpty) {
    constexpr char const *str = "Tralala";
    static_assert(str + 3 == cxs::strchr(str, 'l'));
    EXPECT_EQ(std::strchr(str, 'l'), cxs::strchr(str, 'l'));
}
TEST(StrChrTest, NullCanBeFound) {
    constexpr char const *str = "Tralala";
    static_assert(str + 7 == cxs::strchr(str, '\0'));
    EXPECT_EQ(std::strchr(str, '\0'), cxs::strchr(str, '\0'));
}
TEST(StrChrTest, AllCharactersCanBeFound) {
    char allchars[256];
    for (size_t i{}; i <= 255; ++i) {
        allchars[i] = static_cast<char>(i + 1);
    }
    EXPECT_EQ(255, std::strlen(allchars));
    for (size_t i{}; i < 255; ++i) {
        char const symbol = allchars[i];
        EXPECT_EQ(allchars + i, cxs::strchr(allchars, symbol));
        EXPECT_EQ(std::strchr(allchars, symbol), cxs::strchr(allchars, symbol));
    }
}

// strrchr
TEST(StrRchrTest, Empty) {
    constexpr char const *str = "";
    static_assert(nullptr == cxs::strrchr(str, 'A'));
    EXPECT_EQ(nullptr, cxs::strrchr(str, '?'));
}
TEST(StrRchrTest, NonEmpty) {
    constexpr char const *str = "Tralala";
    static_assert(str + 5 == cxs::strrchr(str, 'l'));
    EXPECT_EQ(std::strrchr(str, 'l'), cxs::strrchr(str, 'l'));
}
TEST(StrRchrTest, NullCanBeFound) {
    constexpr char const *str = "Tralala";
    static_assert(str + 7 == cxs::strrchr(str, '\0'));
    EXPECT_EQ(std::strrchr(str, '\0'), cxs::strrchr(str, '\0'));
}
TEST(StrRchrTest, AllCharactersCanBeFound) {
    char allchars[511];
    for (size_t i{}; i < 255; ++i) {
        allchars[i] = static_cast<char>(i + 1);
        allchars[255 + i] = static_cast<char>(i + 1);
    }
    allchars[510] = '\0';
    EXPECT_EQ(510, std::strlen(allchars));
    for (size_t i{}; i < 255; ++i) {
        char const symbol = allchars[i];
        EXPECT_EQ(allchars + 255 + i, cxs::strrchr(allchars, symbol));
        EXPECT_EQ(std::strrchr(allchars, symbol),
                  cxs::strrchr(allchars, symbol));
    }
}

// strspn
TEST(StrSpnTest, EmptySrc) {
    constexpr char const *dst = "foobar";
    constexpr char const *src = "";
    static_assert(0 == cxs::strspn(dst, src), "Test Failure");
    EXPECT_EQ(std::strspn(dst, src), cxs::strspn(dst, src));
}

TEST(StrSpnTest, AllIn) {
    constexpr char const *dst = "foobar";
    constexpr char const *src = "foobar";
    static_assert(6 == cxs::strspn(dst, src), "Test Failure");
    EXPECT_EQ(std::strspn(dst, src), cxs::strspn(dst, src));
}

TEST(StrSpnTest, CppReferenceTestCase) {
    constexpr char const *low_alpha = "qwertyuiopasdfghjklzxcvbnm";
    constexpr char const *dst = "abcde312$#@";
    static_assert(5 == cxs::strspn(dst, low_alpha), "Test Failure");
    EXPECT_EQ(std::strspn(dst, low_alpha), cxs::strspn(dst, low_alpha));
}

// strcspn

TEST(StrCSpnTest, EmptySrc) {
    constexpr char const *dst = "foobar";
    constexpr char const *src = "";
    static_assert(6 == cxs::strcspn(dst, src), "Test Failure");
    EXPECT_EQ(std::strcspn(dst, src), cxs::strcspn(dst, src));
}

TEST(StrCSpnTest, AllIn) {
    constexpr char const *dst = "foobar";
    constexpr char const *src = "foobar";
    static_assert(0 == cxs::strcspn(dst, src), "Test Failure");
    EXPECT_EQ(std::strcspn(dst, src), cxs::strcspn(dst, src));
}

TEST(StrCSpnTest, CppReferenceTestCase) {
    constexpr char const *invalid = "$#@";
    constexpr char const *dst = "abcde312$#@";
    static_assert(8 == cxs::strcspn(dst, invalid), "Test Failure");
    EXPECT_EQ(std::strcspn(dst, invalid), cxs::strcspn(dst, invalid));
}

// strpbrk
TEST(StrPbrkTest, AllEmpty) {
    constexpr char const *dest = "";
    constexpr char const *breakset = "";
    static_assert(nullptr == cxs::strpbrk(dest, breakset));
    EXPECT_EQ(std::strpbrk(dest, breakset), cxs::strpbrk(dest, breakset));
}
TEST(StrPbrkTest, DestEmpty) {
    constexpr char const *dest = "";
    constexpr char const *breakset = "abc";
    static_assert(nullptr == cxs::strpbrk(dest, breakset));
    EXPECT_EQ(std::strpbrk(dest, breakset), cxs::strpbrk(dest, breakset));
}
TEST(StrPbrkTest, CppRefferenceExample) {
    const char *str = "hello world, friend of mine!";
    const char *sep = " ,!";
    unsigned int cnt = 0;

    std::string expected[]{" world, friend of mine!", ", friend of mine!",
                           " of mine!", " mine!", "!"};
    size_t i{};
    do {
        str = cxs::strpbrk(str, sep); // find separator
        EXPECT_EQ(std::string(str), expected[i]);
        ++i;
        if (str) {
            str += std::strspn(str, sep); // skip separator
        }
        ++cnt; // increment word count
    } while (str && *str);
}

// strstr
TEST(StrStrTest, EmptyEmpty) {
    constexpr char const *haystack = "";
    constexpr char const *needle = "";
    static_assert(haystack == cxs::strstr(haystack, needle));
    EXPECT_EQ(std::strstr(haystack, needle), cxs::strstr(haystack, needle));
}
TEST(StrStrTest, EmptyNeedle) {
    constexpr char const *haystack = "Hello";
    constexpr char const *needle = "";
    static_assert(haystack == cxs::strstr(haystack, needle));
    EXPECT_EQ(std::strstr(haystack, needle), cxs::strstr(haystack, needle));
}
TEST(StrStrTest, EmptyHaystack) {
    constexpr char const *haystack = "";
    constexpr char const *needle = "x";
    static_assert(nullptr == cxs::strstr(haystack, needle));
    EXPECT_EQ(std::strstr(haystack, needle), cxs::strstr(haystack, needle));
}
TEST(StrStrTest, Basic) {
    constexpr char const *haystack = "cdrabgteababauit";
    constexpr char const *needle = "aba";
    static_assert(haystack + 8 == cxs::strstr(haystack, needle));
    EXPECT_EQ(std::strstr(haystack, needle), cxs::strstr(haystack, needle));
    EXPECT_EQ(haystack + 8, cxs::strstr(haystack, needle));
}

// memchr

// memcmp

// tests of helper functions and classes
TEST(CharSetTest, SetCharIsSetBasic) {
    cxs::detail::CharSet chs{};
    chs.set('a');
    chs.set('x');
    chs.set('0');
    EXPECT_TRUE(chs.isSet('a'));
    EXPECT_TRUE(chs.isSet('x'));
    EXPECT_TRUE(chs.isSet('0'));
    EXPECT_FALSE(chs.isSet('b'));
    EXPECT_FALSE(chs.isSet('Z'));
    EXPECT_FALSE(chs.isSet('+'));
}
TEST(CharSetTest, SetCharIsSetExhaustive) {
    for (size_t i{0}; i <= 255; ++i) {
        char const symbol = static_cast<char>(i);
        cxs::detail::CharSet chs{};
        EXPECT_FALSE(chs.isSet(symbol));
        chs.set(symbol);
        EXPECT_TRUE(chs.isSet(symbol));
    }
}
TEST(CharSetTest, DefaultConstructedIsEmpty) {
    cxs::detail::CharSet chs{};
    for (size_t i{0}; i <= 255; ++i) {
        char const symbol = static_cast<char>(i);
        EXPECT_FALSE(chs.isSet(symbol));
    }
}
TEST(CharSetTest, StringConstructor) {
    constexpr char const *characters = "acf845;)p";
    constexpr cxs::detail::CharSet chs(characters);
    for (size_t i{0}; i <= 255; ++i) {
        char const symbol = static_cast<char>(i);
        bool const is_null = ('\0' == symbol);
        bool const found_in_characters =
            (std::strchr(characters, symbol) != nullptr);
        bool const should_be_set = !is_null && found_in_characters;
        if (should_be_set) {
            EXPECT_TRUE(chs.isSet(symbol))
                << "Symbol " << symbol << " should be set!";
        } else {
            EXPECT_FALSE(chs.isSet(symbol))
                << "Symbol " << symbol << " should not be set!";
        }
    }
}
TEST(CharSetTest, StringConstructorConstexpr) {
    constexpr char const *characters = "ac4";
    constexpr cxs::detail::CharSet chs(characters);
    static_assert(chs.isSet('a'));
    static_assert(chs.isSet('c'));
    static_assert(chs.isSet('4'));
    static_assert(!chs.isSet('b'));
    static_assert(!chs.isSet('C'));
    static_assert(!chs.isSet('9'));
}
TEST(RandomSymbolTest, AllSymbolsGenerated) {
    std::set<unsigned char> generated_symbols;
    for (int i = 0; i < 2000; ++i) {
        generated_symbols.insert(random_symbol());
    }
    EXPECT_EQ(256, generated_symbols.size());
}