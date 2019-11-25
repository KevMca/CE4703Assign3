#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

int main()
{
    double arr[] = {5, 0, 1};
    polyList *poly1 = create(2, arr);
    printf("%lf", poly1->current->d.coefficient);
}

polyList *create(int order, double arr[])
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
            poly->head->d.coefficient = arr[0];
            poly->head->d.order = 0;
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

    for(int i = 1; i <= order; i++)
    {
        poly->current->next = addCoeff(arr[i], poly->current);
        poly->current = poly->current->next;
    }

    poly->current = poly->head;
    return poly;
}

polyNode *addCoeff(double coefficient, polyNode *current)
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
    new_node->d.coefficient = current->d.order + 1;
    new_node->next = NULL;
 
    // Link new node to current node
    return new_node;
}

//int delete();
