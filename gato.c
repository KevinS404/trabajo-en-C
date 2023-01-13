#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int cambio(char * palabra, int n){
  int x = 0;
  int y = 1;
  char aux[5];
  aux[] = palabra[];
  char lista[120];
  lista[0]= palabra;
  while(x < 120){
    aux[x] = aux[x+1];
    aux[x+1]= aux[x];
    lista[y] = aux;
    x = x + 1;
    y = y + 1;

  }
  return lista;
}
void leer(char lista){
  int i;
  for(i= 0;i<120;i++){ 
     printf("%s",lista[i]);
  }
}
int main(){
  char palabra[5];
  printf("Ingrese una palabra de 4 o 5 letras: ");
  scanf("%s",palabra);
  printf("Las permutaciones de la palabra ingresada son: \n");
  int n = strlen(palabra);
  leer(cambio(palabra,n));
 
  

  return 0;
}
