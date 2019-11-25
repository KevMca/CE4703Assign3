polyList normalise(polyList *poly1){
  polyList norm; // variable to store value before returned
  double highCoeff; // stores coefficient of highest order
  int order; // stores highest order
  order = order(poly1); // calls order function to find highest order
  for(int i =0; i < order; i++) // for loop from 0 to order in increments of 1
    {
      current = poly1->current->next; // sets current to next value
    }

  highCoeff = poly1->current->d.coefficient; // stores coefficient
  norm =  polyList divide(poly1, highCoeff); // calls dividing function
  return norm; // returns coefficient of highest order 
}

int order(polyList *poly1){
  int length; // variable to store highest order in polyList
  for(int i=0; i =< (poly1->order); i ++) // for loop from 0 to length of polylist 
    {
      if(poly1->current->d.coefficient !=0) // if poly1's coefficient is not equal to 0 
	{
	  length = i; // length is highest order that is not equal to 0
	} 
      current = poly1->current->next; // sets current to next value
    }
  return length; // returns most significant order
}
