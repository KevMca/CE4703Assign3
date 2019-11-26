// Author: Aaron

//#include <stdio.h>
//#include <stdlib.h>
#include "polynomial.h"
/*
int main()
{
  polyList *polyNew;
  polyNew = polyCreate();
  double arr[] = {10, 5, 0, 2, 0};
  fillPoly(polyNew, 3, arr);
  //printf("%d\n", polyOrder(polyNew));
  polyList *polyNorm = polyNormalise(polyNew);
  printf("%lf\n", polyNorm->current->d.coefficient);
}*/

polyList *polyNormalise(polyList *poly1)
{
  polyList *norm; // variable to store value before returned
  double highCoeff; // stores coefficient of highest order
  int order = polyOrder(poly1); // calls order function to find highest order
  poly1->current = poly1->head;
  for(int i =0; i < order; i++) // for loop from 0 to order in increments of 1
  {
      poly1->current = poly1->current->next; // sets current to next value
  }
  highCoeff = poly1->current->d.coefficient; // stores coefficient
  poly1->current = poly1->head;
  norm = divide(poly1, highCoeff); // calls dividing function
  return norm; // returns coefficient of highest order 
}

int polyOrder(polyList *poly1)
{
  int length; // variable to store highest order in polyList
  poly1->current = poly1->head;
  for(int i=0; i <= (poly1->order); i ++) // for loop from 0 to length of polylist 
  {
      if(poly1->current->d.coefficient !=0) // if poly1's coefficient is not equal to 0 
      {
	  length = i; // length is highest order that is not equal to 0
      } 
      poly1->current = poly1->current->next; // sets current to next value
  }
  poly1->current = poly1->head;
  return length; // returns most significant order
}
