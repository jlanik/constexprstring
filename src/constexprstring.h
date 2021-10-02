#include <cstddef>

namespace constexprstring {

constexpr std::size_t strlen(const char *str) {
  std::size_t cnt{};
  for (char const *it = str; *it != '\0'; ++it) {
    ++cnt;
  }
  return cnt;
}

constexpr int strcmp(const char *lhs, const char *rhs) {
  constexpr int LEFT_LOWER{-1};
  constexpr int LEFT_GREATER{1};
  constexpr int BOTH_EQUAL{0};

  // This copy is necessary as lhs and rhs can not be modified in constexpr
  // context.
  char const *lptr = lhs;
  char const *rptr = rhs;

  do {
    if ('\0' == *lptr) {
      if ('\0' == *rptr) {
        // both empty
        return BOTH_EQUAL;
      } else {
        // lptr is a prefix of rptr
        return LEFT_LOWER;
      }
    } else {
      if ('\0' == *rptr) {
        // rptr is a prefix of lptr
        return LEFT_GREATER;
      } else {
        int const diff = (static_cast<int>(static_cast<unsigned char>(*lptr)) -
                          static_cast<int>(static_cast<unsigned char>(*rptr)));
        if (diff > 0) {
          return LEFT_GREATER;
        } else if (diff < 0) {
          return LEFT_LOWER;
        } else {
          // Equal until now - need to look at the next symbol.
          ++lptr;
          ++rptr;
          continue;
        }
      }
    }

  } while (true);
}


} //namespace constexprstring
