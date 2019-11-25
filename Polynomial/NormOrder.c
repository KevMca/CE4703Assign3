polyList normalise(polyList *poly1){
  polyList norm;
  double highCoeff;
  int order;
  order = order(poly1);
  for(int i =0; i < order; i++)
    {
      *poly1->current->next;
      current = poly1->current->next;
    }

  highCoeff = poly1->current->d.coefficient; 
  norm =  polyList divide(poly1, highCoeff);
  return norm;
}

int order(polyList *poly1){
  int length;
  for(int i=0; i =< (poly1->order); i ++)
    {
      if(poly1->current->d.coefficient !=0)
	{
	  
	  length = (poly1List->order);
	}
      *poly1->current->next;
      current = poly1->current->next;
    }
  return length;
}
