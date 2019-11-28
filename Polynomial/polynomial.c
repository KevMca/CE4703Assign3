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
            poly->current = poly->head;
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
// Name: polyToend()
// Purpose: Moves current cursor to the end of the polynomial
// Parameters:  poly - pointer to polynomial
// Return: if there was an error
///////////////////////////////////////////////////////

polyError polyToEnd(polyList *poly)
{
  if(poly != NULL)
  {
    // Reset to current to head
    polyToHead(poly);
    // While next isn't equal to NULL increment the current
    while(poly->current->next != NULL)
    {
      poly->current = poly->current->next;
    }
  }
  else
    return nullPoly;

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
    // Assign head coefficient first
    poly->current = poly->head;
    poly->current->d.coefficient = arr[0];
    poly->current->d.order = 0;

    // Assign the rest of the coefficients
    for(int i = 1; i <= order; i++)
    {
        poly->current->next = newCoeff(arr[i], i);
        poly->current = poly->current->next;
    }
    
    // Reset current and return success
    poly->current = poly->head;
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
        // Return NULL
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
  polyList *poly3; // declares a polynomial
  poly3 = polyCreate(); // creates an empty polynomial
  int smallOrd, bigOrd, whichOrd;
  // checks which polynomial has a higher order
  // assigns variables for each order
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

  // reset current cursors
  poly1->current = poly1->head;
  poly2->current = poly2->head;
  poly3->current = poly3->head;

  // adds each coefficient of the polynomials to each other until one runs out of coefficients
  for(int i = 0; i <= smallOrd; i++)
  {
    poly3->current->d.coefficient = poly1->current->d.coefficient + poly2->current->d.coefficient;
    poly1->current = poly1->current->next;
    poly2->current = poly2->current->next;
    poly3->current->next = newCoeff(0, i);
    poly3->current = poly3->current->next;
  }

  // checks which polynomial has the higher order then assigns the rest of its terms to poly3
  if(whichOrd == 1)
  {
    for(int i = smallOrd + 1; i < bigOrd; i++)
    {
      poly3->current->d.coefficient = poly1->current->d.coefficient;
      poly1->current = poly1->current->next;
      poly3->current->next = newCoeff(0, i);
      poly3->current = poly3->current->next;
    }
    poly3->current->d.coefficient = poly1->current->d.coefficient; // final assign, doesn't make a new node
  }
  else if(whichOrd == 0)
  {
    for(int i = smallOrd + 1; i < bigOrd; i++)
    {
      poly3->current->d.coefficient = poly2->current->d.coefficient;
      poly2->current = poly2->current->next;
      poly3->current->next = newCoeff(0, i);
      poly3->current = poly3->current->next;
    }
    poly3->current->d.coefficient = poly2->current->d.coefficient;
  }

  // reset current cursor to head
  poly3->current = poly3->head;
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
  polyList *poly3;
  poly3 = polyCreate(); // creates an empty polynomial
  int smallOrd, bigOrd, whichOrd;
  // checks which polynomial has the higher order
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

  // subracts poly2 from poly1 until one runs out of coefficients
  for(int i = 0; i <= smallOrd; i++)
  {
    poly3->current->d.coefficient = poly1->current->d.coefficient - poly2->current->d.coefficient;
    poly1->current = poly1->current->next;
    poly2->current = poly2->current->next;
    poly3->current->next = newCoeff(0, i);
    poly3->current = poly3->current->next;
  }

  // checks which polynomial has the higher order
  // if the minuend has a higher order, its remaining elements are assigned to poly3
  // if the subtrahend has a higher order, the inverse of its remaining elements are assigned to poly3
  if(whichOrd == 1)
  {
    for(int i = smallOrd + 1; i < bigOrd; i++)
    {
      poly3->current->d.coefficient = poly1->current->d.coefficient;
      poly1->current = poly1->current->next;
      poly3->current->next = newCoeff(0, i);
      poly3->current = poly3->current->next;
    }
    poly3->current->d.coefficient = poly1->current->d.coefficient;
  }
  else if(whichOrd == 0)
  {
    for(int i = smallOrd + 1; i < bigOrd; i++)
    {
      poly3->current->d.coefficient = 0 - poly2->current->d.coefficient;
      poly2->current = poly2->current->next;
      poly3->current->next = newCoeff(0, i);
      poly3->current = poly3->current->next;
    }
    poly3->current->d.coefficient = 0 - poly2->current->d.coefficient;
  }

  // reset current cursor to head
  poly3->current = poly3->head;
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
	polyList *polyMul; //creates a new polynomial to use for multiplication
	polyMul = polyCreate();
	int ord = polyOrder(poly1); //int ord is assigned the value of the order of the polynomial
	//Assign head first
	polyMul->current = polyMul->head;
	polyMul->current->d.order = 0;
	polyMul->current->d.coefficient = 
                        (poly1->current->d.coefficient) * (multiplier);
	
	//Assign the remaining coefficients
	for(int i = 1; i <= ord; i++)
	{	
		//create new node and move to that node
		polyMul->current->next = newCoeff(0, i);
		polyMul->current = polyMul->current->next;
		
		//value of current coefficient is multiped 
                //by the double and stored in the new polynomial
		polyMul->current->d.coefficient = 
			(poly1->current->d.coefficient) * (multiplier);
	}
	return polyMul; //returns the multipied polynomial
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
  polyList *polyDiv; //creates a new polynomial to use for division
	polyDiv = polyCreate();
	int ord = polyOrder(poly1); //int ord is assigned the value of the order of the polynomial
  
  // Reset current cursors
	polyDiv->current = polyDiv->head;
  poly1->current = poly1->head;
  
  //Assign head first
	polyDiv->current->d.order = 0;
	polyDiv->current->d.coefficient = 
		(poly1->current->d.coefficient) / (divider);
	
  //Assign the remaining coefficients
	for(int i = 1; i <= ord; i++)
	{	
		  //create new node and move to that node
      polyDiv->current->next = newCoeff(1, i);
      polyDiv->current = polyDiv->current->next;
      // Increment poly1 as well
      poly1->current = poly1->current->next;

      //value of current coefficient is multiped 
      //by the double and stored in the new polynomial
      polyDiv->current->d.coefficient = 
              (poly1->current->d.coefficient) / (divider);
	}
	return polyDiv; //returns the divided polynomial 
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
  polyList *norm; // variable to store value before returned
  double highCoeff; // stores coefficient of highest order
  int order = polyOrder(poly1); // calls order function to find highest order
  poly1->current = poly1->head;
  for(int i =0; i < order; i++) // for loop from 0 to order in increments of 1
  {
      poly1->current = poly1->current->next; // sets current to next value
  }
  highCoeff = poly1->current->d.coefficient; // stores coefficient
  poly1->current = poly1->head;
  norm = polyDivide(poly1, highCoeff); // calls dividing function
  return norm; // returns coefficient of highest order 
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
  poly1->current = poly1->head;

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
      poly1->current = poly1->current->next;
      i++;
  } while(poly1->current != NULL);

  // Reset current to head and return
  poly1->current = poly1->head;
  return highOrder;
}

////////////////////////////////////////////////////
// Name: polyPrint()
// Purpose: prints a polynomial to stdout
// Parameters: poly1 - pointer to the polynomial
// Return: The printed polynomial to the stdout
////////////////////////////////////////////////////

void polyPrint(polyList *poly1)
{  
  int order = polyOrder(poly1); // get highest order that coefficient isn't 0
  poly1->current = poly1->head; // set current to first element
  fprintf(stdout, "%.3lf", (poly1->current->d.coefficient)); // prints first element
  poly1->current = poly1->current->next; // sets current to next number 
  
  for(int i = 1; i <= order; i ++) // for loop from 0 to highest order
  {
    fprintf(stdout, " + %.3lfx^%d", poly1->current->d.coefficient, i); // prints coefficient polynominal starting at least significant
      poly1->current = poly1->current->next; // sets current to next number 
  }
  // Print new line
  fprintf(stdout, "\n\n");
}
