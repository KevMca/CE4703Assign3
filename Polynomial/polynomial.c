// polynomial.c
// Purpose: Contains all functions to create, delete and manipulate the polynomial
// Author: Kevin McAndrew, Aaron Naylor, Stephen Gannon, Conor Pesch
// Date: 27/11/2019

#include "polynomial.h"

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

int fillPoly(polyList *poly, int order, double arr[])
{
    // Fill polyList parameters
    poly->order = order;
    
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
    return 0;
}

polyNode *newCoeff(double coefficient, int order)
{
    // Allocate memory for new node
    polyNode *new_node = (polyNode*)malloc(sizeof(polyNode));
    if(new_node == NULL)
    {
        // Report error
        exit(0);
    }

    // Assign attributes
    new_node->d.coefficient = coefficient;
    new_node->d.order = order;
    new_node->next = NULL;
 
    // Link new node to current node
    return new_node;
}

int polyDelete(polyList *poly)
{
    // Reset
    poly->current = poly->head;

    // While there is a next node, delete current node
    while(poly->head->next != NULL)
    {
        deleteNext(poly->current);
    }

    // Polynomial is empty, so head and polynomial need to
    // be freed
    free(poly->head);
    free(poly);
    return 0;
}

int deleteNext(polyNode *current)
{
    polyNode *toDelete;
    if (current->next == NULL)
    {
        // Next is tail => cannot remove node
        return -1;
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
    return 0;
}

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
  else
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
  else
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
  norm = divide(poly1, highCoeff); // calls dividing function
  return norm; // returns coefficient of highest order 
}

int polyOrder(polyList *poly1)
{
  int length; // variable to store highest order in polyList
  poly1->current = poly1->head;
  for(int i=0; i <= (poly1->order); i ++) // for loop from 0 to length of polylist 
  {
      if(poly1->current->d.coefficient !=0) // if poly1's coefficient is not equal to 0 
      {
	  length = i; // length is highest order that is not equal to 0
      } 
      poly1->current = poly1->current->next; // sets current to next value
  }
  poly1->current = poly1->head;
  return length; // returns most significant order
}

void polyPrint(polyList *poly1)
{  
  int order = polyOrder(poly1); // get highest order that coefficient isn't 0
  poly1->current = poly1->head; // set current to first element
  fprintf(stdout, "%lf", (poly1->current->d.coefficient)); // prints first element
  poly1->current = poly1->current->next; // sets current to next number 
  
  for(int i = 1; i <= order; i ++) // for loop from 0 to highest order
  {
    fprintf(stdout, " + %lfx^%d", poly1->current->d.coefficient, i); // prints coefficient polynominal starting at least significant
      poly1->current = poly1->current->next; // sets current to next number 
  }
  // Print new line
  fprintf(stdout, "\n\n");
}
