// main.c

#include "Polynomial/polynomial.h"
#include <stdlib.h>
#include <stdio.h>


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

int main()
{
  int continueLoop = 1;
  polyList *polyArray[20];
  int polyArrayCounter = 0;

  int polyChoice1, polyChoice2;
  double constant;
  
  while(continueLoop)
    {
      int interfaceChoice;
      printf("Please choose the number corresponding to the action you want\n1. Display all polynomials\n2. Create a polynomial\n3. Delete a polynomial\n4. Add two polynomials\n5. Subtract two polynomials\n6. Multiply a polynomial by a constant\n7. Divide a polynomial by a constant\n8. Normalise a polynomial\n9. Return the order of a polynomial\n10. Close the application\n");
      scanf("%i", &interfaceChoice);

      switch(interfaceChoice)
	{
	// displays all polynomials
	case 1:
	  for(int i = 0; i < polyArrayCounter; i++)
	  {
	    polyPrint(polyArray[i]);
	    printf("\n");
	  }
	  break;
	  
	// creates a polynomial
	case 2:
	  polyArray[polyArrayCounter] = polyDeclare();
	  polyArrayCounter += 1;
	  break;
	  
	// deletes a polynomial
	case 3:
	  printf("Please select a polynomial to delete\n");
	  polyPrintList(polyArray, polyArrayCounter);
	  scanf("%d",&polyChoice1);
	  polyDelete(polyArray[polyChoice1 - 1]);
	  polyArrayCounter -= 1;
	  break;
	  
	// adds 2 polynomials
	case 4:
	  printf("Please select two polynomials to add together\n");
	  polyPrintList(polyArray, polyArrayCounter);
	  scanf("%d %d", &polyChoice1, &polyChoice2);
	  polyArray[polyArrayCounter] = polyAdd(polyArray[polyChoice1 - 1], polyArray[polyChoice2 - 1]);
	  polyPrint(polyArray[polyArrayCounter]);
	  polyArrayCounter += 1;
	  break;
	  
	// subtracts 2 polynomials
	case 5:
	  printf("Please select a polynomial to subract from another\n");
	  polyPrintList(polyArray, polyArrayCounter);
	  scanf("%d %d", &polyChoice1, &polyChoice2);
	  polyArray[polyArrayCounter] = polySubtract(polyArray[polyChoice1 - 1], polyArray[polyChoice2 - 1]);
	  polyPrint(polyArray[polyArrayCounter]);
	  polyArrayCounter += 1;
	  break;
	  
	// multiplies a polynomial by a constant
	case 6:
	  printf("Please select a polynomial and a constant to multiply together\n");
	  polyPrintList(polyArray, polyArrayCounter);
	  scanf("%d %lf", &polyChoice1, &constant);
	  polyArray[polyArrayCounter] = polyMultiply(polyArray[polyChoice1 - 1], constant);
	  polyPrint(polyArray[polyArrayCounter]);
	  polyArrayCounter += 1;
	  break;
	  
	// divides a polynomial by a constant
	case 7:
	  printf("Please select a polynomial and a constant to divide from it\n");
	  polyPrintList(polyArray, polyArrayCounter);
	  scanf("%d %lf", &polyChoice1, &constant);
	  polyArray[polyArrayCounter] = polyDivide(polyArray[polyChoice1 - 1], constant);
	  polyPrint(polyArray[polyArrayCounter]);
	  polyArrayCounter += 1;
	  break;
	// normalise a polynomial
	case 8:
	  printf("Please select a polynomial to normalise\n");
	  polyPrintList(polyArray, polyArrayCounter);
	  scanf("%d", &polyChoice1);
	  polyArray[polyArrayCounter] = polyNormalise(polyArray[polyChoice1 - 1]);
	  polyPrint(polyArray[polyArrayCounter]);
	  polyArrayCounter += 1;
	  break;
	  
	// return order of polynomial
	case 9:
	  printf("Please select a polynomial you want to get the order of\n");
	  polyPrintList(polyArray, polyArrayCounter);
	  scanf("%d", &polyChoice1);
	  constant = polyOrder(polyArray[polyChoice1 - 1]);
	  printf("The order of the polynomial chosen is %.0lf\n", constant);
	  break;

	case 10:
	  printf("Closing Program\n");
	  continueLoop = 0;
	  break;
	  
	// ends loop, closes program
	default:
	  printf("Invalid choice. Closing Program\n");
	  continueLoop = 0;
	  break;
	}
    }
  
}
