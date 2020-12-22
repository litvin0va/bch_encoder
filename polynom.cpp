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

polynom::polynom (std::vector<bool> &pol)
{
  for (bool p : pol)
    m_coefs.push_back (polynom_coef (p));
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

int polynom::get_polynom () const
{
  int ans = 0;
  for (int i = 0; i < size (); i++)
    {
      if (m_coefs[i] ())
        ans += 1<<i;
    }
  return ans;
}

void polynom::get_string_polynom (std::string &ans) const
{
  for (int i = 0; i < size (); i++)
    {
      if (m_coefs[i] ())
        ans += "1";
      else
        ans += "0";
    }
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

void polynom::squeeze () ///delete leading zeros
{
  while (1)
    {
      if (m_coefs.size () && !m_coefs.back () ())
        m_coefs.pop_back ();
      else
        return;
    }
}

polynom polynom::insert_polynom (const polynom &value, const polynom &mod) const
{
  polynom res;
  polynom term (true);
  for (int i = 0; i < size (); i++)
    {
      term *= value;
      term %= mod;
      if (!m_coefs[i] ())
        continue;
      res += term;
    }
  return res;
}

bool polynom::get_value (bool value) const
{
  if (!value)
    {
      if (size ())
        return m_coefs.front ()();
      return false;
    }
  polynom_coef res (false);
  for (auto &coef : m_coefs)
    {
      if (!coef ())
        continue;
      res += polynom_coef (true);
    }
  return res ();
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

  res.squeeze ();
  return res;
}

polynom polynom::operator - (const polynom &second) const
{
  return *this + second;
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

  res.squeeze ();
  return res;
}


void divide (const polynom &dividend, const polynom &divider, polynom &res, polynom &remainder)
{
  int first_size = dividend.size ();
  int second_size = divider.size ();

  if (dividend.size () < divider.size ())
    {
      res = polynom (0);
      remainder = dividend;
      return;
    }

  remainder = dividend;

  while (remainder.size () >= divider.size ())
    {
      int factor_degree = remainder.size () - divider.size ();
      polynom factor_polynom (1 << factor_degree);
      res += factor_polynom;
      remainder -= divider * factor_polynom;
    }
}

polynom polynom::operator / (const polynom &divider) const
{
  polynom res, remainder;
  divide (*this, divider, res, remainder);
  return res;
}

bool polynom::is_all_units () const
{
  for (const auto &coef : m_coefs)
    if (!coef ())
      return false;
  return true;
}


polynom polynom::operator % (const polynom &divider) const
{
  polynom res, remainder;
  divide (*this, divider, res, remainder);
  return remainder;
}


bool polynom::operator > (const polynom &second) const
{
  if (this->size () != second.size ())
    return this->size () > second.size ();

  for (int i = 0; i < second.size (); i++)
    if (m_coefs[i] > second.m_coefs[i])
      return true;
  return false;
}

bool polynom::operator < (const polynom &second) const
{
  if (this->size () != second.size ())
    return this->size () < second.size ();

  for (int i = 0; i < second.size (); i++)
    if (m_coefs[i] < second.m_coefs[i])
      return true;
  return false;
}

bool polynom::operator == (const polynom &second) const
{
  if (this->size () != second.size ())
    return false;

  for (int i = 0; i < second.size (); i++)
    if (m_coefs[i] != second.m_coefs[i])
      return false;
  return true;
}

void polynom::operator += (const polynom &second)
{
  *this = *this + second;
}

void polynom::operator -= (const polynom &second)
{
  *this = *this - second;
}

void polynom::operator *= (const polynom &pol)
{
  *this = *this * pol;
}

void polynom::operator /= (const polynom &second)
{
  *this = *this / second;
}

void polynom::operator %= (const polynom &pol)
{
  *this = *this % pol;
}


