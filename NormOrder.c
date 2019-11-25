polyList normalise(polyList poly1){
  polyList norm;
  double highCoeff;
  highCoeff = order(poly1);
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
