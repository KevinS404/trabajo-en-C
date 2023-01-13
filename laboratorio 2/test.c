#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

void energiaDepositada(float *arreglo,int j, int n, float energiaP){
    int i;
    float energiaD;
    float MIN_ENERGY = (1/1000)/n;
    for(i = 0; i < n; i++){
        energiaD = (1000*energiaP)/(n*sqrt(abs(j-i)+1));
        if (energiaD >= MIN_ENERGY){
            arreglo[i] = arreglo[i] + energiaD;
        }
    }
}


int main(){
    int n = 35;
    float arreglo[n],energia;
    FILE * archivoEnergia;
    archivoEnergia = fopen("test1_35.txt", "r");
    int cantidadParticulas;
    fscanf(archivoEnergia, "%d" , &cantidadParticulas);
    int i,posicion;
    for (i=0; i < cantidadParticulas;i++){
        fscanf(archivoEnergia, "%d" , &posicion);
        fscanf(archivoEnergia, "%f" , &energia);
        energiaDepositada(arreglo, posicion, n, energia);
    }
    for(i=0;i < n;i++){
        printf("posicion %d: %f \n",i, arreglo[i]);
    }

    fclose(archivoEnergia);
    return 0;
}
/*
int main(int argc, char * const argv[], const char *optstring){
    int option;
    while((option = getopt(argc, argv, "cf")) != -1){
        switch (option){
        case 'c':
            printf("Quieres grados celcius\n");
            break;
        
        case 'f':
            printf("Quieres grados farenheit\n");
            break;
        default:
            printf("Error");
        }
    }
    
    
    
    return 0;
}
*/