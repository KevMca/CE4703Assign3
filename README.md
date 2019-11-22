# CE4703Assign3

## File structure

* Main.c : interface
* Makefile : make
* Polynomial : module folder
	* polyTest.c : test file
	* polynomial.h : header file
	* polynomial.c : module source file

## Structures
	
~~~~
typedef struct
{
	polyNode *head;
	polyNode *current;
} polyList;	
~~~~
	
~~~~
typedef struct
{
	polyData d;
	struct n *next;
} polyNode;	
~~~~

	
~~~~
typedef struct
{
	double coefficient;
	int order;
} polyData;	
~~~~

## Pseudo code

int create(address of polylist, order of poly, array of coefficients)
{
  
}
int addNode()
delete
add
subtract
multiply
divide
normalise
order
print
