#include <stdio.h>
#include "polynom.h"
#include "prime_elem.h"
#include <vector>
#define MAX_POLYNOM 1e15

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

void encode_word (std::vector<bool> &input_vector, const polynom &g, int n)
{
  polynom word (input_vector);
  int k = word.size();
  word.squeeze ();

  std::vector<bool> pol_vec;
  for (int i = 0; i < n - k; i++)
    pol_vec.push_back (false);
  pol_vec.push_back (true);

  polynom mult (pol_vec/*1<<(n-k)*/);
  word *= mult;
  word += word % g;
  word.add_zeros_to (n);
  word.print();
}

std::vector<polynom> create_power_vector (const polynom &pol, int max_deg, const polynom &mod)
{
  std::vector<polynom> vec;
  polynom tmp (1);
  for (int i = 1; i <= max_deg; i++)
    {
      tmp *= pol;
      tmp %= mod;
      vec.push_back (tmp);
    }
  return vec;
}

polynom get_nullifying_polynom (const polynom &p, const polynom &mod) ///find f : f(p)=0 (mod)
{
  int pol = 2;
  while (pol < MAX_POLYNOM)
    {
      polynom f (pol);
      polynom ins = f.insert_polynom (p, mod);
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


