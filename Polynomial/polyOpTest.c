/////////////////////////////////////////////////////////
// polyOpTest.c
//
// main test program for testing Polynomial operations
// that add, subtract, multiply, divide, normalise and
// find order
//
// author:      kevin mcandrew
// date:        28.11.2019
/////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

// Enum for either PASSED or FAILED
typedef enum {PASSED, FAILED} result;

// Test functions that test each individual function
result testPolyAdd();
result testPolySubtract();
result testPolyMultiply();
result testPolyDivide();
result testPolyNormalise();
result testPolyOrder();
result testPolyPrint();

// Custom general unit testing that takes reasons for passing or failing,
// the function name and a pointer to the function to run
void test(char *passReason, char *failReason, char *funcName, result (*f)(void))
{
	if((*f)() == PASSED)
	{
		printf("\n%s\n", passReason);
		printf("%s PASSED\n", funcName);
	}
	else
	{
		printf("\n%s\n", failReason);
		printf("%s FAILED, check implementation\n", funcName);
	}
}

//////////////////////////////////////////////////
// function main()
// entry point from operating system. Defines 
// the main application of this program. Runs a
// series of calculations and prints thems
//////////////////////////////////////////////////
int main(int argc, char **argv)
{
	/////////////////////////////////////////////////////////
  	// polynomial operations
  	/////////////////////////////////////////////////////////
  	
  	// Test polyAdd /////////////////////////////////////////
  	test("all coefficients and order were as expected", 
		"a coefficient or order wasn't as expected", 
		"polyAdd()", 
		testPolyAdd);

  	// Test polySubtract ////////////////////////////////////
  	test("all coefficients and order were as expected", 
		"a coefficient or order wasn't as expected", 
		"polySubtract()", 
		testPolySubtract);

  	// Test polyMultiply ////////////////////////////////////
  	test("all coefficients and order were as expected", 
		"a coefficient or order wasn't as expected", 
		"polyMultiply()", 
		testPolyMultiply);
  	
	// Test polyDivide //////////////////////////////////////
  	test("all coefficients and order were as expected", 
		"a coefficient or order wasn't as expected", 
		"polyDivide()", 
		testPolyDivide);

  	// Test polyNormalise ///////////////////////////////////
  	test("all coefficients and order were as expected", 
		"a coefficient or order wasn't as expected", 
		"polyNormalise()", 
		testPolyNormalise);

  	// Test polyOrder ///////////////////////////////////////
  	test("returned correct order", 
		"order was not as expected", 
		"polyOrder()", 
		testPolyOrder);

  	//Print new line for formatting
  	printf("\n");

  	// Test polyPrint ///////////////////////////////////////
  	test("no error returned", 
		"some error returned", 
		"polyPrint()", 
		testPolyPrint);

  	//Print new line for formatting
  	printf("\n");
}

/////////////////////////////////////////////////////////
// Test polyAdd
// Inputs:
// poly1 = 0 1 2 3 
// poly2 = 3 2 1 0
// Expected Result: 3 3 3 3
/////////////////////////////////////////////////////////
result testPolyAdd()
{
	// Create polynomials
	polyList *poly1 = polyCreate();
	polyList *poly2 = polyCreate();
	polyList *poly3 = polyCreate();
	// Create arr to fill polynomials
	double arrFill1[] = {0, 1, 2, 3};
	double arrFill2[] = {3, 2, 1, 0};
	int order = 3;
	// Fill arrrays
	fillPoly(poly1, order, arrFill1);
	fillPoly(poly2, order, arrFill2);

	// Run polyAdd
	poly3 = polyAdd(poly1, poly2);

	// Reset current cursor
	polyToHead(poly1);
	polyToHead(poly2);
	polyToHead(poly3);
	// Check each coefficient and order
	for(int i = 0; i <=order; i++)
	{
		if(poly3->current->d.coefficient != arrFill1[i] + arrFill2[i]
			|| poly3->current->d.order != i)
		{
			// Print current iteration, order and coefficient
			printf("\niter: %d\norder:%d\ncoefficient:%lf", i, 
				poly3->current->d.order, poly3->current->d.coefficient);
			// Coefficient not as expected
			polyDelete(poly1);
			polyDelete(poly2);
			polyDelete(poly3);
			return FAILED;
		}
		// Increment current cursors
		poly3->current = poly3->current->next;
		poly2->current = poly2->current->next;
		poly1->current = poly1->current->next;
	}

	// All coefficients were as expected
	polyDelete(poly1);
	polyDelete(poly2);
	polyDelete(poly3);
	return PASSED;
}

/////////////////////////////////////////////////////////
// Test polySubtract
// Inputs:
// poly1 = 0 1 2 3 
// poly2 = 3 2 1 0
// Expected Result: -3 -1 1 3
/////////////////////////////////////////////////////////
result testPolySubtract()
{
	// Create polynomials
	polyList *poly1 = polyCreate();
	polyList *poly2 = polyCreate();
	polyList *poly3 = polyCreate();
	// Create arr to fill polynomials
	double arrFill1[] = {0, 1, 2, 3};
	double arrFill2[] = {3, 2, 1, 0};
	int order = 3;
	// Fill arrrays
	fillPoly(poly1, order, arrFill1);
	fillPoly(poly2, order, arrFill2);

	// Run polyAdd
	poly3 = polySubtract(poly1, poly2);

	// Reset current cursor
	polyToHead(poly1);
	polyToHead(poly2);
	polyToHead(poly3);
	// Check each coefficient and order
	for(int i = 0; i <=order; i++)
	{
		if(poly3->current->d.coefficient != arrFill1[i] - arrFill2[i]
			|| poly3->current->d.order != i)
		{
			// Print current iteration, order and coefficient
			printf("\niter: %d\norder:%d\ncoefficient:%lf", i, 
				poly3->current->d.order, poly3->current->d.coefficient);
			// Coefficient not as expected
			polyDelete(poly1);
			polyDelete(poly2);
			polyDelete(poly3);
			return FAILED;
		}
		// Increment current cursors
		poly3->current = poly3->current->next;
		poly2->current = poly2->current->next;
		poly1->current = poly1->current->next;
	}

	// All coefficients were as expected
	polyDelete(poly1);
	polyDelete(poly2);
	polyDelete(poly3);
	return PASSED;
}

/////////////////////////////////////////////////////////
// Test polyMultiply
// Inputs:
// poly1 = 0 1 2 3
// multiplier = 2
// Expected Result: 0 2 4 3
/////////////////////////////////////////////////////////
result testPolyMultiply()
{
	// Create polynomials
	polyList *poly1 = polyCreate();
	polyList *poly2 = polyCreate();
	// Create arr to fill polynomials
	double arrFill1[] = {0, 1, 2, 3};
	int order = 3;
	// Fill arrrays
	fillPoly(poly1, order, arrFill1);

	// Run polyAdd
	poly2 = polyMultiply(poly1, 2);

	// Reset current cursor
	polyToHead(poly1);
	polyToHead(poly2);
	// Check each coefficient and order
	for(int i = 0; i <=order; i++)
	{
		if(poly2->current->d.coefficient != arrFill1[i] * 2
			|| poly2->current->d.order != i)
		{
			// Print current iteration, order and coefficient
			printf("\niter: %d\norder:%d\ncoefficient:%lf", i, 
				poly2->current->d.order, poly2->current->d.coefficient);
			// Coefficient not as expected
			polyDelete(poly1);
			polyDelete(poly2);
			return FAILED;
		}
		// Increment current cursors
		poly2->current = poly2->current->next;
		poly1->current = poly1->current->next;
	}

	// All coefficients were as expected
	polyDelete(poly1);
	polyDelete(poly2);
	return PASSED;
}

/////////////////////////////////////////////////////////
// Test polyDivide
// Inputs:
// poly1 = 0 1 2 3 
// divider = 2
// Expected Result: 0 0.5 1 1.5
/////////////////////////////////////////////////////////
result testPolyDivide()
{
	// Create polynomials
	polyList *poly1 = polyCreate();
	polyList *poly2 = polyCreate();
	// Create arr to fill polynomials
	double arrFill1[] = {0, 1, 2, 3};
	int order = 3;
	// Fill arrrays
	fillPoly(poly1, order, arrFill1);

	// Run polyAdd
	poly2 = polyDivide(poly1, 2);

	// Reset current cursor
	polyToHead(poly1);
	polyToHead(poly2);
	// Check each coefficient and order
	for(int i = 0; i <=order; i++)
	{
		if(poly2->current->d.coefficient != arrFill1[i] / 2
			|| poly2->current->d.order != i)
		{
			// Print current iteration, order and coefficient
			printf("\niter: %d\norder:%d\ncoefficient:%lf", i, 
				poly2->current->d.order, poly2->current->d.coefficient);
			// Coefficient not as expected
			polyDelete(poly1);
			polyDelete(poly2);
			return FAILED;
		}
		// Increment current cursors
		poly2->current = poly2->current->next;
		poly1->current = poly1->current->next;
	}

	// All coefficients were as expected
	polyDelete(poly1);
	polyDelete(poly2);
	return PASSED;
}

/////////////////////////////////////////////////////////
// Test polyNormalise
// Input: 0 1 2 3
// Expected Result: 0 .33 .66 1
/////////////////////////////////////////////////////////
result testPolyNormalise()
{
	// Create polynomials
	polyList *poly1 = polyCreate();
	polyList *poly2 = polyCreate();
	// Create arr to fill polynomials
	double arrFill1[] = {0, 1, 2, 3};
	int order = 3;
	// Fill arrrays
	fillPoly(poly1, order, arrFill1);

	// Run polyAdd
	poly2 = polyNormalise(poly1);

	// Reset current cursor
	polyToHead(poly1);
	// Check each coefficient and order
	for(int i = 0; i <=order; i++)
	{
		if(poly2->current->d.coefficient != arrFill1[i] / 3
			|| poly2->current->d.order != i)
		{
			// Print current iteration, order and coefficient
			printf("\niter: %d\norder:%d\ncoefficient:%lf", i, 
				poly2->current->d.order, poly2->current->d.coefficient);
			// Coefficient not as expected
			polyDelete(poly1);
			polyDelete(poly2);
			return FAILED;
		}
		// Increment current cursors
		poly2->current = poly2->current->next;
		poly1->current = poly1->current->next;
	}

	// All coefficients were as expected
	polyDelete(poly1);
	polyDelete(poly2);
	return PASSED;
}

/////////////////////////////////////////////////////////
// Test polyOrder
// Input: 0 1 2 3
// Expected Result: 3
/////////////////////////////////////////////////////////
result testPolyOrder()
{
	// Create polynomials
	polyList *poly1 = polyCreate();
	// Create arr to fill polynomials
	double arrFill1[] = {0, 1, 2, 3};
	int order = 3;
	// Fill arrrays
	fillPoly(poly1, order, arrFill1);

	// Run polyAdd
	int returnedOrder = polyOrder(poly1);

	if(returnedOrder == order)
	{
		// Returned correct order
		polyDelete(poly1);
		return PASSED;
	}

	// Returned incorrect order
	polyDelete(poly1);
	return FAILED;
}

/////////////////////////////////////////////////////////
// Test polyPrint
// Input: 0 1 2 3
// Expected Result: "0.000 + 1.000x^1 + 2.000x^2 + 3.000x^3"
/////////////////////////////////////////////////////////
result testPolyPrint()
{
	// Create polynomials
	polyList *poly1 = polyCreate();
	// Create arr to fill polynomials
	double arrFill1[] = {0, 1, 2, 3};
	int order = 3;
	// Fill arrrays
	fillPoly(poly1, order, arrFill1);

	if(polyPrint(poly1) == ok)
	{
		// No error returned
		polyDelete(poly1);
		return PASSED;
	}

	// There was an error
	polyDelete(poly1);
	return FAILED;
}
