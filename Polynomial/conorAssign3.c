// conorAssign3


#include "polynomial.h"

/*
  function add: adds two polynomials together

  parameters: 
  poly1: pointer for the first polynomial to added 
  poly2: pointer for the second polynomial to be added

  return:
  poly3: sum of poly1 and poly2
 */
polyList add(polyList *poly1, polyList *poly2){
  polyList *poly3; // declares a polynomial
  poly3 = polyCreate(); // creates an empty polynomial
  // checks which polynomial has a higher order
  // assigns variables for each order
  if(order(poly1) > order(poly2)){
    int smallOrd = order(poly2);
    int bigOrd = order(poly1);
  }
  else{
    int smallOrd = order(poly1);
    int bigOrd = order(poly2);
  }

  // adds each coefficient of the polynomials to each other until one runs out of coefficients
  for(int i = 0; i <= smallOrd; i++){
    poly3.current->d.coefficient = *poly1->current->d.coefficient + *poly2->current->d.coefficient;
    poly1->current = poly1->current->next;
    poly2->current = poly2->current->next;
    poly3.current->next = newCoeff(0, i);
    poly3.current = poly3.current->next;
  }

  // checks which polynomial has the higher order then assigns the rest of its terms to poly3
  if(order(poly1) > order(poly2)){
    for(int i = smallOrd + 1; i < bigOrd; i++){
      poly3.current->d.coefficient = *poly1->current->d.coefficient;
      poly1->current = poly1->current->next;
      poly3.current->next = newCoeff(0, i);
      poly3.current = poly3.current->next;
    }
    poly3.current->d.coefficient = *poly1->current->d.coefficient // final assign, doesn't make a new node
  }
  else{
    for(int i = smallOrd + 1; i < bigOrd; i++){
      poly3.current->d.coefficient = *poly2->current->d.coefficient;
      poly2->current = poly2->current->next;
      poly3.current->next = newCoeff(0, i);
      poly3.current = poly3.current->next;
    }
    poly3.current->d.coefficient = *poly2->current->d.coefficient;
  }

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
polyList subtract(polyList *poly1, polyList *poly2){
  polyList *poly3;
  poly3 = polyCreate(); // se
  // checks which polynomial has the higher order
  if(order(poly1) > order(poly2)){
    int smallOrd = order(poly2);
    int bigOrd = order(poly1);
  }
  else{
    int smallOrd = order(poly1);
    int bigOrd = order(poly2);
  }

  // subracts poly2 from poly1 until one runs out of coefficients
  for(int i = 0; i <= smallOrd; i++){
    poly3.current->d.coefficient = *poly1->current->d.coefficient - *poly2->current->d.coefficient;
    poly1->current = poly1->current->next;
    poly2->current = poly2->current->next;
    poly3.current->next = newCoeff(0, i);
    poly3.current = poly3.current->next;
  }

  // checks which polynomial has the higher order
  // if the minuend has a higher order, its remaining elements are assigned to poly3
  // if the subtrahend has a higher order, the inverse of its remaining elements are assigned to poly3
  if(order(poly1) > order(poly2)){
    for(int i = smallOrd + 1; i < bigOrd; i++){
      poly3.current->d.coefficient = *poly1->current->d.coefficient;
      poly1->current = poly1->current->next;
      poly3.current->next = newCoeff(0, i);
      poly3.current = poly3.current->next;
    }
    poly3.current->d.coefficient = *poly1->current->d.coefficient;
  }
  else{
    for(int i = smallOrd + 1; i < bigOrd; i++){
      poly3.current->d.coefficient = 0 - *poly2->current->d.coefficient;
      poly2->current = poly2->current->next;
      poly3.current->next = newCoeff(0, i);
      poly3.current = poly3.current->next;
    }
    poly3.current->d.coefficient = 0 - *poly2->current->d.coefficient;
  }
  return poly3;
}
