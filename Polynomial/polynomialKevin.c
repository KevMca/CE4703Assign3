///////////////////////////////////////////////////////
// polynomialKevin.c
// implementation of create and delete operation for a 
// polynomial structure
//
// author:	kevin mcandrew
// date:	25.11.2019
///////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"
/*
int main()
{
    double arr[] = {5, 0, 1};
    polyList *poly1 = polyCreate();
    fillPoly(poly1, 2, arr);
    printf("%d %lf\n", poly1->current->d.order, poly1->current->d.coefficient);
    poly1->current = poly1->current->next;
    printf("%d %lf\n", poly1->current->d.order, poly1->current->d.coefficient);
    poly1->current = poly1->current->next;
    printf("%d %lf\n", poly1->current->d.order, poly1->current->d.coefficient);
    polyDelete(poly1);
}*/

///////////////////////////////////////////////////////
// polyCreate()
// Creates an empty polynomial, head points to tail and
// has no coefficients.
// Use fillPoly() or newCoeff() to add new coefficients
// 
// return: pointer to polynomial if successful
//         NULL if unsuccessful
///////////////////////////////////////////////////////
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
// fillPoly(poly, order, arr[])
// Fills an empty polynomial of with a certain order,
// with the coefficients in arr[]
//
// parameter:  poly - the empty polynomial to fill
//             order - the order of the polynomial
//             arr - the array of coefficients 
// return: pointer to polynomial if successful
///////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////
// newCoeff(coefficient, order)
// Creates and returns a new polyNode to be added to
// the next node of the previous node.
//
// parameter:  coefficient - the value of the coefficient
//             order - the order of the coefficient
// return: pointer to new node, if successful
///////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////
// polyDelete(poly)
// Deletes and frees up memory from a polynomial
//
// parameter:  poly - the polynomial to delete
// return: returns 0 if successful
///////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////
// deleteNext(current)
// Deletes and frees up memory for the next node after
// the current node specified
//
// parameter:  toDelete - the coefficient node to delete
// return: returns 0 if successful
///////////////////////////////////////////////////////
int deleteNext(polyNode *current)
{
    polyNode *toDelete;
    if (current->next == NULL) {
        // Next is tail => cannot remove node
        return -1;
    } else {
        // 1. Keep pointer to node to be deleted
        toDelete = current->next;
        // 2. Set successor of current to successor of node to be deleted
        current->next = toDelete->next;
        // 3. Delete node from memory
        free(toDelete);
  }
  return 0;
}
