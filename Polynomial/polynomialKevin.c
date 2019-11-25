#include "polynomial.h"

int create(polylist *poly, int order, double[] arr)
{
  
}

int addNode(double coefficient, polyNode *current)
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
    new_node->d.coefficient = current->d.order + 1;;
    new_node->next = NULL;
 
    // Link new node to current node
    current->next = new_node;
}

int delete();
