////////////////////////////////////////////////////
// polyFunc.c
// Purpose: Contains all functions to create, delete 
//          and manipulate polynomials
// Authors: Kevin McAndrew, Aaron Naylor, Stephen Gannon, Conor Pesch
// Date: 29/11/2019
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
