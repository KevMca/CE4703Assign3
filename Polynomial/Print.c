

void print(polyList *poly1)
{
  
  for(int i=0; i < (poly1->order); i ++)
    {
      
      printf("%lf x^%d +",(poly1->current->d.coefficient),i);
      
      *poly1->current->next;
      current = poly1->current->next;
    }
  
  printf("%lf", (poly1->order));
}
