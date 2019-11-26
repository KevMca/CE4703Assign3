// main.c

#include "polynomial.h"

polyList declarePoly(){
  int order;
  
  printf("Please enter the order of the polynomial: ");
  scanf("%d", &order);// temp, to be changed

  double coeff[order+1];

  printf("Please enter the coefficients of the polynomial from least to most significant\n");
  for(int i = 0; i <= order; i++){
    scanf("%i", coeff[i]);
  }

  poly3 = create(order, coeff[]);
  
  return poly3;
}
