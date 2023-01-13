#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int * crearArray(int tamanio){
    //srand(time(NULL));
    int * arreglo = (int*)malloc(sizeof(int)*tamanio);

    for (int i = 0; i < tamanio; ++i){
        arreglo[i] = rand()%50 + 1;
    }
    return arreglo;
}
/*************************************************/
int opcionIterativa(int arreglo[],int solucion[],int tamanio,int resta){
    int j,k;
    int contador = 0;
    for(j = 0; j < tamanio; j++){
        for(k = 0;k < tamanio; k++){
            if ((arreglo[k]-arreglo[j]) == resta){
                solucion[0] = 1;
                solucion[1] = arreglo[k];
                solucion[2] = arreglo[j];
                contador++;
            }

        }
    }
    return 0;
}

int opcionRecursiva(int arreglo[],int inicio,int tamanio,int resta){
    if(arreglo[inicio]-arreglo[tamanio] == resta){
        return 1;
    }
    else if(inicio < tamanio){
        return opcionRecursiva(arreglo,inicio+1,tamanio,resta);
    } 
    else if(inicio > tamanio){
        return opcionRecursiva(arreglo,inicio-1,tamanio,resta);

    }
    else if(inicio == tamanio){
        return opcionRecursiva(arreglo,inicio,tamanio-1,resta);
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
    int solucion[3] = {0,0,0};
    printf("1 - es para la solucion iterativa\n2 - es para la solucion recursiva");
    int opcion;
    printf("\nEliga la solucion que desee: ");
    scanf("%d",&opcion);
    if(opcion == 1){
        int respuesta = opcionIterativa(arreglo,solucion,n,d);
        printf("%d %d %d", solucion[0],solucion[1],solucion[2]);   
    }
    else if(opcion == 2){
        int respuesta = opcionRecursiva(arreglo,0,n-1,d);
        if (respuesta == 1){
            printf("si");
        }
        else{
            printf("no");
        }
        //printf("%d %d %d", solucion[0],solucion[1],solucion[2]); 

    }
    

    /**************************/
    free(arreglo);
    return 0;
}