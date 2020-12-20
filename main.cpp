#include <stdio.h>
#include "polynom.h"
#include "prime_elem.h"

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

  polynom a1 (8 + 1);
  polynom b1 (16 + 4 + 1);
  printf ("\na1 = ");
  a1.print_polynom ();
  printf ("\nb1 = ");
  b1.print_polynom ();
  printf ("\nb1 %% a1 = ");
  (b1 % a1).print_polynom ();

  polynom prime (8 + 4 + 1);
  printf ("prime for factor by x3 + x2 + 1 :\n");
  find_prime (prime).print_polynom ();

  return 0;
}
