#include "polynom.h"
#include <vector>
#include <stdio.h>

polynom::polynom (int n)
{
  while (n)
    {
      m_coefs.push_back (n % 2);
      n >>= 1;
    }
}

polynom::polynom (std::vector<polynom_coef> &pol)
{
  m_coefs = pol;
}

polynom::~polynom ()
{
}


void polynom::print () const
{
  printf ("< ");
  for (auto val : m_coefs)
    printf ("%d ", val);
  printf (">\n");
}

void polynom::print_polynom () const
{
  bool is_first = true;
  for (int deg = 0; deg < m_coefs.size (); ++deg)
    {
      if (!m_coefs[deg]())
        continue;
      if (is_first)
        if (!deg)
          printf ("1");
        else
          printf ("x%d", deg);
      else
        printf (" + x%d", deg);
      is_first = false;
    }
  printf ("\n");
}


polynom polynom::operator + (const polynom &second) const
{
  int first_size = this->size ();
  int second_size = second.size ();
  const polynom &little = (second_size > first_size ? *this : second);
  const polynom &big = (second_size > first_size ? second : *this);

  polynom res = big;

  for (int i = 0; i < little.size (); ++i)
    res.m_coefs[i] += little.m_coefs[i];

  return res;
}


polynom polynom::operator * (const polynom &pol) const
{
  int first_size = this->size ();
  int second_size = pol .size ();
  const auto &first = this->m_coefs;
  const auto &second = pol.m_coefs;

  polynom res;
  auto &coefficients = res.m_coefs;
  coefficients.resize (first_size + second_size - 1, false);

  for (int i1 = 0; i1 < first_size; i1++)
    for (int i2 = 0; i2 < second_size; i2++)
      coefficients[i1 + i2] += first[i1] * second[i2];

  return res;
}

















