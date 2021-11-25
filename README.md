# constexprstring
Constexpr versions of cstring functions in C++14

In C++11 constexpr functions can have just one line, therefore we use C++14, as the one-line requirement would enforce recursive implementation that wouldn't be efficient in non-constexpr context. 

Functions that are currently implemented:
- strlen
- strcmp
- strncmp
- strchr
- strrchr
- strspn
- strcspn
- strpbrk
- strstr

To use it, just copy and include src/constexprstring.h
