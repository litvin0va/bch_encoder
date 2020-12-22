#include <stdio.h>
#include "polynom.h"
#include "prime_elem.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int get_input_parameters (int &n, int &m);
int get_factor_polynom (int m);
std::vector<bool> get_input (int max_len);
void check (const polynom &g, int n);

int main ()
{
  int n, t, m;
  if (get_input_parameters (n, m))
    return -1;
  printf ("Input t less then %d: ", 1<<m);
  scanf ("%d", &t);

  int factor_pol = get_factor_polynom (m);
  if (factor_pol < 1)
    return -1;

  polynom factor_polynom (factor_pol);
  polynom prime = find_prime (factor_polynom);
  auto powers_of_prime = create_power_vector (prime, 2 * t, factor_polynom);
  polynom g = get_nullifying_product (powers_of_prime, factor_polynom);

  check (g, (1 << m) - 1);
  g.print_polynom ();

  auto input_vector = get_input (n - g.size());
  polynom word (input_vector);
  int k = word.size ();
  word.squeeze ();
  polynom mult (1<<(n-k));
  word *= mult;
  word += word % g;
  word.print();
  return 0;
}

std::vector<bool> get_input (int max_size)
{
  printf ("Input word (max len = %d): ", max_size);
  char input[100];
  scanf ("%s", input);

  std::vector<bool> input_vector;
  for (int i = 0 ; i < strlen (input); i++)
    {
      if (!(input[i] == '0' || input[i] == '1' && i < max_size))
        {
          printf ("Incorrect input word!\n");
          return {};
        }
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

int get_input_parameters (int &n, int &m)
{
  printf ("Input m less then 5: ");
  scanf ("%d", &m);

  if (m > 15)
    {
      printf ("Error: Bad Input!\n");
      return -1;
    }

  n = (1 << m) - 1;
  printf ("n : %d \n", n);
  return 0;
}

void check (const polynom &g, int n)
{
  printf ("p1\n");
  polynom pol ((1 << n) + 1);
  if (!(pol % g).size ())
    printf ("POLYNOM g IS CORRECT\n");
  else
    printf ("POLYNOM g IS NOT CORRECT\n");
}
