//polynomialsteve.c
//author: Stephen Gannon
//date: 25/11/19
//purpose: multiply and divde functions

#include <stdlib.h>
#include <stdio.h>
#include "polynomial.h"

polyList multiply(polyList *poly, double multiplyer)
{
	polyList polyMul;
	int ord = order(&poly)
	for(int i = 0; i <= ord; i++)
	{
		polyMul.current->d.coefficient = *poly->current->d.coefficient*multiplyer;
		addNode(...);
		polyMul.current = polyMul.current->next;
		return polyMul;
	}

}

polyList divide(polyList *poly, double divider)
{
	polyList polyDiv;
	int ord = order(&poly)
	for(int i = 0; i <= ord; i++)
	{
		polyDiv.current->d.coefficient = *poly->current->d.coefficient/divider;
		addNode(...);
		polyDiv.current = polyDiv.current->next;
		return poly3;
	}

}
