#include <stdio.h>
#include <stdlib.h>

int * crearArray(int tamanio){
    int * arreglo = (int*)malloc(sizeof(int)*tamanio);

    for (int i = 0; i < tamanio; ++i){
        arreglo[i] = rand()%50 + 1;
    }
    return arreglo;
}
/*************************************************/

//Funcion que soluciona el problema de manera recursiva
//Como entrada tiene el arreglo original,el inicio de este, su tamaño
//el numero a buscar y el arreglo que guardara la solucion
int solucionRecursiva(int arreglo[],int inicio,int tamanio,int resta,int solucion[]){
    if(arreglo[inicio]-arreglo[tamanio] == resta && inicio != tamanio){
        solucion[0] = 1;
        solucion[1] = arreglo[inicio];
        solucion[2] = arreglo[tamanio];
        return 1;
    }
    else if(arreglo[tamanio]-arreglo[inicio] == resta && inicio != tamanio){
        solucion[0] = 1;
        solucion[1] = arreglo[tamanio];
        solucion[2] = arreglo[inicio];
        return 1;
    }
    else if(inicio < tamanio){
        return solucionRecursiva(arreglo,inicio+1,tamanio,resta,solucion);
    }
    else if(inicio == tamanio){
        return solucionRecursiva(arreglo,0,tamanio-1,resta,solucion);
    }
    else{
        return 0;
    }

}

/*************************************************/
/*
FUNCIÓN PRINCIPAL
*/
int main(){
    int n, d;
    printf("Ingrese el tamanio del arreglo a generar: ");
    scanf("%d",&n);

    printf("Ingrese la distancia a buscar: ");
    scanf("%d",&d);

    int * arreglo = crearArray(n);

    printf("\nARREGLO: ");
    for (int i = 0; i < n; ++i){
        printf("%d - ",arreglo[i]);
    }
    printf("\n");
    /**************************/
    //se crea un arreglo de tamaño 3 que para almacenar las posibles variables
    //tal como se pide en el enunciado
    int solucion[3] = {0,0,0};
    int respuesta = solucionRecursiva(arreglo,0,n-1,d,solucion);
    if(respuesta == 1){
        printf("Se ha encontrado un par que cumple con la distancia buscada\nPor lo cual el arreglo pedido queda de la siguiente forma:\n");
        printf("%d %d %d", solucion[0],solucion[1],solucion[2]); 
    }
    else if(respuesta == 0){
        printf("NO se ha encontrado un par que cumpla con la distancia buscada\nPor lo cual el arreglo pedido queda de la siguiente forma:\n");

        printf("%d %d %d", solucion[0],solucion[1],solucion[2]); 
    }

    /**************************/
    free(arreglo);
    return 0;
    
}
