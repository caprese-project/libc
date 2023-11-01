#include <stdlib.h>

div_t div(int numer, int denom) {
  div_t result;
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
