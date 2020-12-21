#include <stdio.h>
#include "polynom.h"
#include "prime_elem.h"

int get_m_by_n (int n)
{
  return (polynom (n) + polynom (1)).size ();
}

bool check_n (int n)
{
  polynom pol (n);
  return pol.is_all_units ();
}

int main ()
{
  int n, t;
  printf ("Input n : ");
  scanf ("%d", &n);

  printf ("Input t : ");
  scanf ("%d", &t);

  if (!check_n (n))
    {
      printf ("Error: N need to be as 2^m-1 \n");
      return -1;
    }

  int m = get_m_by_n (n);
  printf ("m : %d \n", m);
  if (m > 15)
    {
      printf ("Error: Bad Input!\n");
      return 0;
    }

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
  word %= g;
  word.print();
  return 0;
}
