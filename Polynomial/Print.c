

void print(polyList *poly1)
{
  int order = order(poly1); // get highest order that coefficient isn't 1
  for(int i=0; i < order; i ++) // for loop from 0 to highest order
    {
      
      printf("%lf x^%d +",(poly1->current->d.coefficient),i); // prints coefficient polynominal starting at least significant
     
      current = poly1->current->next; // sets current to next number 
    }
  
  printf("%lf", (poly1->order)); // prints most signicant of polynominal
}
