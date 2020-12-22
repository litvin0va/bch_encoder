#include <stdio.h>
#include "polynom.h"
#include "prime_elem.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>

int get_input_parameters (int &n, int &m);
std::vector<bool> get_input (int max_len);
bool check (const polynom &g, int n);

int main ()
{
  int n, t, m;
  if (get_input_parameters (n, m))
    return -1;
  printf ("Input t less then %d: ", 1<< (m - 2));
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
  encode_word (input_vector, g, n);
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



int get_input_parameters (int &n, int &m)
{
  printf ("Input m less then 16: ");
  scanf ("%d", &m);

  if (m >= 15)
    {
      printf ("Error: Bad Input!\n");
      return -1;
    }

  n = (1 << m) - 1;
  printf ("n : %d \n", n);
  return 0;
}

bool check (const polynom &g, int n)
{
  std::vector<bool> pol_vec;
  pol_vec.push_back (true);
  for (int i = 1; i < n; i++)
    pol_vec.push_back (false);
  pol_vec.push_back (true);
  polynom pol (pol_vec);
  if (!(pol % g).size ())
    {
      //printf ("POLYNOM g IS CORRECT\n");
      return true;
    }
  else
    {
      //printf ("POLYNOM g IS NOT CORRECT\n");
      return false;
    }
}
