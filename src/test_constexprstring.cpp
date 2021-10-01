#include "constexprstring.h"

#include <gtest/gtest.h>

#include <cstring>

namespace cxs = constexprstring;

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
