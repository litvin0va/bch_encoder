#include <stdio.h>
#include "polynom.h"
#include "prime_elem.h"

int main ()
{
  int n, t, m;
  printf ("Input m : ");
  scanf ("%d", &m);

  if (m > 15)
    {
      printf ("Error: Bad Input!\n");
      return 0;
    }

  n = (1 << m) - 1;
  printf ("n : %d \n", n);

  printf ("Input t : ");
  scanf ("%d", &t);

  FILE *fp;
  if (!(fp = fopen ("primes.txt", "r")))
    {
      printf ("File \n");
      return -1;
    }
  int deg, pol;
  while (fscanf (fp, "%d %d", &deg, &pol) == 2)
    {
      if (deg == m)
        break;
      pol = -1;
    }
  if (pol <= 1)
    {
      printf ("CANT TAKE FACTOR POLYNOM FROM FILE\n");
      fclose (fp);
      return 0;
    }
  fclose (fp);

  polynom first_polynom (pol);
  polynom prime = find_prime (first_polynom);
  auto powers_of_prime = create_power_vector (prime, 2 * t, first_polynom);
  polynom g = get_nullifying_product (powers_of_prime, first_polynom);
  g.print_polynom ();

  int input;
  printf ("Input word : ");
  scanf ("%d", &input);
  polynom word (input);
  int k = word.size ();
  polynom mult (1<<(n-k));
  word *= mult;
  word += word % g;
  word.print();
  return 0;
}
