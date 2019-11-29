////////////////////////////////////////////////////
// main.c
//
// purpose: Contains a lovely interface for interacting
//          with polynomials
//
// authors: Kevin McAndrew, Aaron Naylor, Stephen Gannon, Conor Pesch
// date:    29.11.2019
////////////////////////////////////////////////////

#include "Polynomial/polynomial.h"
#include <stdlib.h>
#include <stdio.h>

// Helper function declarations
polyList *polyDeclare();
void delete(int *polyArrayCounter, polyList *polyArray[100]);
void doubleOperation(int *polyArrayCounter, polyList *polyArray[100], 
	polyList *(*f)(polyList *, polyList *));
void singleOperation(int *polyArrayCounter, polyList *polyArray[100], 
	polyList *(*f)(polyList *, double constant));
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

  int polyChoice1;
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
		  	delete(&polyArrayCounter, polyArray);
		  	break;
		  
		// adds 2 polynomials
		case 4:
			// Pass polyAdd() into operation function
			printf("\nPlease select two polynomials to add together\n");
			doubleOperation(&polyArrayCounter, polyArray, polyAdd);
		  	break;
		  
		// subtracts 2 polynomials
		case 5:
		  	printf("\nPlease select a polynomial to subract from another\n");
		  	doubleOperation(&polyArrayCounter, polyArray, polySubtract);
		  	break;
		  
		// multiplies a polynomial by a constant
		case 6:
		  	printf("\nPlease select a polynomial and a constant to multiply together\n");
		  	singleOperation(&polyArrayCounter, polyArray, polyMultiply);
		 	break;
		  
		// divides a polynomial by a constant
		case 7:
		  	printf("\nPlease select a polynomial and a constant to divide from it\n");
		  	singleOperation(&polyArrayCounter, polyArray, polyDivide);
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
// Purpose: Declares the polynomial, asks the user 
//          to enter a polynomial 
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
// Name: delete
// Purpose: Deletes a selected polynomial from the
//          polynomial list
// Parameters: polyArrayCounter - the array counter
//             polyArray - the array of polynomials
////////////////////////////////////////////////////
void delete(int *polyArrayCounter, polyList *polyArray[100])
{
	// Declare local variables
	int polyChoice;

	// Print options and read choice
	printf("\nPlease select a polynomial to delete\n\n");
	polyPrintList(polyArray, *polyArrayCounter);
	printf("\n");
	scanf("%d",&polyChoice);

	// Check if choice is valid
	if(polyChoice > *polyArrayCounter || polyChoice < 1)
		return;

	// If valid, remove polynomial from list
	polyDelete(polyArray[polyChoice - 1]);

	// Move all later polynomials back
	for(int i = polyChoice; i <= *polyArrayCounter; i++)
	{
		polyArray[i - 1] = polyArray[i];
	}

	// Move array counter back
	*polyArrayCounter -= 1;
}

////////////////////////////////////////////////////
// Name: doubleOperation
// Purpose: Runs an operation with two polynomials
// Parameters: polyArrayCounter - the array counter
//             polyArray - the array of polynomials
//             *f - pointer to function to use
////////////////////////////////////////////////////
void doubleOperation(int *polyArrayCounter, polyList *polyArray[100], 
	polyList *(*f)(polyList *, polyList *))
{
	// Declare local variables
	int polyChoice1, polyChoice2;

	// Print options and read choice
	polyPrintList(polyArray, *polyArrayCounter);
	printf("\n");
	scanf("%d %d", &polyChoice1, &polyChoice2);

	// Check if choice is valid
	if((polyChoice1 < 1 || polyChoice1 > *polyArrayCounter)
		|| (polyChoice2 < 1 || polyChoice2 > *polyArrayCounter))
		return;

	// Apply given operation
	polyArray[*polyArrayCounter] = (*f)(polyArray[polyChoice1 - 1], polyArray[polyChoice2 - 1]);
	polyPrint(polyArray[*polyArrayCounter]);
	*polyArrayCounter += 1;
}

////////////////////////////////////////////////////
// Name: singleOperation
// Purpose: Runs an operation with one polynomial
// Parameters: polyArrayCounter - the array counter
//             polyArray - the array of polynomials
//             *f - pointer to function to use
////////////////////////////////////////////////////
void singleOperation(int *polyArrayCounter, polyList *polyArray[100], 
	polyList *(*f)(polyList *, double constant))
{
	// Declare local variables
	int polyChoice1;
	double constant;

	// Print options and read choice
	polyPrintList(polyArray, *polyArrayCounter);
	printf("\n");
	scanf("%d %lf", &polyChoice1, &constant);

	// Check if choice is valid
	if(polyChoice1 < 1 || polyChoice1 > *polyArrayCounter)
		return;

	// Apply given operation
	polyArray[*polyArrayCounter] = (*f)(polyArray[polyChoice1 - 1], constant);
	polyPrint(polyArray[*polyArrayCounter]);
	*polyArrayCounter += 1;
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
