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

//////////////////////////////////////////////////
// function main()
// entry point from operating system. Defines 
// the main application of this program. Runs a
// series of calculations and prints thems
//////////////////////////////////////////////////
int main(int argc, char **argv)
{
	int passed = 0;
  	/////////////////////////////////////////////////////////
  	// polynomial create and delete
  	/////////////////////////////////////////////////////////
	
	// Test polyCreate //////////////////////////////////////
	passed = 0;

	polyList *poly1 = polyCreate();
	
	// If next node from head is NULL it probably created properly
	if(poly1->head->next == NULL)
	{
		passed = 1;
	}
	if(passed == 1)
		printf("\npoly1->head->next intitialised to NULL\n"
			"polyCreate() PASSED\n");
	else
		printf("\npoly1->head->next not intitialised to NULL\n"
			"polyCreate() FAILED, check implementation\n");

	// Test fillPoly ////////////////////////////////////////
	passed = 0;

	double arrFill[] = {0, 1, 2, 3};
	fillPoly(poly1, 3, arrFill);
	
	// Reset the current cursor to be able to test
	poly1->current = poly1->head;
	// Test if each coefficient is correct
	for(int i = 0; i <= 3; i++)
	{
		if(poly1->current->d.coefficient == arrFill[i] 
			&& poly1->current->d.order == i)
		{
			passed = 1;
			poly1->current = poly1->current->next;
		}
		else
		{
			passed = 0;
			break;
		}
	}
	if(passed == 1)
		printf("\nAll coefficients are correct\n"
			"fillyPoly() PASSED\n");
	else
		printf("\nNot all coefficients are correct\n"
			"fillyPoly() FAILED, check implementation\n");


	// Test new coeff
	//newCoeff()
	//polyDelete()
	//deleteNext()

	/////////////////////////////////////////////////////////
  	// polynomial operations
  	/////////////////////////////////////////////////////////
  	//polyAdd()
  	//polySubtract()
  	//multiply()
  	//divide()
  	//polyNormalise()
  	//polyOrder()
}
