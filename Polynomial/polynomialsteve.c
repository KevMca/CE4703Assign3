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

//uses a for loop to move through the link list and 
//multiply each coefficient by a double value
polyList *multiply(polyList *poly, double multiplyer)
{
	polyList *polyMul; //creates a new polynomial to use for multiplication
	polyMul = polyCreate();
	int ord = polyOrder(poly); //int ord is assigned the value of the order of the polynomial
	//Assign head first
	polyMul->current = polyMul->head;
	polyMul->current->d.order = 0;
	polyMul->current->d.coefficient = 
                        (poly->current->d.coefficient) * (multiplyer);
	
	//Assign the remaining coefficients
	for(int i = 1; i <= ord; i++)
	{	
		//create new node and move to that node
		polyMul->current->next = newCoeff(0, i);
		polyMul->current = polyMul->current->next;
		
		//value of current coefficient is multiped 
                //by the double and stored in the new polynomial
		polyMul->current->d.coefficient = 
			(poly->current->d.coefficient) * (multiplyer);
	}
	return polyMul; //returns the multipied polynomial
}

//uses a for loop to move through the link list and divide each coefficient by a double value
polyList *divide(polyList *poly, double divider)
{
	polyList *polyDiv; //creates a new polynomial to use for division
	polyDiv = polyCreate();
	int ord = polyOrder(poly); //int ord is assigned the value of the order of the polynomial
	//Assign head first
	polyDiv->current = polyDiv->head;
	polyDiv->current->d.order = 0;
	polyDiv->current->d.coefficient = 
		(poly->current->d.coefficient) / (divider);
	//Assign the remaining coefficients
	for(int i = 1; i <= ord; i++)
	{	
		//create new node and move to that node
                polyDiv->current->next = newCoeff(0, i);
                polyDiv->current = polyDiv->current->next;
                
                //value of current coefficient is multiped 
                //by the double and stored in the new polynomial
                polyDiv->current->d.coefficient = 
                        (poly->current->d.coefficient) / (divider);
	}
	return polyDiv; //returns the divided polynomial 
}
