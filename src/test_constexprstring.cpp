#include "constexprstring.h"

#include <gtest/gtest.h>

#include <cstring>

namespace cxs = constexprstring;

// c++14 compatibility
TEST(CPP14Compatibility,Check){
  //EXPECT_EQ( 201103L, __cplusplus);
  EXPECT_EQ( 201402L, __cplusplus);
}

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
  EXPECT_EQ(std::strcmp(str_empty1, str_empty2),
            cxs::strcmp(str_empty1, str_empty2));

  static_assert(-1 == cxs::strcmp(str_empty1, str_nonempty), "Test Failure");
  EXPECT_EQ(-1, cxs::strcmp(str_empty1, str_nonempty));
  EXPECT_EQ(std::strcmp(str_empty1, str_nonempty),
            cxs::strcmp(str_empty1, str_nonempty));

  static_assert(1 == cxs::strcmp(str_nonempty, str_empty1), "Test Failure");
  EXPECT_EQ(1, cxs::strcmp(str_nonempty, str_empty1));
  EXPECT_EQ(std::strcmp(str_nonempty, str_empty1),
            cxs::strcmp(str_nonempty, str_empty1));
}

TEST(StrCmpTest, OneCharSame) {
  constexpr const char *str1 = "H";
  constexpr const char *str2 = "H";
  static_assert(0 == cxs::strcmp(str1, str2), "Test Failure");
  EXPECT_EQ(0, cxs::strcmp(str1, str2));
  EXPECT_EQ(std::strcmp(str1, str2), cxs::strcmp(str1, str2));
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
  EXPECT_EQ(std::strcmp(str1, str2), cxs::strcmp(str1, str2));
}

TEST(StrCmpTest, Prefix) {
  constexpr const char *str1 = "Hi";
  constexpr const char *str2 = "Hi There!";
  static_assert(-1 == cxs::strcmp(str1, str2), "Test Failute");
  EXPECT_EQ(-1, cxs::strcmp(str1, str2));
  EXPECT_EQ(std::strcmp(str1, str2), cxs::strcmp(str1, str2));
  static_assert(1 == cxs::strcmp(str2, str1), "Test Failute");
  EXPECT_EQ(1, cxs::strcmp(str2, str1));
  EXPECT_EQ(std::strcmp(str2, str1), cxs::strcmp(str2, str1));
}

TEST(StrCmpTest, DifferentFirstChar) {
  constexpr const char *str1 = "Atralala";
  constexpr const char *str2 = "Btralala";
  static_assert(-1 == cxs::strcmp(str1, str2), "Test Failute");
  EXPECT_EQ(-1, cxs::strcmp(str1, str2));
  EXPECT_EQ(std::strcmp(str1, str2), cxs::strcmp(str1, str2));
  static_assert(1 == cxs::strcmp(str2, str1), "Test Failute");
  EXPECT_EQ(1, cxs::strcmp(str2, str1));
  EXPECT_EQ(std::strcmp(str2, str1), cxs::strcmp(str2, str1));
}

TEST(StrCmpTest, DifferentLaterChar) {
  constexpr const char *str1 = "tralaAla";
  constexpr const char *str2 = "tralaCla";
  static_assert(-1 == cxs::strcmp(str1, str2), "Test Failute");
  EXPECT_EQ(-1, cxs::strcmp(str1, str2));
  EXPECT_EQ(std::strcmp(str1, str2), cxs::strcmp(str1, str2));
  static_assert(1 == cxs::strcmp(str2, str1), "Test Failute");
  EXPECT_EQ(1, cxs::strcmp(str2, str1));
  EXPECT_EQ(std::strcmp(str2, str1), cxs::strcmp(str2, str1));
}

// strncmp

// strcoll

// strchr

// strrchr

// strspn

// strcspn

// strpbrk

// strstr

// strtok NOTE: has internal state, can we adjust it?

// memchr

// memcmp
