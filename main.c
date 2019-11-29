////////////////////////////////////////////////////
// main.c
// Purpose: Contains a lovely interface for interacting
//          with polynomials
// Author: Conor Pesch
// Date: 29/11/2019
////////////////////////////////////////////////////

#include "Polynomial/polynomial.h"
#include <stdlib.h>
#include <stdio.h>

polyList *polyDeclare();
void polyPrintList(polyList *polyArray[], int polyArrayCounter);

////////////////////////////////////////////////////
// Name: main
// Purpose: creates interface and runs program
////////////////////////////////////////////////////

int main()
{
  int continueLoop = 1;
  polyList *polyArray[100];
  int polyArrayCounter = 0;

  int polyChoice1, polyChoice2;
  double constant;
  
  while(continueLoop)
    {
      int interfaceChoice;
      printf("\nPlease choose the number corresponding to the action you want:\n"
      	"  1.  DISPLAY polynomials\n"
      	"  2.  CREATE new polynomial\n"
      	"  3.  DELETE polynomial\n"
      	"  4.  ADD\n"
      	"  5.  SUBTRACT\n"
      	"  6.  MULTIPLY\n"
      	"  7.  DIVIDE\n"
      	"  8.  NORMALISE\n"
      	"  9.  ORDER\n"
      	"  10. EXIT\n\n");
      scanf("%i", &interfaceChoice);

      switch(interfaceChoice)
		{
		// displays all polynomials
		case 1:
			printf("\n");
		  	for(int i = 0; i < polyArrayCounter; i++)
		  	{
		  		printf("%d: ", i + 1);
		    	polyPrint(polyArray[i]);
		  	}
		  	break;
		  
		// creates a polynomial
		case 2:
		  	polyArray[polyArrayCounter] = polyDeclare();
		  	polyArrayCounter += 1;
		  	break;
		  
		// deletes a polynomial
		case 3:
		  	printf("\nPlease select a polynomial to delete\n\n");
		  	polyPrintList(polyArray, polyArrayCounter);
		  	printf("\n");
		  	scanf("%d",&polyChoice1);

		  	// Check if choice is valid
		  	if(polyChoice1 > polyArrayCounter || polyChoice1 < 1)
		  		break;

		  	// If valid, remove polynomial from list
		  	polyDelete(polyArray[polyChoice1 - 1]);

		  	// Move all later polynomials back
		  	for(int i = polyChoice1; i <= polyArrayCounter; i++)
		  	{
		  		polyArray[i - 1] = polyArray[i];
		  	}
		  	
		  	// Move array counter back
		  	polyArrayCounter -= 1;
		  	break;
		  
		// adds 2 polynomials
		case 4:
		  	printf("\nPlease select two polynomials to add together\n");
		  	polyPrintList(polyArray, polyArrayCounter);
		  	printf("\n");
		  	scanf("%d %d", &polyChoice1, &polyChoice2);
		  	polyArray[polyArrayCounter] = polyAdd(polyArray[polyChoice1 - 1], polyArray[polyChoice2 - 1]);
		  	polyPrint(polyArray[polyArrayCounter]);
		  	polyArrayCounter += 1;
		  	break;
		  
		// subtracts 2 polynomials
		case 5:
		  	printf("\nPlease select a polynomial to subract from another\n");
		  	polyPrintList(polyArray, polyArrayCounter);
		  	printf("\n");
		  	scanf("%d %d", &polyChoice1, &polyChoice2);
		  	polyArray[polyArrayCounter] = polySubtract(polyArray[polyChoice1 - 1], polyArray[polyChoice2 - 1]);
		  	polyPrint(polyArray[polyArrayCounter]);
		  	polyArrayCounter += 1;
		  	break;
		  
		// multiplies a polynomial by a constant
		case 6:
		  	printf("\nPlease select a polynomial and a constant to multiply together\n");
		  	polyPrintList(polyArray, polyArrayCounter);
		  	printf("\n");
		  	scanf("%d %lf", &polyChoice1, &constant);
		  	polyArray[polyArrayCounter] = polyMultiply(polyArray[polyChoice1 - 1], constant);
		  	polyPrint(polyArray[polyArrayCounter]);
		  	polyArrayCounter += 1;
		 	break;
		  
		// divides a polynomial by a constant
		case 7:
		  	printf("\nPlease select a polynomial and a constant to divide from it\n");
		  	polyPrintList(polyArray, polyArrayCounter);
		  	printf("\n");
		  	scanf("%d %lf", &polyChoice1, &constant);
		  	polyArray[polyArrayCounter] = polyDivide(polyArray[polyChoice1 - 1], constant);
		  	polyPrint(polyArray[polyArrayCounter]);
		  	polyArrayCounter += 1;
		  	break;
		// normalise a polynomial
		case 8:
		  	printf("\nPlease select a polynomial to normalise\n");
		  	polyPrintList(polyArray, polyArrayCounter);
		  	printf("\n");
		  	scanf("%d", &polyChoice1);
		  	polyArray[polyArrayCounter] = polyNormalise(polyArray[polyChoice1 - 1]);
		  	polyPrint(polyArray[polyArrayCounter]);
		  	polyArrayCounter += 1;
		  	break;
		  
		// return order of polynomial
		case 9:
		  	printf("\nPlease select a polynomial you want to get the order of\n");
		 	polyPrintList(polyArray, polyArrayCounter);
		 	printf("\n");
		  	scanf("%d", &polyChoice1);
		  	constant = polyOrder(polyArray[polyChoice1 - 1]);
		  	printf("The order of the polynomial chosen is %.0lf\n", constant);
		 	 break;

		// closes the application
		case 10:
		  	printf("\nClosing Program...\n");
		  	continueLoop = 0;
		  	break;
		  
		// ends loop, closes program
		default:
		  	printf("Invalid choice. Try another\n");
		  	break;
		}
    }
  
}

////////////////////////////////////////////////////
// Name: polyDeclare
// Purpose: Declares the polynomial, asks the user to enter a polynomial 
// Return: returns a polynomial
////////////////////////////////////////////////////

polyList *polyDeclare()
{
  polyList *poly;
  poly = polyCreate();

  int order;
  
  printf("Please enter the order of the polynomial: ");
  scanf("%d", &order);

  double coeff[order+1];

  printf("Please enter the coefficients of the polynomial from least to most significant\n");
  for(int i = 0; i <= order; i++){
    scanf("%lf", &coeff[i]);
  }

  fillPoly(poly, order, coeff);

  return poly;
}

////////////////////////////////////////////////////
// Name: polyPrintList
// Purpose: prints out a list of polynomials
// Parameters: polyArray[] - pointer to array of polynomials
//             PolyArrayCounter - counts number of polynomials in the array
////////////////////////////////////////////////////

void polyPrintList(polyList *polyArray[], int polyArrayCounter)
{
  for(int i = 0; i < polyArrayCounter; i++)
  {
    printf("%d. ", i+1);
    polyPrint(polyArray[i]);
  }
}
