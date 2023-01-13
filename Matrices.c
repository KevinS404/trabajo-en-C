#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Función que crea la matriz dado el tamaño, se le agregan valores aleatoreamente, en este caso, acorde al tamaño
*/
int ** crearMatriz(int tamanio){
	int ** matriz = (int **)malloc(sizeof(int*)*tamanio);
	for (int i = 0; i < tamanio; ++i){
		matriz[i] = (int *)malloc(sizeof(int)*tamanio);
	}
	for (int i = 0; i < tamanio; ++i){
		for (int j = 0; j < tamanio; ++j){
			matriz[i][j] = rand()%tamanio;
		}
	}
	return matriz;
}


/**  INICIO - ACÁ DEBE IR EL CÓDIGO DEL ESTUDIANTE  **/
/*****************************************************/

//Funcion que recibe como entrada la matriz original, un entero para representar las filas
//un entero para las columnas, el tamaño de la matriz y una variable que almacenara el mayor
//valor encontrado
int busqueda(int ** matriz, int fila,int columna, int tamanio,int mayor){
    if (fila > tamanio){
        return mayor;
    }
    if (mayor < matriz[fila][columna] ){
        mayor = matriz[fila][columna];
        }
    if (mayor < matriz[fila+1][columna]){
        mayor = matriz[fila+1][columna];
    }
    if(fila+1 <= tamanio && columna < tamanio){
        return busqueda(matriz,fila,columna+1,tamanio,mayor);
    }
    else if(columna == tamanio && fila+1 < tamanio){
        return busqueda(matriz,fila+1,0,tamanio,mayor);

    }
    
}


/*****************************************************/
/**  FIN - ACÁ DEBE IR EL CÓDIGO DEL ESTUDIANTE  **/


/*
FUNCIÓN PRINCIPAL
*/
int main(){
	int n, i=0, validacion = 0; //Varibles a utilizar dentro del código
	while (validacion == 0){ //Validación de que el valor ingresado por el usuario sea una potencia de 2.
		printf("Ingrese el tamanio de la matriz, cuyo valor sea resultado de una potencia de 2:");
		scanf("%d",&n);
		while((int)pow(2,i) <= n){
			if((int)pow(2,i)==n)
				validacion = 1;
			i++;
		}
		if(validacion == 0){
			printf("\nEl valor ingresado no es valido para el problema.\n");
		}
	}
	//Se crea la matriz a trabajar
	int ** matriz = crearMatriz(n);

	//*** ACÁ EL ALUMNO DEBERÁ LLAMAR A LA FUNCIÓN QUE CREO
	/********************************************************/
	int mayor = 0;
    int resultado = busqueda(matriz,0,0,n-1,mayor);
    printf("\nel mayor indice de criticidad es: %d\n",resultado);
    
	/********************************************************/
	//*** FIN DEL 

	printf("La matriz es:\n");
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < n; ++i){
		free(matriz[i]);
	}
	free(matriz);

	return 0;
}
