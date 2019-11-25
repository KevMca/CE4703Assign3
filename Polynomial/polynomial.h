//polynomial.h
//author: Stephen Gannon
//date: 25/11/19
//purpose: To declare all functions and data structures

#ifndef HEADER_FILEPOLY
#define HEADER_FILEPOLY

typedef struct
{
  	polyNode *head;
  	polyNode *current;
  	int order; //order of the coefficient
} polyList;

typedef struct
{
  	polyData d;
  	struct n *next
} polyNode;

typedef struct
{
  	double coefficient;
	int order;
} polyData;



polyList *create(polyList *poly1, order, double array()); //creates a polynomial

int addNode(); //adds a node to a polynomial

int deleteNode(); //deletes a polynomial

polyList add(polyList *poly1, polyList *poly2); //adds two polynomials together

polyList subtract(polyList *poly1, polyList *poly2); //subtracts 2 polynomials

polyList multiply(polyList *poly1, polyList *poly2); //multiplies 2 polynomials

polyList divide(polyList *poly1, polyList poly2); //divides 2 polynomials

polyList normalise(polyList *poly1); //normalises a polynomial

int order(polyList *poly1); //returns the highest order of the polynomial 

void print(polyList *poly1); //prints out the polynomial to stdout



#endif
