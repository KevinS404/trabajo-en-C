#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "funciones.h" 
#include <unistd.h>


/*
Entradas: Se recibe un arreglo con las energias, un archivo para la salida,
el entero n con el numero de celdas y un entero de verificador.

Funcionamiento: esta funcion escribe el archivo de salida, buscando primero el 
numero mas alto entre las energias junto a su posicion y despues escribiendolas
por orden.

Salidas: no se retorna nada.
*/
void escribirSalida(float * arreglo,FILE * salida, int n, int verificador){
    //se genera un entero de iterador y otro para guardar la posicion del
    //numero mas grande, asi como se genera un float para guardar el maximo
    int i,posicion;
    float max;
    max = arreglo[0];
    //con un ciclo recorremos todo el arreglo buscando el numero mas grande
    for(i=0;i < n;i++){
        if (arreglo[i] > max){
            max = arreglo[i];
            posicion = i;
        }
    }
    //escribimos en el archivo la posicion y el numero encontrados en la 
    //primera linea del archivo
    fprintf(salida, "%d %f \n",posicion,max);
    //ahora nuevamente recorremos el archivo escribiendo cada una de las energias
    //registradas con su posicion respectiva
    for(i=0;i<n;i++){
        fprintf(salida, "%d %f \n",i,arreglo[i]);
    }
    //si el verificador entregado en la funcion principal es igual a 1 entonces
    //se hara uso de la funcion niceprint para imprimir por consola 
    //una representacion grafica de las energias.
    if(verificador == 1){
        niceprint(n, arreglo,max);
    }
}

/*
Entradas: Un archivo con las energias, un archivo para la salida,
el entero n con el numero de celdas y un entero de verificador.

Funcionamiento: Esta funcion se encarga de calcular la energia depositada
en cada celda del arreglo segun la cantida de celdas que tenga este, para 
esto se arma una variable energiaD que representara la energia depositada
al momento de hacer el calculo con la funcion presentada en el documento,
si dicha energia es mayor que el minimo de energia entonces esta es añadida 
a la celda correspondiente

Salidas: no se retorna nada.
*/
void energiaDepositada(FILE * energy,FILE * salida, int n, int verificador){
    //se genera un arreglo de floats de tamaño n para representar las n celdas
    //se genera un float para guardar la energia leida y un float para la 
    //energia que se calcule mediante la formula
    float arreglo[n],energia,energiaD;
    //se calcula la energia minima necesaria para depositar energia en una celda
    float MIN_ENERGY = (1/1000)/n;
    //se genera un entero para guardar la cantidad de particulas que se lea en el
    //archivo
    int cantidadParticulas;
    //guardamos la cantidad de particulas que se lee en la primera linea del
    //archivo en la variable anterior
    fscanf(energy, "%d" , &cantidadParticulas);
    //se generan 2 enteros para iterar y uno para guardar la posicion
    //de la particula
    int i,k,posicion;
    //se inicializa el arreglo con 0's
    for(i =0; i < n; i++){
        arreglo[i] = 0;
    }
    //ahora segun la cantidad de particulas recorremos todo el arreglo
    //calculando la energia depositada en cada celula segun la energia de
    //de cada particula y su posicion con la implementacion de la formula
    //presentada en el enunciado
    for (i=0; i < cantidadParticulas;i++){
        fscanf(energy, "%d" , &posicion);
        fscanf(energy, "%f" , &energia);
        for(k = 0; k < n; k++){
            energiaD = (1000*energia)/(n*sqrt(abs(posicion-k)+1));
            if (energiaD >= MIN_ENERGY){
                arreglo[k] += energiaD;
            }
        }   
        
    }
    //terminado todo lo anterior el programa se va a la funcion para escribir
    //el archivo de salida
    escribirSalida(arreglo,salida,n,verificador);
}