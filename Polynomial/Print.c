// Author : Aaron Naylor

//#include <stdlib.h>
//#include <stdio.h>
#include "polynomial.h"

/*int main()
{
  double arr[] = {5, 2, 6, 7};
  polyList *poly1;
  poly1 = polyCreate();
  fillPoly(poly1, 3, arr);
  polyPrint(poly1);
}*/
///////////////////////////////////////////////////////
// polyPrint(poly1)
//  prints a polynomial to the user
//
// parameter:  poly - pointer to polynomial
///////////////////////////////////////////////////////

void polyPrint(polyList *poly1)
{  
  int order = polyOrder(poly1); // get highest order that coefficient isn't 0
  poly1->current = poly1->head; // set current to first element
  fprintf( stdout, "%lf", (poly1->current->d.coefficient)); // prints first element
  poly1->current = poly1->current->next; // sets current to next number 
  
  for(int i = 1; i <= order; i ++) // for loop from 0 to highest order
  {
    fprintf( stdout, " + %lfx^%d", poly1->current->d.coefficient, i); // prints coefficient polynominal starting at least significant
      poly1->current = poly1->current->next; // sets current to next number 
  }
  // Print new line
  printf("\n\n");
}
