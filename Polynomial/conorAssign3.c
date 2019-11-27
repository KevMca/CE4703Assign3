// conorAssign3

#include <stdlib.h>
#include <stdio.h>
#include "polynomial.h"

int main()
{
  double arr1[] = {2, 2, 2, 2};
  double arr2[] = {3, 0, 8, 0, 9, 0};
  polyList *poly1;
  polyList *poly2;
  polyList *polyA;
  polyList *polyS;
  poly1 = polyCreate();
  poly2 = polyCreate();
  fillPoly(poly1, 3, arr1);
  fillPoly(poly2, 5, arr2);
  polyA = polyAdd(poly1, poly2);
  polyS = polySubtract(poly1, poly2);
  polyA->current = polyA->current->next;
  polyA->current = polyA->current->next;
  polyA->current = polyA->current->next;
  polyA->current = polyA->current->next;
  printf("add = %lf\n", polyA->current->d.coefficient);
  printf("sub = %lf\n", polyS->head->d.coefficient);
}

/*
  function add: adds two polynomials together

  parameters: 
  poly1: pointer for the first polynomial to added 
  poly2: pointer for the second polynomial to be added

  return:
  poly3: sum of poly1 and poly2
 */
polyList *polyAdd(polyList *poly1, polyList *poly2)
{
  polyList *poly3; // declares a polynomial
  poly3 = polyCreate(); // creates an empty polynomial
  int smallOrd, bigOrd, whichOrd;
  // checks which polynomial has a higher order
  // assigns variables for each order
  if(polyOrder(poly1) > polyOrder(poly2))
  {
    whichOrd = 1;
    smallOrd = polyOrder(poly2);
    bigOrd = polyOrder(poly1);
  }
  else
  {
    smallOrd = polyOrder(poly1);
    bigOrd = polyOrder(poly2);
  }

  // reset current cursors
  poly1->current = poly1->head;
  poly2->current = poly2->head;
  poly3->current = poly3->head;

  // adds each coefficient of the polynomials to each other until one runs out of coefficients
  for(int i = 0; i <= smallOrd; i++)
  {
    poly3->current->d.coefficient = poly1->current->d.coefficient + poly2->current->d.coefficient;
    poly1->current = poly1->current->next;
    poly2->current = poly2->current->next;
    poly3->current->next = newCoeff(0, i);
    poly3->current = poly3->current->next;
  }

  // checks which polynomial has the higher order then assigns the rest of its terms to poly3
  if(whichOrd == 1)
  {
    for(int i = smallOrd + 1; i < bigOrd; i++)
    {
      poly3->current->d.coefficient = poly1->current->d.coefficient;
      poly1->current = poly1->current->next;
      poly3->current->next = newCoeff(0, i);
      poly3->current = poly3->current->next;
    }
    poly3->current->d.coefficient = poly1->current->d.coefficient; // final assign, doesn't make a new node
  }
  else
  {
    for(int i = smallOrd + 1; i < bigOrd; i++)
    {
      poly3->current->d.coefficient = poly2->current->d.coefficient;
      poly2->current = poly2->current->next;
      poly3->current->next = newCoeff(0, i);
      poly3->current = poly3->current->next;
    }
    poly3->current->d.coefficient = poly2->current->d.coefficient;
    printf("%lf\n", poly2->current->d.order);
  }

  // reset current cursor to head
  poly3->current = poly3->head;
  return poly3;
}

/*
  function subract: subtracts a polynomial from another

  parameters:
  poly1: the minuend polynomial
  poly2: the subtrahend polynomial

  return:
  poly3: poly1 - poly2
 */
polyList *polySubtract(polyList *poly1, polyList *poly2)
{
  polyList *poly3;
  poly3 = polyCreate(); // creates an empty polynomial
  int smallOrd, bigOrd, whichOrd;
  // checks which polynomial has the higher order
  if(polyOrder(poly1) > polyOrder(poly2))
  {
    whichOrd = 1;
    smallOrd = polyOrder(poly2);
    bigOrd = polyOrder(poly1);
  }
  else
  {
    smallOrd = polyOrder(poly1);
    bigOrd = polyOrder(poly2);
  }

  // subracts poly2 from poly1 until one runs out of coefficients
  for(int i = 0; i <= smallOrd; i++)
  {
    poly3->current->d.coefficient = poly1->current->d.coefficient - poly2->current->d.coefficient;
    poly1->current = poly1->current->next;
    poly2->current = poly2->current->next;
    poly3->current->next = newCoeff(0, i);
    poly3->current = poly3->current->next;
  }

  // checks which polynomial has the higher order
  // if the minuend has a higher order, its remaining elements are assigned to poly3
  // if the subtrahend has a higher order, the inverse of its remaining elements are assigned to poly3
  if(whichOrd == 1)
  {
    for(int i = smallOrd + 1; i < bigOrd; i++)
    {
      poly3->current->d.coefficient = poly1->current->d.coefficient;
      poly1->current = poly1->current->next;
      poly3->current->next = newCoeff(0, i);
      poly3->current = poly3->current->next;
    }
    poly3->current->d.coefficient = poly1->current->d.coefficient;
  }
  else
  {
    for(int i = smallOrd + 1; i < bigOrd; i++)
    {
      poly3->current->d.coefficient = 0 - poly2->current->d.coefficient;
      poly2->current = poly2->current->next;
      poly3->current->next = newCoeff(0, i);
      poly3->current = poly3->current->next;
    }
    poly3->current->d.coefficient = 0 - poly2->current->d.coefficient;
  }

  // reset current cursor to head
  poly3->current = poly3->head;
  return poly3;
}
