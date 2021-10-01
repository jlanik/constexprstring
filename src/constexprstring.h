#include <cstddef>

namespace constexprstring {

constexpr std::size_t strlen(const char *str) {
  std::size_t cnt{};
  for (char const *it = str; *it != '\0'; ++it) {
    ++cnt;
  }
  return cnt;
}
}
