#include <stdio.h>
#include "polynom.h"
#include "prime_elem.h"
#include <vector>


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
				fprintf (f, "%d %d\n", curr.size (), i);
		}
	fclose (f);
}

