#include <stdio.h>
#include "polynom.h"
#include "prime_elem.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int get_input_parameters (int &n, int &t, int &m);
int get_factor_polynom (int m);
std::vector<bool> get_input ();

int main ()
{
  int n, t, m;
  if (get_input_parameters (n, t, m))
    return -1;

  int factor_pol = get_factor_polynom (m);
  if (factor_pol < 1)
    return -1;

  polynom factor_polynom (factor_pol);
  polynom prime = find_prime (factor_polynom);
  auto powers_of_prime = create_power_vector (prime, 2 * t, factor_polynom);
  polynom g = get_nullifying_product (powers_of_prime, factor_polynom);

  g.print_polynom ();

  auto input_vector = get_input ();
  polynom word (input_vector);
  int k = word.size ();
  word.squeeze ();
  polynom mult (1<<(n-k));
  word *= mult;
  word += word % g;
  word.print();
  return 0;
}

std::vector<bool> get_input ()
{
  printf ("Input word : ");
  char input[100];
  scanf ("%s", input);

  std::vector<bool> input_vector;
  for (int i = 0 ; i < strlen (input); i++)
    {
      bool f = (input[i] == '0' ? false : true);
      input_vector.push_back (f);
    }
  return input_vector;
}

int get_factor_polynom (int m)
{
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
      return -2;
    }
  fclose (fp);
  return pol;
}

int get_input_parameters (int &n, int &t, int &m)
{
  printf ("Input m : ");
  scanf ("%d", &m);

  if (m > 15)
    {
      printf ("Error: Bad Input!\n");
      return -1;
    }

  n = (1 << m) - 1;
  printf ("n : %d \n", n);

  printf ("Input t : ");
  scanf ("%d", &t);
  return 0;
}
