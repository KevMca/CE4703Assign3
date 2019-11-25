// Author: kevin mcandrew
// create and delete functions

#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

int main()
{
    double arr[] = {5, 0, 1};
    polyList *poly1 = create();
    fillPoly(poly1, 2, arr);
    printf("%lf", poly1->current->d.coefficient);
}

polyList *create()
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
    // Assign head coefficient first
    poly->head->d.coefficient = arr[0];
    poly->head->d.order = 0;

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
    new_node->d.coefficient = order;
    new_node->next = NULL;
 
    // Link new node to current node
    return new_node;
}

int delete()
{
    return 0;
}
