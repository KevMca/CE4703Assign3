//polynomial.h
//author: Stephen Gannon
//date: 25/11/19
//purpose: To declare all functions and data structures

#ifndef HEADER_FILEPOLY
#define HEADER_FILEPOLY

typedef struct
{
  	polyNode *head;
  	polyNode *current;
  	int order;
} polyList;

typedef struct
{
  	polyData d;
  	struct n *next
} polyNode;

typedef struct
{
  	double coefficient;
	int order;
} polyData;

int create()
int addNode()
int deleteNode()
polyList add(polyList poly1, polyList poly2)
polyList subtract()
polyList multiply()
polyList divide()
polyList normalise()
int order()
void print(polyList)



#endif
