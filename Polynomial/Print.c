// Author : Aaron Naylor

void polyPrint(polyList *poly1)
{
  
  int power=1; // stores power value
  int order = polyOrder(poly1); // get highest order that coefficient isn't 1
  poly1->current = poly1->head; // set current to first element
  printf("%lf +", (poly1->current->d.coefficient)); // prints first element
  poly1->current = poly1->current->next; // sets current to next number 
  
  for(int i=1; i < order; i ++) // for loop from 0 to highest order
    {
      
      printf("%lf x^%d +",(poly1->current->d.coefficient),power); // prints coefficient polynominal starting at least significant
      power++; // increase power by 1
      poly1->current = poly1->current->next; // sets current to next number 
    }
  
  printf("%lf x^%d\n", (poly1->current->d.coofficient),power); // prints most signicant of polynominal
}
