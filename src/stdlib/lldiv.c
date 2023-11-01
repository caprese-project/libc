#include <stdlib.h>

lldiv_t lldiv(long long int numer, long long int denom) {
  lldiv_t result;
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
