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
#include <string.h>
#include "polynomial.h"

// Enum for either PASSED or FAILED
typedef enum {PASSED, FAILED} result;

// Test functions that test each individual function
result testPolyCreate();
result testPolyToHead();
result testPolyToEnd();
result testFillPoly();
result testNewCoeff();
result testDeleteNext();
result testPolyDelete();

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
  	// polynomial functions
  	/////////////////////////////////////////////////////////
	
	// Test polyCreate //////////////////////////////////////
	test("poly1 was not NULL", 
		"poly1 was NULL", 
		"polyCreate()", 
		testPolyCreate);

	// Test polyToHead //////////////////////////////////////
	test("current cursor moved to head", 
		"current cursor didn't move to head", 
		"polyToHead()", 
		testPolyToHead);

	// Test polyToEnd //////////////////////////////////////
	test("current cursor moved to end", 
		"current cursor didn't move to end", 
		"polyToEnd()", 
		testPolyToEnd);

	// Test fillPoly ////////////////////////////////////////
	test("all coefficients were correct", 
		"at least one coefficient was incorrect", 
		"fillPoly()", 
		testFillPoly);

	// Test newCoeff ////////////////////////////////////////
	test("end coefficient and order was correct", 
		"end coefficient or order was incorrect", 
		"newCoeff()", 
		testNewCoeff);

	// Test deleteNext //////////////////////////////////////
	test("deleted with no errors", 
		"returned node error", 
		"deleteNext()", 
		testDeleteNext);

	// Test polyDelete //////////////////////////////////////
	test("deleted with no errors", 
		"returned node error", 
		"polyDelete()", 
		testPolyDelete);

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
// Test polyToHead
/////////////////////////////////////////////////////////
result testPolyToHead()
{
	// Create new polynomial and add node
	polyList *poly1 = polyCreate();
	poly1->current->next = newCoeff(0, 1);

	// Increment current to see if it will return to head
	poly1->current = poly1->current->next;

	// Run polyToHead
	polyToHead(poly1);

	if(poly1->current == poly1->head)
	{
		// Successfully moved current cursor to head
		free(poly1);
		return PASSED;
	}

	// Current cursor is not the same as head
	free(poly1);
	return FAILED;
}

/////////////////////////////////////////////////////////
// Test polyToEnd
/////////////////////////////////////////////////////////
result testPolyToEnd()
{
	// Create new polynomial and add node
	polyList *poly1 = polyCreate();
	poly1->current->next = newCoeff(0, 1);

	// Run polyToHead
	polyToEnd(poly1);

	if(poly1->current == poly1->head->next)
	{
		// Successfully moved current cursor to end
		free(poly1);
		return PASSED;
	}

	// Current cursor is not the same as end
	free(poly1);
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

/////////////////////////////////////////////////////////
// Test deleteNext
/////////////////////////////////////////////////////////
result testDeleteNext()
{
	// Create new polynomial and add node
	polyList *poly1 = polyCreate();
	poly1->current->next = newCoeff(0, 1);

	// Delete new node
	if(deleteNext(poly1->current) == ok)
	{
		// Deleted next node without any errors
		free(poly1);
		return PASSED;
	}

	// Returned a node error
	free(poly1);
	return FAILED;
}

/////////////////////////////////////////////////////////
// Test polyDelete
/////////////////////////////////////////////////////////
result testPolyDelete()
{
	// Create new polynomial and add node
	polyList *poly1 = polyCreate();
	poly1->current->next = newCoeff(0, 1);

	// Delete polynomial
	if(polyDelete(poly1) == ok)
	{
		// Deleted polynomial without any errors
		return PASSED;
	}

	// Returned a node error
	return FAILED;
}
