#include <stdio.h>
#include "polynom.h"

int main ()
{
  polynom a (17);
  a.print ();
  a.print_polynom ();

  printf ("\n");

  polynom b (3);
  b.print ();
  b.print_polynom ();

  printf ("\nSum:\n");
  polynom c = a + b;
  c.print ();
  c.print_polynom ();

  printf ("\nMult:\n");
  c = a * b;
  c.print ();
  c.print_polynom ();

  return 0;
}
