#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int * crearArray(int tamanio){
    srand(time(NULL));
    int * arreglo = (int*)malloc(sizeof(int)*tamanio);

    for (int i = 0; i < tamanio; ++i){
        arreglo[i] = rand()%50 + 1;
    }
    return arreglo;
}
/*************************************************/
//Funcion que soluciona el problema de manera iterativa
//como entrada recibe el arreglo original, el arreglo donde guardara la solucion
//el tamaño del arreglo y el numero buscado
int opcionIterativa(int arreglo[],int solucion[],int tamanio,int resta){
    int j,k;
    for(j = 0; j < tamanio; j++){
        for(k = 0;k < tamanio; k++){
            if ((arreglo[k]-arreglo[j]) == resta){
                solucion[0] = 1;
                solucion[1] = arreglo[k];
                solucion[2] = arreglo[j];
            }

        }
    }
    return 0;
}
//Funcion que soluciona el problema de manera recursiva
//Como entrada tiene el arreglo original,el inicio de este, su tamaño
//el numero a buscar y el arreglo que guardara la solucion
int opcionRecursiva(int arreglo[],int inicio,int tamanio,int resta,int solucion[]){
    if(arreglo[inicio]-arreglo[tamanio] == resta){
        solucion[0] = 1;
        solucion[1] = arreglo[inicio];
        solucion[2] = arreglo[tamanio];
        return 1;
    }
    else if(arreglo[tamanio]-arreglo[inicio] == resta){
        solucion[0] = 1;
        solucion[1] = arreglo[tamanio];
        solucion[2] = arreglo[inicio];
        return 1;
    }
    else if(inicio < tamanio){
        return opcionRecursiva(arreglo,inicio+1,tamanio,resta,solucion);
    }
    else if(inicio == tamanio){
        return opcionRecursiva(arreglo,0,tamanio-1,resta,solucion);
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
        int respuesta = opcionRecursiva(arreglo,0,n-1,d,solucion);
        if (respuesta == 1){
            printf("%d %d %d", solucion[0],solucion[1],solucion[2]); 
        }
        else{
            printf("%d %d %d", solucion[0],solucion[1],solucion[2]); 
        }

    }
    

    /**************************/
    free(arreglo);
    return 0;
}