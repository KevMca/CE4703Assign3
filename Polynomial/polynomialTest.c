/////////////////////////////////////////////////////////
// polynomialTest.c
//
// main test program for testing Polynomial module and its
// functions. Also gives example implementations to
// demonstrate how the module works
//
// author:      kevin mcandrew
// date:        27.11.2019
/////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

// Macros for printing if the function PASSED or FAILED
#define passPrint(FUNC) printf("%s PASSED\n", #FUNC)
#define failPrint(FUNC) printf("%s FAILED, check implementation\n", #FUNC)

typedef enum {PASSED, FAILED} result;

result testPolyCreate();
result testFillPoly();
result testNewCoeff();

//////////////////////////////////////////////////
// function main()
// entry point from operating system. Defines 
// the main application of this program. Runs a
// series of calculations and prints thems
//////////////////////////////////////////////////
int main(int argc, char **argv)
{
  	/////////////////////////////////////////////////////////
  	// polynomial create and delete
  	/////////////////////////////////////////////////////////
	
	// Test polyCreate //////////////////////////////////////
	if(testPolyCreate() == PASSED)
	{
		printf("\npoly1 was not NULL\n");
		passPrint(polyCreate());
	}
	else
	{
		printf("\npoly1 was NULL\n");
		failPrint(polyCreate());
	}

	// Test fillPoly ////////////////////////////////////////
	
	if(testFillPoly() == PASSED)
	{
		printf("\nall coefficients were correct\n");
		passPrint(fillPoly());
	}
	else
	{
		printf("\nat least one coefficient was incorrect\n");
		failPrint(fillPoly());
	}

	// Test newCoeff ////////////////////////////////////////
	
	if(testNewCoeff() == PASSED)
	{
		printf("\nend coefficient and order was correct\n");
		passPrint(newCoeff());
	}
	else
	{
		printf("\nend coefficient or order was incorrect\n");
		failPrint(newCoeff());
	}

	//polyDelete()
	//deleteNext()

	/////////////////////////////////////////////////////////
  	// polynomial operations
  	/////////////////////////////////////////////////////////
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
// Test polyCreate
/////////////////////////////////////////////////////////
result testPolyCreate()
{
	// Run polyCreate
	polyList *poly1 = polyCreate();
	
	// If next node from head is NULL it probably created properly
	if(poly1 != NULL)
	{
		// Free poly1
		polyDelete(poly1);
		return PASSED;
	}

	// Else poly1 was NULL and didn't assign properly
	return FAILED;
}

/////////////////////////////////////////////////////////
// Test fillPoly
/////////////////////////////////////////////////////////
result testFillPoly()
{
	// Create polynomial
	polyList *poly1 = polyCreate();
	// Create arr to fill polynomial
	double arrFill[] = {0, 1, 2, 3};
	int order = 3;

	// Run fillPoly
	fillPoly(poly1, order, arrFill);
	
	// Reset the current cursor to be able to test
	poly1->current = poly1->head;

	// Test if each coefficient and order is correct
	for(int i = 0; i <= order; i++)
	{
		if(poly1->current->d.coefficient == arrFill[i] 
			&& poly1->current->d.order == i)
		{
			// Increment current cursor
			poly1->current = poly1->current->next;
		}
		else
		{
			// Coefficient is incorrect
			free(poly1);
			return FAILED;
		}
	}

	// All coefficients were correct
	free(poly1);
	return PASSED;
}

/////////////////////////////////////////////////////////
// Test newCoeff
/////////////////////////////////////////////////////////
result testNewCoeff()
{
	// Create and fill new polynomial
	polyList *poly1 = polyCreate();
	// Create arr to fill polynomial
	double arrFill[] = {0, 1, 2, 3};
	int order = 3;
	fillPoly(poly1, order, arrFill);

	// Reset current pointer and move to the end
	polyToEnd(poly1);
	// Add new coefficient to the end
	poly1->current->next = newCoeff(4, order + 1);
	
	// Test if the new coefficient was added on the end
	polyToEnd(poly1);
	if(poly1->current->d.coefficient == 4
		&& poly1->current->d.order == order + 1)
	{
		// Coefficient and order of tail node were correct
		free(poly1);
		return PASSED;
	}

	// Either coefficient or order of tail were incorrect
	free(poly1);
	return FAILED;
}
