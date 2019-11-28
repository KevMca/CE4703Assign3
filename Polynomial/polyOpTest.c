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
  	test("poly1 was not NULL", 
		"poly1 was NULL", 
		"polyCreate()", 
		testPolyAdd);
  	//polyAdd()
  	//polySubtract()
  	//multiply()
  	
	// Test divide //////////////////////////////////////////
  	/*passed = 0;

  	// Test dividing by 2
  	polyList *polyD = polyDivide(poly1, 2);

  	// Reset current cursor to head
  	polyD->current = polyD->head;
  	for(int i = 0; i <= 3; i++)
	{
		if(polyD->current->d.coefficient == arrFill[i]/2 
			&& polyD->current->d.order == i)
		{
			passed = 1;
			polyD->current = polyD->current->next;
		}
		else
		{
			passed = 0;
			//break;
		}
	}
	if(passed == 1)
		printf("\nAll coefficients are correct\n"
			"polyDivide() PASSED\n");
	else
		printf("\nNot all coefficients are correct\n"
			"polyDivide() FAILED, check implementation\n");*/
  	//polyNormalise()
  	//polyOrder()

  	//Print new line for formatting
  	printf("\n");
}

/////////////////////////////////////////////////////////
// Test polyAdd
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
			// Coefficient not as expected
			free(poly1);
			free(poly2);
			free(poly3);
			return FAILED;
		}
		// Increment current cursors
		poly3->current = poly3->current->next;
		poly2->current = poly2->current->next;
		poly1->current = poly1->current->next;
	}

	// All coefficients were as expected
	free(poly1);
	free(poly2);
	free(poly3);
	return PASSED;
}
