//polynomial.h
//author: Stephen Gannon
//date: 25/11/19
//purpose: To declare all functions and data structures

#include <stdlib.h>
#include <stdio.h> 

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

typedef struct
{
  	double coefficient; // Coefficient for order
  	int order; // Order of coefficient in polynomial
} polyData;

typedef struct n
{
  	polyData d; // Coefficient and order
  	struct n *next; // Next coefficient
} polyNode;


typedef struct
{
  	polyNode *head; // Head of the polynomial
  	polyNode *current; // Current node cursor
} polyList;

typedef enum {ok, memoryErr, nodeErr, nullPoly} polyError;

// Polynomial editing functions
// Creates an empty polynomial
polyList *polyCreate();
// Moves current cursor to head
polyError polyToHead(polyList *poly);
// Moves current cursor to tail
polyError polyToTail(polyList *poly);
// Moves current cursor to end
polyError polyToEnd(polyList *poly);
// Increment the cursor by a number of steps
polyError polyIncrement(polyList *poly, int steps);
// Fills a polynomial with coefficients
polyError fillPoly(polyList *poly, int order, double arr[]);
// Adds a coefficient to a polynomial
polyNode *newCoeff(double coefficient, int order);
// Deletes a polynomial
polyError polyDelete(polyList *poly);
// Deletes a polynomial coefficient
polyError deleteNext(polyNode *current);

// Polynomial operations
// Adds two polynomials together
polyList *polyAdd(polyList *poly1, polyList *poly2);
// Subtracts 2 polynomials
polyList *polySubtract(polyList *poly1, polyList *poly2);
// Multiplies a polynomial by a doubles
polyList *polyMultiply(polyList *poly, double multiplyer);
// Divides a polynomial by a double
polyList *polyDivide(polyList *poly, double divider);
// Normalises a polynomial
polyList *polyNormalise(polyList *poly1);
// Returns the highest order of the polynomial
int polyOrder(polyList *poly1);
// Prints out the polynomial to stdout 
polyError polyPrint(polyList *poly1);

#endif
