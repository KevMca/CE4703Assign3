//polynomialsteve.c
//author: Stephen Gannon
//date: 25/11/19
//purpose: multiply and divde functions

#include <stdlib.h>
#include <stdio.h>
#include "polynomial.h"


//uses a for loop to move through the link list and multiply each coefficient by a double value
polyList multiply(polyList *poly, double multiplyer)
{
	polyList polyMul; //creates a new polynomial to use for multiplication
	int ord = order(poly); //int ord is assigned the value of the order of the polynomial
	for(int i = 0; i <= ord; i++)
	{	
		//value of current coefficient is multiped by the double and stored in the new 			polynomial
		polyMul.current->d.coefficient = *poly->current->d.coefficient*multiplyer;
		addNode(...);
		polyMul.current = polyMul.current->next; //moves the current to the next coefficient  
	}
	return polyMul; //returns the multipied polynomial
}

//uses a for loop to move through the link list and divide each coefficient by a double value
polyList divide(polyList *poly, double divider)
{
	polyList polyDiv; //creates a new polynomial to use for division
	int ord = order(poly); //int ord is assigned the value of the order of the polynomial
	for(int i = 0; i <= ord; i++)
	{	
		//value of current coefficient is divided by the double and stored in the new 			polynomial
		polyDiv.current->d.coefficient = *poly->current->d.coefficient/divider;
		addNode(...);
		polyDiv.current = polyDiv.current->next; //moves the current to the next coefficient
	}
	return polyDiv; //returns the divided polynomial 
}
