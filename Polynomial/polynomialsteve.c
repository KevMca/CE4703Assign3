//polynomialsteve.c
//author: Stephen Gannon
//date: 25/11/19
//purpose: multiply and divde functions

//#include <stdlib.h>
//#include <stdio.h>
#include "polynomial.h"

/*int main()
{
	double arr[] = {6, 0, 2};
	polyList *polyT;
	polyT = polyCreate();
	fillPoly(polyT, 2, arr);
	polyList *polyM = multiply(polyT, 3);
	polyList *polyD = divide(polyT, 2);
	return 0;
}*/

///////////////////////////////////////////////////////
// polyMultiply(poly1, multiplier)
// multiplies a polynomial by a double
//
// parameters:  poly1 - pointer for the polynomial
//              multiplier - number that multiplies the polynomial
// return: polynomial that was multiplied
///////////////////////////////////////////////////////

//uses a for loop to move through the link list and 
//multiply each coefficient by a double value
polyList *polyMultiply(polyList *poly1, double multiplier)
{
	polyList *polyMul; //creates a new polynomial to use for multiplication
	polyMul = polyCreate();
	int ord = polyOrder(poly1); //int ord is assigned the value of the order of the polynomial
	//Assign head first
	polyMul->current = polyMul->head;
	polyMul->current->d.order = 0;
	polyMul->current->d.coefficient = 
                        (poly1->current->d.coefficient) * (multiplier);
	
	//Assign the remaining coefficients
	for(int i = 1; i <= ord; i++)
	{	
		//create new node and move to that node
		polyMul->current->next = newCoeff(0, i);
		polyMul->current = polyMul->current->next;
		
		//value of current coefficient is multiped 
                //by the double and stored in the new polynomial
		polyMul->current->d.coefficient = 
			(poly1->current->d.coefficient) * (multiplier);
	}
	return polyMul; //returns the multipied polynomial
}
//////////////////////////////////////////////////////
// polyDivide(poly1, divider)
// divides a polynomial by a double
//
// parameters:  poly1 - pointer for the polynomial
//              divider - number that divides the polynomial
// return: polynomial that was divided
///////////////////////////////////////////////////////

//uses a for loop to move through the link list and divide each coefficient by a double value
polyList *polyDivide(polyList *poly1, double divider)
{
	polyList *polyDiv; //creates a new polynomial to use for division
	polyDiv = polyCreate();
	int ord = polyOrder(poly1); //int ord is assigned the value of the order of the polynomial
	//Assign head first
	polyDiv->current = polyDiv->head;
	polyDiv->current->d.order = 0;
	polyDiv->current->d.coefficient = 
		(poly1->current->d.coefficient) / (divider);
	//Assign the remaining coefficients
	for(int i = 1; i <= ord; i++)
	{	
		//create new node and move to that node
                polyDiv->current->next = newCoeff(0, i);
                polyDiv->current = polyDiv->current->next;
                
                //value of current coefficient is multiped 
                //by the double and stored in the new polynomial
                polyDiv->current->d.coefficient = 
                        (poly1->current->d.coefficient) / (divider);
	}
	return polyDiv; //returns the divided polynomial 
}
