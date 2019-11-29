////////////////////////////////////////////////////
// polyOp.c
//
// purpose: Contains all operations to add, subtract,
//          multiply, divide, normalise, get order of
//          and print polynomials
//
// authors: Kevin McAndrew, Aaron Naylor, Stephen Gannon, Conor Pesch
// date:    29.11.2019
////////////////////////////////////////////////////

#include "polynomial.h"

///////////////////////////////////////////////////////
// Name: polyAdd()
// Purpose: Adds two polynomials together
// Parameters:  poly1 - pointer for the first polynomial to added 
//              poly2 - pointer for the second polynomial to be added
// Return: sum of poly1 and poly2
///////////////////////////////////////////////////////

polyList *polyAdd(polyList *poly1, polyList *poly2)
{
  // Declares a polynomial and allocates memory
  polyList *poly3;
  poly3 = polyCreate();
  // Variables for holding which poly is biggest and smallest
  int smallOrd, bigOrd, whichOrd;

  // Checks which polynomial has a higher order
  // Assigns variables for each order
  if(polyOrder(poly1) > polyOrder(poly2))
  {
    whichOrd = 1;
    smallOrd = polyOrder(poly2);
    bigOrd = polyOrder(poly1);
  }
  else if(polyOrder(poly1) < polyOrder(poly2))
  {
    whichOrd = 0;
    smallOrd = polyOrder(poly1);
    bigOrd = polyOrder(poly2);
  }
  else
  {
    smallOrd = polyOrder(poly1);
    bigOrd = polyOrder(poly2);
  }

  // Reset current cursors
  polyToHead(poly1);
  polyToHead(poly2);
  polyToHead(poly3);

  // Adds each coefficient of the polynomials until one runs out of coefficients
  for(int i = 0; i <= smallOrd; i++)
  {
    poly3->current->d.coefficient = poly1->current->d.coefficient + poly2->current->d.coefficient;
    polyIncrement(poly1, 1);
    polyIncrement(poly2, 1);
    poly3->current->next = newCoeff(0, i + 1);
    polyIncrement(poly3, 1);
  }

  // Checks which polynomial has the higher order 
  // Then assigns the rest of its terms to poly3
  if(whichOrd == 1)
  {
    for(int i = smallOrd + 1; i < bigOrd; i++)
    {
      poly3->current->d.coefficient = poly1->current->d.coefficient;
      polyIncrement(poly1, 1);
      poly3->current->next = newCoeff(0, i + 1);
      polyIncrement(poly3, 1);
    }
    // Do not make new node on final assign
    poly3->current->d.coefficient = poly1->current->d.coefficient;
  }
  else if(whichOrd == 0)
  {
    for(int i = smallOrd + 1; i < bigOrd; i++)
    {
      poly3->current->d.coefficient = poly2->current->d.coefficient;
      polyIncrement(poly2, 1);
      poly3->current->next = newCoeff(0, i + 1);
      polyIncrement(poly3, 1);
    }
    // Do not make new node on final assign
    poly3->current->d.coefficient = poly2->current->d.coefficient;
  }

  // Reset current cursor to head
  polyToHead(poly1);
  polyToHead(poly2);
  polyToHead(poly3);
  return poly3;
}

///////////////////////////////////////////////////////
// Name: polySubtract()
// Purpose: Subtracts a polynomial from another
// Parameters:  poly1 - pointer for the minuend polynomial
//              poly2 - pointer for the the subtrahend polynomial
// Return: poly1 minus poly2
///////////////////////////////////////////////////////

polyList *polySubtract(polyList *poly1, polyList *poly2)
{
  // Declares a polynomial and allocates memory
  polyList *poly3;
  poly3 = polyCreate();
  // Variables for holding which poly is biggest and smallest
  int smallOrd, bigOrd, whichOrd;
  // Checks which polynomial has the higher order
  if(polyOrder(poly1) > polyOrder(poly2))
  {
    whichOrd = 1;
    smallOrd = polyOrder(poly2);
    bigOrd = polyOrder(poly1);
  }
  else if(polyOrder(poly1) < polyOrder(poly2))
  {
    whichOrd = 0;
    smallOrd = polyOrder(poly1);
    bigOrd = polyOrder(poly2);
  }
  else
  {
    smallOrd = polyOrder(poly1);
    bigOrd = polyOrder(poly2);
  }

  // Reset current cursors
  polyToHead(poly1);
  polyToHead(poly2);
  polyToHead(poly3);

  // Subtracts poly2 from poly1 until one runs out of coefficients
  for(int i = 0; i <= smallOrd; i++)
  {
    poly3->current->d.coefficient = poly1->current->d.coefficient - poly2->current->d.coefficient;
    polyIncrement(poly1, 1);
    polyIncrement(poly2, 1);
    poly3->current->next = newCoeff(0, i + 1);
    polyIncrement(poly3, 1);
  }

  // Checks which polynomial has the higher order
  // If the minuend has a higher order, its remaining elements are assigned to poly3
  // If the subtrahend has a higher order, the negative of its 
  // remaining elements are assigned to poly3
  if(whichOrd == 1)
  {
    for(int i = smallOrd + 1; i < bigOrd; i++)
    {
      poly3->current->d.coefficient = poly1->current->d.coefficient;
      polyIncrement(poly1, 1);
      poly3->current->next = newCoeff(0, i + 1);
      polyIncrement(poly3, 1);
    }
    // Do not make new node on final assign
    poly3->current->d.coefficient = poly1->current->d.coefficient;
  }
  else if(whichOrd == 0)
  {
    for(int i = smallOrd + 1; i < bigOrd; i++)
    {
      poly3->current->d.coefficient = 0 - poly2->current->d.coefficient;
      polyIncrement(poly2, 1);
      poly3->current->next = newCoeff(0, i + 1);
      polyIncrement(poly3, 1);
    }
    // Do not make new node on final assign
    poly3->current->d.coefficient = 0 - poly2->current->d.coefficient;
  }

  // Reset current cursor to head
  polyToHead(poly1);
  polyToHead(poly2);
  polyToHead(poly3);
  return poly3;
}

///////////////////////////////////////////////////////
// Name: polyMultiply()
// Purpose: Multiplies a polynomial by a double
// Parameters: poly1 - pointer for the polynomial
//             multiplier - number that multiplies the polynomial
// Return: Polynomial that was multiplied
///////////////////////////////////////////////////////

polyList *polyMultiply(polyList *poly1, double multiplier)
{
  // Declares a polynomial and allocates memory
	polyList *polyMul;
	polyMul = polyCreate();

  // Find order of the polynomial
	int ord = polyOrder(poly1);
	
  // Reset cursors to head
	polyToHead(polyMul);
  polyToHead(poly1);
	//Assign the coefficients to poly1 * multiplier
	for(int i = 0; i < ord; i++)
	{	
		// Value of current coefficient is multiped 
    // by the double and stored in the new polynomial
		polyMul->current->d.coefficient = 
			(poly1->current->d.coefficient) * (multiplier);

    // Create new node and move to that node
    polyMul->current->next = newCoeff(0, i + 1);
    polyIncrement(polyMul, 1);
    // Increment poly1 as well
    polyIncrement(poly1, 1);
	}
  // Do not create new node, because it is at the end
  polyMul->current->d.coefficient = 
      (poly1->current->d.coefficient) * (multiplier);

  // Reset cursors to head
  polyToHead(polyMul);
  polyToHead(poly1);
  // Return polynomial multiplied by multiplier
	return polyMul;
}

//////////////////////////////////////////////////////
// Name: polyDivide()
// Purpose: Divides a polynomial by a double
// Parameters: poly1 - pointer for the polynomial
//             divider - number that divides the polynomial
// Return: Polynomial that was divided
///////////////////////////////////////////////////////

polyList *polyDivide(polyList *poly1, double divider)
{
  // Declares a polynomial and allocates memory
  polyList *polyDiv;
	polyDiv = polyCreate();

  // Find order of the polynomial
	int ord = polyOrder(poly1);
  
  // Reset current cursors
	polyToHead(polyDiv);
  polyToHead(poly1);
  //Assign the coefficients to poly1 / divider
	for(int i = 0; i < ord; i++)
	{	
      //value of current coefficient is multiped 
      //by the double and stored in the new polynomial
      polyDiv->current->d.coefficient = 
              (poly1->current->d.coefficient) / (divider);

      //create new node and move to that node
      polyDiv->current->next = newCoeff(0, i + 1);
      polyIncrement(polyDiv, 1);
      // Increment poly1 as well
      polyIncrement(poly1, 1);
	}
  // Do not create new node, because it is at the end
  polyDiv->current->d.coefficient = 
      (poly1->current->d.coefficient) / (divider);

  // Reset current cursors
  polyToHead(polyDiv);
  polyToHead(poly1);
  // Return polynomial divided by divisor
	return polyDiv;
}

//////////////////////////////////////////////////////
// Name: polyNormalise()
// Purpose: Adjusts coeffiecients so that the coefficient
//          of highest order is 1
// parameters: poly1 - pointer to the polynomial
// Return: norm, the adjusted version of poly1 so
// 	   coefficient of highest order is 1
//////////////////////////////////////////////////////

polyList *polyNormalise(polyList *poly1)
{
  // Set up variables for result and highest coefficient
  polyList *norm;
  double highCoeff;

  polyToEnd(poly1);
  // Store highest coefficient
  highCoeff = poly1->current->d.coefficient;
  // Reset current cursor to head and call dividing function
  polyToHead(poly1);
  norm = polyDivide(poly1, highCoeff);

  // Return normalised polynomial
  polyToHead(poly1);
  polyToHead(norm);
  return norm;
}

/////////////////////////////////////////////////////
// Name: polyOrder()
// Purpose: Finds the highest power whos coefficient
// 	    isnt 0
// Parameters: poly1 - pointer to the polynomial
// Return: highOrder, the most significant order
/////////////////////////////////////////////////////

int polyOrder(polyList *poly1)
{
  // Variable to store highest order in polyList
  int highOrder = 0;
  // Reset current to head
  polyToHead(poly1);

  // Do while you haven't reached the end
  int i = 0;
  while(poly1->current->next != NULL)
  {
      // Set current to next value
      polyIncrement(poly1, 1);
      i++;

      // If poly1's coefficient is not equal to 0 
      if(poly1->current->d.coefficient != 0)
      {
         // Length is highest order that is not equal to 0
	       highOrder = i;
      } 
  } 

  // Reset current to head and return
  polyToHead(poly1);
  return highOrder;
}

////////////////////////////////////////////////////
// Name: polyPrint()
// Purpose: prints a polynomial to stdout
// Parameters: poly1 - pointer to the polynomial
// Return: If there was an error
////////////////////////////////////////////////////

polyError polyPrint(polyList *poly1)
{  
  // Report null polynomial
  if(poly1 == NULL)
    return nullPoly;

  // Get order of polynomial
  int order = polyOrder(poly1);
  // Reset current cursor to head
  polyToHead(poly1);
  
  // Print constant coefficient first
  fprintf(stdout, "%.3lf", (poly1->current->d.coefficient));
  // Increment the current cursor
  polyIncrement(poly1, 1);
  
  // Repeat print for the remaining elements
  for(int i = 1; i <= order; i ++) // for loop from 0 to highest order
  {
      fprintf(stdout, " + %.3lfx^%d", poly1->current->d.coefficient, i);
      // Increment the current cursor
      polyIncrement(poly1, 1);
  }

  // Print new line
  fprintf(stdout, "\n");

  return ok;
}
