/////////////////////////////////////////////////////////
// polynomialTest.c
//
// main test program for testing Polynomial module and its
// functions. Also gives example implementations to
// demonstrate how the module works
//
// author:      kevin mcandrew
// date:        27.11.2019
/////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

//////////////////////////////////////////////////
// function main()
// entry point from operating system. Defines 
// the main application of this program. Runs a
// series of calculations and prints thems
//////////////////////////////////////////////////
int main(int argc, char **argv)
{
  	/////////////////////////////////////////////////////////
  	// polynomial create and delete
  	/////////////////////////////////////////////////////////
	polyCreate()
	fillyPoly()
	newCoeff()
	polyDelete()
	deleteNext()

	/////////////////////////////////////////////////////////
  	// polynomial operations
  	/////////////////////////////////////////////////////////
  	polyAdd()
  	polySubtract()
  	multiply()
  	divide()
  	polyNormalise()
  	polyOrder()
}
