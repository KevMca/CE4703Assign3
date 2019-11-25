//polynomial.h
//author: Stephen Gannon
//date: 25/11/19
//purpose: To declare all functions and data structures

#ifndef HEADER_FILEPOLY
#define HEADER_FILEPOLY

typedef struct
{
  	double coefficient; // Coefficient for order
	int order; // Position in polynomial (x^order)
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
  	int order; // Order of the coefficient
} polyList;

// Polynomial editing operation
// Creates an empty polynomial
polyList *polyCreate();
// Fills a polynomial with coefficients
int fillPoly(polyList *poly, int order, double arr[]);
// Adds a coefficient to a polynomial
polyNode *newCoeff(double coefficient, int order);
// Deletes a polynomial
int polyDelete(polyList *poly);
// Deletes a polynomial coefficient
int deleteNext(polyNode *current);

// Polynomial operations
// Adds two polynomials together
polyList add(polyList *poly1, polyList *poly2);
// Subtracts 2 polynomials
polyList subtract(polyList *poly1, polyList *poly2);
// Multiplies a polynomial by a doubles
polyList multiply(polyList *poly1);
// Divides a polynomial by a double
polyList divide(polyList *poly1);
// Normalises a polynomial
polyList normalise(polyList *poly1);
// Returns the highest order of the polynomial
int order(polyList *poly1);
// Prints out the polynomial to stdout 
void print(polyList *poly1);

#endif
