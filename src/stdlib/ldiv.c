#include <stdlib.h>

ldiv_t ldiv(long int numer, long int denom) {
  ldiv_t result;
  result.quot = numer / denom;
  result.rem  = numer % denom;

  if (numer >= 0 && result.rem < 0) {
    ++result.quot;
    result.rem -= denom;
  } else if (numer < 0 && result.rem > 0) {
    --result.quot;
    result.rem += denom;
  }

  return result;
}
