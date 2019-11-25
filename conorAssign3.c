// conorAssign3


#include <stlib.h>
#include <stdio.h>

polyList add(polyList *poly1, polyList *poly2){
  polyList poly3;
  if(order(&poly1) > order(&poly2)){
    int smallOrd = order(&poly2);
    int bigOrd = order(&poly1);
  }
  else{
    int smallOrd = order(&poly1);
    int bigOrd = order(&poly2);
  }

  for(int i = 0; i <= smallOrd; i++){
    poly3.current->d.coefficient = *poly1->current->d.coefficient + *poly2->current->d.coefficient;
    poly1->current = poly1->current->next;
    poly2->current = poly2->current->next;
    addNode(...);
    poly3.current = poly3.current->next;
  }
  
  if(order(&poly1) > order(&poly2)){
    for(int i = smallOrd + 1; i < bigOrd; i++){
      poly3.current->d.coefficient = *poly1->current->d.coefficient
      poly1->current = poly1->current->next;
      addNode(...);
      poly3.current = poly3.current->next;
    }
    poly3.current->d.coefficient = *poly1->current->d.coefficient
  }
  else{
    for(int i = smallOrd + 1; i < bigOrd; i++){
      poly3.current->d.coefficient = *poly2->current->d.coefficient
      poly2->current = poly2->current->next;
      addNode(...);
      poly3.current = poly3.current->next;
    }
    poly3.current->d.coefficient = *poly2->current->d.coefficient
  }

  return poly3;
}

polyList subtract(polyList *poly1, polyList *poly2){
  polyList poly3;
  if(order(&poly1) > order(&poly2)){
    int smallOrd = order(&poly2);
    int bigOrd = order(&poly1);
  }
  else{
    int smallOrd = order(&poly1);
    int bigOrd = order(&poly2);
  }
  for(i
}
