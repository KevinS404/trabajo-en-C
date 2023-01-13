#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Prototipado
int * suma(int * primerNumero, int cantDigitos1, int * segundoNumero, int cantDigitos2, int * cantidadDigitosResultado);
/*
- Complete el código para que se sumen los números guardados en primerNumero y segundoNumero
- La cantidad de dígitos de los números se encuentra guardado en cantDigitos1 y cantDigitos2 respectivamente
- Modifique el parámetro cantidadDigitosResultado por referencia 
  para que guare la cantidad de dígitos del resultado de la suma
*/
int * suma(int * primerNumero, int cantDigitos1, int * segundoNumero, int cantDigitos2, int * cantidadDigitosResultado)
{
	if(cantDigitos1>=cantDigitos2){
		*cantidadDigitosResultado = cantDigitos1+1;
		int * numeroNuevo = (int *)malloc(sizeof(int)*(*cantidadDigitosResultado));
		for(int i = 0; i<cantDigitos1;i++){
			numeroNuevo[i+1] = primerNumero[i];
		}
		numeroNuevo[0] = 0;
		int j = *cantidadDigitosResultado-1;
		for(int i = cantDigitos2-1;i>=0;i--){
			printf("i: %i, j: %i ", i, j);
			printf("\n");
			numeroNuevo[j] = numeroNuevo[j] + segundoNumero[i];
			if(numeroNuevo[j]>9){
				numeroNuevo[j] = numeroNuevo[j]-10;
				numeroNuevo[j-1] = numeroNuevo[j-1] + 1;
			}
			j = j - 1;
		}
		return numeroNuevo;
	}

	else{
		*cantidadDigitosResultado = cantDigitos2+1;
		int * numeroNuevo = (int *)malloc(sizeof(int)*(*cantidadDigitosResultado));
		for(int i = 0; i<cantDigitos2;i++){
			numeroNuevo[i+1] = segundoNumero[i];
		}
		printf("\n");
		numeroNuevo[0] = 0;
		int j = *cantidadDigitosResultado-1;
		for(int i = cantDigitos1-1;i>=0;i--){
			printf("i: %i, j: %i ", i, j);
			printf("\n");
			//printf("numnuevo %d \n", numeroNuevo[j]);
			//printf("snumero %d \n", segundoNumero[i]);
			numeroNuevo[j] = numeroNuevo[j] + primerNumero[i];
			if(numeroNuevo[j]>9){
				numeroNuevo[j] = numeroNuevo[j]-10;
				numeroNuevo[j-1] = numeroNuevo[j-1] + 1;
			}
			j = j - 1;
		}
		return numeroNuevo;
	}
}/*Fin de su código aquí*/

int main(){
	
	srand(time(NULL));
	/*int cantDigitos1 = rand()%101 + 1;
	int cantDigitos2 = rand()%101 + 1;*/

	int cantDigitos1 = rand()%3 + 1;
	int cantDigitos2 = rand()%3 + 1;
	
	int *  primerNumero = (int *) malloc(sizeof(int)*cantDigitos1);
	int *  segundoNumero = (int *) malloc(sizeof(int)*cantDigitos2);
	
	printf("numero1: %d digitos \nnumero2: %d digitos \n\n",cantDigitos1,cantDigitos2);
	
	int i;
	for (i=0;i<cantDigitos1;i++){
        primerNumero[i]= rand()%9 + 1;
    }
    for (i=0;i<cantDigitos2;i++){
    segundoNumero[i]= rand()%9 + 1;
    }
	printf("  ");
	
	for (i=0;i<cantDigitos1;i++)
		printf("%d",primerNumero[i]);
	printf("\n");
	printf("+ ");
	for (i=0;i<cantDigitos2;i++)
		printf("%d",segundoNumero[i]);
	printf("\n");
	printf("________________________________________________________________________\n");
	

	int cantidadDigitosResultado = 0;
	int * resultadoSuma = suma(primerNumero, cantDigitos1, segundoNumero, cantDigitos2, &cantidadDigitosResultado);
	for (i=0;i<cantidadDigitosResultado;i++)
		printf("%d ",resultadoSuma[i]);
		printf("\n");
	printf("\n");

	free(primerNumero);
	free(segundoNumero);
	free(resultadoSuma);
	
	return 0;
}