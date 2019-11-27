// main.c

#include "Polynomial/polynomial.h"
#include <stdlib.h>
#include <stdio.h>

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

void polyPrintList(polyList *polyArray[], int polyArrayCounter)
{
  for(int i = 0; i < polyArrayCounter; i++)
  {
    printf("%d. ", i+1);
    polyPrint(polyArray[i]);
    printf("\n");
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
      printf("Please choose the number corresponding to the action you want\n1. Display all polynomials\n2. Create a polynomial\n3. Delete a polynomial\n4. Add two polynomials\n5. Subtract two polynomials\n6. Multiply a polynomial by a constant\n7. Divide a polynomial by a constant\n8. Normalise a polynomial\n 9.Return the order of a polynomial\n10. Close the application\n");
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
	  polyArray[polyArrayCounter + 1] = polyAdd(polyArray[polyChoice1 - 1], polyArray[polyChoice2 - 1]);
	  polyArrayCounter += 1;
	  polyPrint(polyArray[polyArrayCounter]);
	  break;
	  
	// subtracts 2 polynomials
	case 5:
	  printf("Please select a polynomial to subract from another\n");
	  polyPrintList(polyArray, polyArrayCounter);
	  scanf("%d %d", &polyChoice1, &polyChoice2);
	  polyArray[polyArrayCounter + 1] = polyAdd(polyArray[polyChoice1 - 1], polyArray[polyChoice2 - 1]);
	  polyArrayCounter += 1;
	  polyPrint(polyArray[polyArrayCounter]);
	  break;
	  
	// multiplies a polynomial by a constant
	case 6:
	  printf("Please select a polynomial and a constant to multiply together\n");
	  polyPrintList(polyArray, polyArrayCounter);
	  scanf("%d %lf", &polyChoice1, &constant);
	  polyArray[polyArrayCounter + 1] = multiply(polyArray[polyChoice1 - 1], constant);
	  polyArrayCounter += 1;
	  polyPrint(polyArray[polyArrayCounter]);
	  break;
	  
	// divides a polynomial by a constant
	case 7:
	  printf("Please select a polynomial and a constant to divide from it\n");
	  polyPrintList(polyArray, polyArrayCounter);
	  scanf("%d %lf", &polyChoice1, &constant);
	  polyArray[polyArrayCounter + 1] = divide(polyArray[polyChoice1 - 1], constant);
	  polyArrayCounter += 1;
	  polyPrint(polyArray[polyArrayCounter]);
	  break;
	// normalise a polynomial
	case 8:
	  printf("Please select a polynomial to normalise\n");
	  polyPrintList(polyArray, polyArrayCounter);
	  scanf("%d", &polyChoice1);
	  polyArray[polyArrayCounter + 1] = polyNormalise(polyArray[polyChoice1 - 1]);
	  polyArrayCounter += 1;
	  polyPrint(polyArray[polyArrayCounter]);
	  break;
	  
	// return order of polynomial
	case 9:
	  printf("Please select a polynomial you want to get the order of\n");
	  polyPrintList(polyArray, polyArrayCounter);
	  scanf("%d", &polyChoice1);
	  constant = polyOrder(polyArray[polyChoice1 - 1]);
	  printf("The order of the polynomial chosen is %lf\n", constant);
	  break;
	  
	// ends loop, closes program
	default:
	  printf("Invalid choice. Closing Program\n");
	  continueLoop = 0;
	  break;
	}
    }
  
}
