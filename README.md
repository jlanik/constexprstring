# constexprstring
Constexpr versions of cstring functions in C++14

In C++11 constexpr functions can have just one line, therefore we use C++14, as the one-line requirement would enforce recursive implementation that wouldn't be efficient in non-constexpr context. 

Functions that are implemented:
- strlen
- strcmp
- strncmp
- strchr
- strrchr
- strspn
- strcspn
- strpbrk
- strstr

We implemented only functions that don't have side effect, as side effects are impossible in constexpr functions.

memchr and memcmp are not implemented, as it is not possible to perform a coversion of void* in constexpr funcion (see discussion: https://stackoverflow.com/questions/70543372/how-to-cast-from-const-void-in-a-constexpr-expression/70543641#70543641 ).

We have also ommited functons that use locale (e.g. strcoll).


To use the library, just copy and include src/constexprstring.h
