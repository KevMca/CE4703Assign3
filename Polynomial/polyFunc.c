////////////////////////////////////////////////////
// polynomial.c
// Purpose: Contains all functions to create, delete and manipulate the polynomial
// Author: Kevin McAndrew, Aaron Naylor, Stephen Gannon, Conor Pesch
// Date: 27/11/2019
////////////////////////////////////////////////////

#include "polynomial.h"

///////////////////////////////////////////////////
// Name: polyCreate()
// Purpose: Creates and empty polynomial, head points
//          to tail and has no coeffiecients.
// Parameters: Use fillPoly() or newCoeff() to add
//             new coefficiients.
// return: pointer to polynomial if successful
//   	   NULL if unsuccessful
///////////////////////////////////////////////////

polyList *polyCreate()
{
    polyList *poly;
    poly = (polyList *) malloc(sizeof(polyList));
    // Check for allocation success
    if (poly != NULL) 
    {
        // Allocate memory for head
        poly->head = (polyNode *) malloc(sizeof(polyNode));
        if (poly->head != NULL) 
        {
            // Allocation successful
            poly->head->next = NULL;
            // Reset current to head
            polyToHead(poly);
        } 
        else
        {
            // need to de-allocate list and set it to NULL
            free(poly);
            poly = NULL;
        }
    }
    
    return poly;
}

///////////////////////////////////////////////////////
// Name: polyToHead()
// Purpose: Moves current cursor to the end of the head
// Parameters:  poly - pointer to the polynomial
// Return: if there was an error
///////////////////////////////////////////////////////

polyError polyToHead(polyList *poly)
{
  if(poly != NULL)
    poly->current = poly->head;
  else
    return nullPoly;

  return ok;
}

///////////////////////////////////////////////////////
// Name: polyToTail()
// Purpose: Moves current cursor to the end of the
//          where the next node is the tail
// Parameters:  poly - pointer to polynomial
// Return: if there was an error
///////////////////////////////////////////////////////

polyError polyToTail(polyList *poly)
{
  // Report null polynomial
  if(poly == NULL)
    return nullPoly;

  // While next isn't equal to NULL increment the current
  while(poly->current->next != NULL)
  {
    poly->current = poly->current->next;
  }

  return ok;
}

///////////////////////////////////////////////////////
// Name: polyToEnd()
// Purpose: Moves current cursor to the end of the
//          polynomial where there is a non-zero
//          coefficient
// Parameters:  poly - pointer to polynomial
// Return: if there was an error
///////////////////////////////////////////////////////

polyError polyToEnd(polyList *poly)
{
  // Report null polynomial
  if(poly == NULL)
    return nullPoly;

  // Find high non-zero order
  int order = polyOrder(poly);

  // Reset current cursor to head
  polyToHead(poly);
  // While next isn't equal to NULL increment the current
  for(int i = 0; i < order; i++)
  {
    polyIncrement(poly, 1);
  }

  return ok;
}

///////////////////////////////////////////////////////
// Name: polyIncrement()
// Purpose: Increments the current cursor by a defined
//          number of steps
// Parameters:  poly - pointer to polynomial
//              steps - number of steps to increment by
// Return: if there was an error
///////////////////////////////////////////////////////
polyError polyIncrement(polyList *poly, int steps)
{
  // Increment current cursor the number of times specified
  for(int i = 0; i < steps; i++)
  {
    // If the end has been reached, report node error
    if(poly->current->next == NULL)
      return nodeErr;
    poly->current = poly->current->next;
  }

  return ok;
}

//////////////////////////////////////////////////
// Name: fillPoly()
// Purpose: Fills an empty polynomial of a
//          certain order with coefficients in arr[]
// Parameters: poly - the empty polynomial to fill
// 	       order - the order of the polynomial
//	       arr - the array of coefficients
// Return: Pointer to polynomial if successful
//////////////////////////////////////////////////

polyError fillPoly(polyList *poly, int order, double arr[])
{   
    // Reset current cursor to head
    polyToHead(poly);
    // Assign head first
    poly->current->d.coefficient = arr[0];
    poly->current->d.order = 0;

    // Assign the rest of the coefficients
    for(int i = 1; i <= order; i++)
    {
        poly->current->next = newCoeff(arr[i], i);
        polyIncrement(poly, 1);
    }
    
    // Reset current and return success
    polyToHead(poly);
    return ok;
}

//////////////////////////////////////////////////
// Name: newCoeff()
// Purpose: Creates and returns a new polyNode to
// 	    be added to the next node of the
//	    previous node
// Parameters: coefficient - the value of the coefficient
//   	       order - the order of the coefficient
// Return:  pointer to the new node, if successful
//////////////////////////////////////////////////

polyNode *newCoeff(double coefficient, int order)
{
    // Allocate memory for new node
    polyNode *new_node = (polyNode*)malloc(sizeof(polyNode));
    if(new_node == NULL)
    {
        // Return NULL if unsuccessful
        return new_node;
    }

    // Assign attributes
    new_node->d.coefficient = coefficient;
    new_node->d.order = order;
    new_node->next = NULL;
 
    // Link new node to current node
    return new_node;
}

//////////////////////////////////////////////////
// Name: deleteNext()
// Purpose: Deletes and frees up memory for the next
//      node after the current node specified
// Parameters: toDelete - the coefficient node to
//         to delete
// Return: returns 0 if successful
//////////////////////////////////////////////////git 

polyError deleteNext(polyNode *current)
{
    polyNode *toDelete;
    if (current->next == NULL)
    {
        // Next is tail => cannot remove node
        return nodeErr;
    }
    else
    {
        // 1. Keep pointer to node to be deleted
        toDelete = current->next;
        // 2. Set successor of current to successor of node to be deleted
        current->next = toDelete->next;
        // 3. Delete node from memory
        free(toDelete);
    }
    return ok;
}

//////////////////////////////////////////////////
// Name: polyDelete()
// Purpose: Deletes and frees up memory from a
// 	    polynomial
// Parameters: poly - the to delete
// Return: returns 0 if successful
//////////////////////////////////////////////////

polyError polyDelete(polyList *poly)
{
    // Reset current cursor
    polyToHead(poly);

    // While there is a next node, delete current node
    while(poly->head->next != NULL)
    {
        // If deleteNext returns a node error return
        if(deleteNext(poly->current) != ok)
            return nodeErr;
    }

    // Polynomial is empty, so head and polynomial need to
    // be freed
    free(poly->head);
    free(poly);
    return ok;
}

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
  int highOrder;
  // Reset current to head
  polyToHead(poly1);

  // Do while you haven't reached the end
  int i = 0;
  do
  {
      // If poly1's coefficient is not equal to 0 
      if(poly1->current->d.coefficient !=0)
      {
         // Length is highest order that is not equal to 0
	       highOrder = i;
      } 
      // Set current to next value
      polyIncrement(poly1, 1);
      i++;
  } while(poly1->current->next != NULL);

  // Reset current to head and return
  polyToHead(poly1);
  return ++highOrder;
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
