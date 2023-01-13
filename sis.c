#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>





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