#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct persona persona;
//estructura de tipo persona para guardar su id unico, su peso y su calificacion
struct persona{
    char  idUnico[20];
    int peso;
    int calificacion;
    
};


//funcion que tiene como objetivo mostrar por pantalla las combinaciones y escribirlas en el archivo de salida
//entrada: int para calificaciones, string para el id de los postulantes, entero para los pesos, entero para la cantidad de postulantes
//y el tipo de dato FILE para el archivo de salida
//salida: por pantalla muestra las combinaciones y a escribe en el archivo de salida
void mostrarCombinaciones(int* cal, char** id, int* weight, int n,int limite, FILE * tripulacion){
    int i;
    int suma = 0;
    for ( i = 0 ; i < n ; i++){
        suma = suma + weight[i];
        printf("%s %d %d \n",id[i],weight[i],cal[i]);
    }
    if(suma <= limite){
        printf("%s %d %d \n",id[i],weight[i],cal[i]);
        fprintf (tripulacion, "%s %d %d\n",id[i],weight[i],cal[i]);
        fprintf(tripulacion,"\n");
    }
    printf("\n \n");
}

//funcion que tiene como objetivo ordenar los datos del archivo de entrada
//entradas: tipo de dato FILE con los datos de tripulantes, tipo de dato FILE para el archivo de salida, int con la cantidad de postulantess
//y otro int para la capacidad de la nave
//salida: el archivo de salida con los datos solicitados
void ordenarDatos(FILE * tripulantes,FILE* tripulacion ,int postulantes, int capacidad){
    //creamos tantos estructuras para personas como postulantes haya
    persona candidato[postulantes];
    // sabemos que las columnas del archivo son 3
    int columnas = 3;
    //segun el tamaño del archivo, la cantidad de filas sera igual a los postulantes
    int filas = postulantes;
    //con un ciclo almacenamos en cada estructura los datos de los candidatos
    int i,j;
      for(i= 0;i < filas;i++){
        fscanf (tripulantes, "%s %d %d", candidato[i].idUnico, &candidato[i].peso, &candidato[i].calificacion);
    }
    //mostramos los candidatos disponibles por pantalla
    printf("los postulantes son: \n");
    for(j=0;j<postulantes;j++){
        printf ("%s %d %d \n",candidato[j].idUnico, candidato[j].peso, candidato[j].calificacion);
    }
    //generamos arreglos para almacenar las calificaciones,el id y el peso de los postulantes
    int calificaciones[postulantes];
    char * identificador[postulantes];
    int pesos[postulantes];
    //con otro ciclo vamos guardando 
    int k;
    for(k = 0;k < postulantes;k++){
        calificaciones[k] = candidato[k].calificacion;
        identificador[k]= candidato[k].idUnico;
        pesos[k] = candidato[k].peso;
    }
    //variables auxiliares para hacer el cambio de lugar
    int a,b;
    char * aux;
    //ordenamos los postulantes por sus calificaciones
    for (i = 0; i < postulantes; ++i) {
        for (j = i + 1; j < postulantes; ++j){
            //si la calificacion evaluada en i es menor que la calificacion en j, hacemos el cambio con la ayuda de los auxiliares
            if (calificaciones[i] < calificaciones[j]){
                a =  calificaciones[i];
                calificaciones[i] = calificaciones[j];
                calificaciones[j] = a;
                //se intercambia el lugar de los pesos
                b = pesos[i];
                pesos[i] = pesos[j];
                pesos[j] = b;
                //se intercambia el lugar del postulador
                aux = identificador[i];
                identificador[i] = identificador[j];
                identificador[j] = aux;
            }
        }
    }

    printf("genera combinaciones \n \n");
    for (i = 1; i <= postulantes; i++){
        for (j = 0; j < postulantes-1; j++) {
            a = calificaciones[j];
            calificaciones[j] = calificaciones[j+1];
            calificaciones[j+1] = a;

            b = pesos[j];
            pesos[j] = pesos[j+1];
            pesos[j+1] =b;

            aux = identificador[j];
            identificador[j] = identificador[j+1];
            identificador[j+1] = aux;

            mostrarCombinaciones(calificaciones,identificador,pesos, postulantes,capacidad,tripulacion);
        }
    }
    //fprintf (tripulacion, "This is line %d\n",i); para escribir
    printf("\n \n \n"); 
    printf("Calificaciones en orden descendente: \n");
    for (i = 0; i < postulantes; ++i){
        fprintf (tripulacion, "%s %d %d\n",identificador[i], pesos[i],calificaciones[i]);
        printf(" %s %d %d\n", identificador[i], pesos[i],calificaciones[i]);
    }   
}





int main(){
    //nombre de variable para el archivo que contiene los datos
    FILE * tripulantes;
    //nombre de variable para el archivo de salida
    FILE * tripulacion;
    //se abre ambos archivos, el primero en modo de lectura y el segundo en escritura
    tripulantes = fopen("entrada.in", "r");
    tripulacion = fopen("tripulacion.out", "w");

    //se crea variable para guardar la cantidad de postulantes
    int postulantes;
    //se almacena la cantidad de postulantes mediante fscanf
    fscanf(tripulantes, "%d" , &postulantes);
    printf("cantidad de postulantes: %d\n ", postulantes);
    //se crea variable para guardar la capacida de la nave
    int capacidad;
    //se almacena la capacidad de la nave
    fscanf(tripulantes, "%d" , &capacidad);
    printf("capacidad de la nave: %d\n",capacidad);

    //invocamos la funcion que esta encargada de ordenar datos
    ordenarDatos(tripulantes,tripulacion,postulantes,capacidad);

    //nos aseguramos de cerrar los archivos
    fclose(tripulantes);
    fclose(tripulacion);
    return 0;
}