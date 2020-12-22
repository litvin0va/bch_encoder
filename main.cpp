#include <stdio.h>
#include "polynom.h"
#include "prime_elem.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>

int get_input_parameters (int &n, int &m);
int get_factor_polynom (int m);
std::vector<bool> get_input (int max_len);
bool check (const polynom &g, int n);

int main ()
{
  std::ofstream out;
  out.open("generating.txt");

  for (int m = 2; m < 15; m++)
    {
      int n = (1 << m) - 1;
      int factor_pol = get_factor_polynom (m);
      if (factor_pol < 1)
        return -1;

      polynom factor_polynom (factor_pol);
      polynom prime = find_prime (factor_polynom);

      for (int t = 1; t < (1 << (m - 2)); t++)
        {
          auto powers_of_prime = create_power_vector (prime, 2 * t, factor_polynom);
          polynom g = get_nullifying_product (powers_of_prime, factor_polynom);
          if (n == g.size())
            {
              printf ("Skip t > %d\n", t);
              break;
            }
          /*if (!check (g, (1 << m) - 1))
            {
              printf ("BAD!!!!!\n");
              return -1;
            }*/
          std::string ans = "";
          g.get_string_polynom (ans);
          out << m << " " << t << " " << ans << "\n";
          printf ("%d %d\n", m, t);
        }
    }
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
      printf ("CANT TAKE FACTOR POLYNOM %d FROM FILE\n", m);
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

bool check (const polynom &g, int n)
{

  polynom pol ((1 << n) + 1);
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
