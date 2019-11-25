///////////////////////////////////////////////////////
// polynomialKevin.c
// implementation of create and delete operation for a 
// polynomial structure
//
// author:	kevin mcandrew
// date:	25.11.2019
///////////////////////////////////////////////////////

/*#include <stdio.h>
#include <stdlib.h>*/
#include "polynomial.h"

/*int main()
{
    double arr[] = {5, 0, 1};
    polyList *poly1 = create();
    fillPoly(poly1, 2, arr);
    printf("%lf", poly1->current->d.coefficient);
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
    new_node->d.coefficient = order;
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
        deleteCoeff(poly->head->next);
    
    // Polynomial is empty, so head and polynomial need to
    // be freed
    free(poly->head);
    free(poly);
    return 0;
}

///////////////////////////////////////////////////////
// deleteCoeff(toDelete)
// Deletes and frees up memory for a particular node
//
// parameter:  toDelete - the coefficient node to delete
// return: returns 0 if successful
///////////////////////////////////////////////////////
int deleteCoeff(polyNode *toDelete)
{
    // Save address of toDelete so that it can be deleted
    polyNode *node = toDelete;
    
    // Remove the coefficient from the polynomial
    toDelete = toDelete->next;
    free(node);

    return 0;
}
