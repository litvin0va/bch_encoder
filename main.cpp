#include <stdio.h>
#include "polynom.h"
#include "prime_elem.h"

int main ()
{
  polynom a (4 + 1);
  polynom b (4 + 2 + 1);
  polynom mod (2 + 1);

  std::vector<polynom> vec;
  vec.push_back (a);
  vec.push_back (b);

  printf ("\nVECTOR PROD:\n");
  auto prod = get_nullifying_product (vec, mod);
  prod.print_polynom ();

  return 0;
}
