#if(defined(_MSC_VER) && (_MSC_VER < 1600))
  // old MSVC - hasn't stdint header
  typedef unsigned __int32  uint32_t;
#elif defined(__hpux) && !defined(__GNUC__)
# include <inttypes.h>
#else
# include <stdint.h>
#endif

#include <cstddef>

int dispatch(const size_t x) { return 1; }
int dispatch(const uint32_t x) { return 1; }

template <class TheKeyType>
class foo {
  static int bar(const TheKeyType& theKey)
  { return dispatch(theKey); }
};

int main(int argc, char* argv[])
{
  foo<size_t> o1;
  foo<uint32_t> o3;
  return 0;
}
