#pragma once
#include <vector>


struct polynom_coef
{
  bool m_coef = false;

  polynom_coef (bool state) : m_coef (state) {}

  polynom_coef operator + (const polynom_coef &c) const
  {
    if ( (this->m_coef &&  c.m_coef) ||
        (!this->m_coef && !c.m_coef))
      return polynom_coef (false);
    return polynom_coef (true);
  }

  polynom_coef operator * (const polynom_coef &c) const
  {
    return this->m_coef && c.m_coef;
  }

  void operator += (const polynom_coef &c)
  {
    *this = *this + c;
  }

  void operator *= (const polynom_coef &c)
  {
    *this = *this * c;
  }

  bool operator () () const
  {
    return m_coef;
  }

  bool operator == (const polynom_coef &c) const
  {
    return m_coef == c.m_coef;
  }

  bool operator != (const polynom_coef &c) const
  {
    return m_coef != c.m_coef;
  }

  bool operator > (const polynom_coef &c) const
  {
    return m_coef && !c.m_coef;
  }

  bool operator < (const polynom_coef &c) const
  {
    return !m_coef && c.m_coef;
  }

};


class polynom
{
  //int max_size;
  std::vector<polynom_coef> m_coefs;

public:
  polynom () {}
  polynom (int n);
  polynom (std::vector<polynom_coef> &pol);
  ~polynom ();

  int size () const { return m_coefs.size (); }

  void print () const;
  void print_polynom () const;
  void squeeze ();

  bool get_value (bool value) const;

  
  polynom operator + (const polynom &second) const;
  polynom operator - (const polynom &second) const;
  polynom operator * (const polynom &pol) const;
  polynom operator / (const polynom &divider) const;
  polynom operator % (const polynom &divider) const;
  bool operator > (const polynom &second) const;
  bool operator < (const polynom &second) const;
  bool operator == (const polynom &second) const;

  void operator += (const polynom &second);
  void operator -= (const polynom &second);
  void operator *= (const polynom &pol);
  void operator /= (const polynom &pol);
  void operator %= (const polynom &pol);
};


void divide (const polynom &dividend, const polynom &divider, polynom &res, polynom &remainder);
