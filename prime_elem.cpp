#include <stdio.h>
#include "polynom.h"
#include "prime_elem.h"
#include <vector>
#define MAX_POLYNOM 1e15


std::vector<polynom> create_power_vector (const polynom &pol, int max_deg, const polynom &mod)
{
  std::vector<polynom> vec;
  polynom tmp (1);
  for (int i = 1; i <= max_deg; i++)
    {
      tmp *= pol;
      vec.push_back (tmp % mod);
    }
  return vec;
}

polynom get_nullifying_polynom (const polynom &p, const polynom &mod) ///find f : f(p)=0 (mod)
{
  int pol = 2;
  while (pol < MAX_POLYNOM)
    {
      polynom f (pol);
      polynom ins = f.insert_polynom (p);
      polynom remainder = ins % mod;
      if (!remainder.size ())
        return f;
      pol++;
    }
  printf ("Nullifying Polynom not Found!!!!\n");
  return polynom ();
}

bool find (const std::vector<polynom> &pol_vector, const polynom &pol_to_find)
{
  for (const auto &pol : pol_vector)
    {
      if (pol == pol_to_find)
        return true;
    }
  return false;
}

polynom get_product (const std::vector<polynom> &pol_vector)
{
  polynom ans (1);
  for (const auto &pol : pol_vector)
    {
      //pol.print ();
      ans *= pol;
    }
  return ans;
}

polynom get_nullifying_product (const std::vector<polynom> &vec, const polynom &mod)
{
  std::vector<polynom> polynoms_to_product;

  for (const auto &pol : vec)
    {
      auto nullinying = get_nullifying_polynom (pol, mod);
      if (find (polynoms_to_product, nullinying))
        continue;
      polynoms_to_product.push_back (nullinying);
    }
  //printf ("SIZE: %d\n", polynoms_to_product.size ());
  if (!polynoms_to_product.size ())
    printf ("Nullifying Polynoms Vector is Empty!!!!\n");
  return get_product (polynoms_to_product);
}


polynom find_prime (const polynom &factor)
{
	int factor_deg = factor.size () - 1;
	int polynoms_num = (1 << factor_deg);
	for (int i = 2; i < polynoms_num; i++)
		{
			polynom prime_condidate (i);
			int cicle_size = 1;
			polynom prime = prime_condidate;

			while (prime.size () > 1)
				{
					prime *= prime_condidate;
					prime %= factor;
					cicle_size++;
					if (!prime.size ())
						{
							fprintf (stderr, "FACTOR POLYNOM IS NOT PRIME!\n");
							return polynom (0);
						}
				}
			if (cicle_size == polynoms_num - 1)
				return polynom (i);
		}
	fprintf (stderr, "PRIME ELEM NOT FOUND!\n");
	return polynom (0);
}

void gener_prime_polynoms (int max_size)
{
	FILE *f = fopen ("primes.txt", "w");
	for (int i = 2; i <= (1 << max_size); i++)
		{
			polynom curr (i);
			if (!curr.get_value (0) || !curr.get_value (1))
				continue;

			int j;
			for (j = 2; j < i; j++)
				{
					if (!((curr % polynom (j)).size ()))
						break;
				}
			if (j >= i)
				fprintf (f, "%d %d\n", curr.size () - 1, i);
		}
	fclose (f);
}


