/////////////////////////////////////////////////////////
// polyFuncTest.c
//
// main test program for testing Polynomial functions for
// creating, deleting and modifying polynomials
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
result testPolyCreate();
result testPolyToHead();
result testPolyToTail();
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

	// Test polyToTail //////////////////////////////////////
	test("current cursor moved to tail", 
		"current cursor didn't move to tail", 
		"polyToTail()", 
		testPolyToTail);

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
		polyDelete(poly1);
		return PASSED;
	}

	// Current cursor is not the same as head
	polyDelete(poly1);
	return FAILED;
}

/////////////////////////////////////////////////////////
// Test polyToTail
/////////////////////////////////////////////////////////
result testPolyToTail()
{
	// Create new polynomial and add node
	polyList *poly1 = polyCreate();
	poly1->current->next = newCoeff(0, 1);

	// Run polyToEnd
	polyToTail(poly1);

	if(poly1->current == poly1->head->next)
	{
		// Successfully moved current cursor to end
		polyDelete(poly1);
		return PASSED;
	}

	// Current cursor is not the same as end
	polyDelete(poly1);
	return FAILED;
}

/////////////////////////////////////////////////////////
// Test polyToEnd
/////////////////////////////////////////////////////////
result testPolyToEnd()
{
	// Create new polynomial and add node
	polyList *poly1 = polyCreate();
	poly1->current->next = newCoeff(1, 1);
	poly1->current = poly1->current->next;
	poly1->current->next = newCoeff(0, 2);

	// Run polyToEnd
	polyToEnd(poly1);

	if(poly1->current == poly1->head->next)
	{
		// Successfully moved current cursor to end
		polyDelete(poly1);
		return PASSED;
	}

	// Current cursor is not the same as end
	printf("\n%d", polyOrder(poly1));
	polyDelete(poly1);
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
			polyDelete(poly1);
			return FAILED;
		}
	}

	// All coefficients were correct
	polyDelete(poly1);
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
	polyToTail(poly1);
	// Add new coefficient to the end
	poly1->current->next = newCoeff(4, order + 1);
	
	// Test if the new coefficient was added on the end
	polyToTail(poly1);
	if(poly1->current->d.coefficient == 4
		&& poly1->current->d.order == order + 1)
	{
		// Coefficient and order of tail node were correct
		polyDelete(poly1);
		return PASSED;
	}

	// Either coefficient or order of tail were incorrect
	polyDelete(poly1);
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
		polyDelete(poly1);
		return PASSED;
	}

	// Returned a node error
	polyDelete(poly1);
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
