#include <stdio.h>
#include "polynom.h"

int main ()
{
  printf ("\nA:\n");
  polynom a (32+16+4+1);
  a.print ();
  a.print_polynom ();

  printf ("\nB:\n");
  polynom b (5);
  b.print ();
  b.print_polynom ();

  printf ("\nA + B:\n");
  polynom c = a + b;
 // c.print ();
  c.print_polynom ();

  printf ("\nA * B:\n");
  c = a * b;
  //c.print ();
  c.print_polynom ();

  printf ("\nA / B:\n");
  c = a / b;
  //c.print ();
  c.print_polynom ();

  printf ("\nA % B:\n");
  c = a % b;
  //c.print ();
  c.print_polynom ();

  return 0;
}
