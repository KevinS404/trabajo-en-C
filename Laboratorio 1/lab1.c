#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <getopt.h>
#include <time.h>

int main(int argc, char * argv[]){
    //Se usa una variable para calcular el tiempo de ejecuccion del programa
    clock_t inicio;
    inicio = clock();
    //Se generan dos enteros, uno para la opcion que se elija por terminal
    //y otro para guardar el numero de celdas
    int opcion,n;
    //Se generan variables para los archivos de entrada con las energias y
    //el archivo de salida 
    FILE * archivoEnergia;
    FILE * archivoSalida;
    //Verificamos que lo ingresado en la terminal supere los 4 elementos
    //de esta forma nos aseguramos que al menos todo menos la D flag fueron ingresadas
    //Hay que fijarse bien si los argumentos estan en mayuscula o minuscula
    if( argc > 4){
        while((opcion = getopt(argc, argv, "N:i:o:D")) != -1)
            switch (opcion){
            //En el caso de la "n" capturamos el numero que la acompaña para tener la cantidad
            //de celdas para el arreglo
            case 'N':
                n = atoi(argv[2]);
                break;
            //En el caso de la "i", se abrira el archivo con el nombre guardado en argv[4]
            //en modo lectura para su posterior uso
            case 'i':
                archivoEnergia = fopen(argv[4], "r");
                break;
            //En el caso de la "o" se abre un archivo de salida con el nombre guardado
            //en argv[6] en modo lectura, luego se verifica que argc sea o no igual a 8
            //en el caso de serlo, se ingresa la D flag entonces se hara uso de la 
            //funcion niceprint, lo cual se verificara con un entero entregado a la 
            //funcion energiDepositada
            case 'o':
                archivoSalida = fopen(argv[6], "w");
                if(argc == 8){
                    energiaDepositada(archivoEnergia,archivoSalida,n,1);
                }
                else{
                    energiaDepositada(archivoEnergia,archivoSalida,n,0);
                }
                break;
            }
        }
    
    else{
        printf("Faltan argumentos");
    }
    //Se cierran los archivos
    fclose(archivoEnergia);
    fclose(archivoSalida);
    //Se entrega el tiempo que se demoro el programa por pantalla
    printf("Tiempo empleado: %f segundos\n", (clock()-inicio)/(double)CLOCKS_PER_SEC );
    return 0;
}
