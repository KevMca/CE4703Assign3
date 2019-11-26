// main.c

#include "polynomial.h"

polyList polyDeclare()
{
  polyList *poly;
  poly = polyCreate();

  int order;
  
  printf("Please enter the order of the polynomial: ");
  scanf("%d", &order);

  double coeff[order+1];

  printf("Please enter the coefficients of the polynomial from least to most significant\n");
  for(int i = 0; i <= order; i++){
    scanf("%i", coeff[i]);
  }

  fillPoly(&poly, order, coeff[]);

  return poly;
}

int main()
{
  int continueLoop = 1;

  while(continueLoop)
    {
      int interfaceChoice;
      printf("Please choose the number corresponding to the action you want\n1. Display all polynomials\n2. Create a polynomial\n3. Delete a polynomial\n4. Add two polynomials\n5. Subtract two polynomials\n6. Multiply a polynomial by a constant\n7. Divide a polynomial by a constant\n8. Normalise a polynomial\n 9.Return the order of a polynomial\n10. Close the application\n");
      scanf("%i", &interfaceChoice);

      switch(interfaceChoice)
	{
	case 1:
	  
	  break;

	case 2:
	  polyList poly = polyDeclare();
	  break;

	case 3:

	  break;

	case 4:

	  break;

	case 5:

	  break;

	case 6:

	  break;

	case 7:

	  break;

	case 8:

	  break;

	case 9:

	  break;

	default:
	  printf("Invalid choice. Closing App\n");
	  break;
	}
    }
  
}
