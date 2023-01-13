#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <getopt.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <math.h>


/*
execl("./bomb","./bomb","-N", argv[2], "-p",argv[4],"-s", 
strNumeroParticulas, "-o", strResto, "-c", argv[6], "-i", argv[8], NULL);
*/
int main(int argc, char * argv[]){
    /*
    Se generan enteros para guardar la opcion que se elige por terminal,
    para la cantidad de celdas del arreglo, la cantidad de lineas, el numero
    de particulas que ve cada proceso, el resto del calculo para cada proceso,
    k para iterar, posicion para guardar la posicion que se lee del archivo,
    verificador para la funcion niceprint y p para la cantidad de procesos totales.
    */
    int opcion,n,c,nParticulas,resto,verificador,posicion,p;
    //Se genera un arreglo para almacenar los pids de los hijos que se vayan creando
    int pids[p-1];
    //se genera un arreglo con la cantidad de particulas, asi como 2 floats para
    //almacenar los calculos de la energia
    float energia,energiaD;
    //se calcula la energia minima necesaria para depositar energia en una celda
    float MIN_ENERGY = (1/1000)/nParticulas;
    FILE * archivoEnergia;
    FILE * archivoSalida;
    while((opcion = getopt(argc, argv, "N:p:s:o:c:i:e:D")) != -1){
            switch (opcion){
            //En el caso de la "n" capturamos el numero que la acompaña para tener la cantidad
            //de celdas para el arreglo
            case 'N':
                n = atoi(argv[2]);
                break;
            //Numero de lineas del archivo
            case 'p':
                p = atoi(argv[4]);
                break;
            //Numero de particulas para cada proceso
            case 's':
                nParticulas = atoi(argv[6]);
                break;
            //numero que contiene el resto 
            case 'o':
                resto = atoi(argv[6]);
                break;
            //Lineas del archivo
            case 'c':
                c = atoi(argv[8]);
                break;
            //En el caso de la "i", se abrira el archivo con el nombre guardado en argv[4]
            //en modo lectura para su posterior uso
            case 'i':
                archivoEnergia = fopen(argv[12], "r");
                break;
            case 'e':
                archivoSalida = fopen(argv[14], "w");
                break;
            case 'D':
                verificador = atoi(argv[16]);
                break;
            }
        }

	//Ahora con un ciclo creamos los procesos restantes que se necesitan
    //para calcular la energia en las celdas
    int i,j,k,l;
    float arreglo[nParticulas];
    for(i = 0; i < nParticulas;i++){
        arreglo[i] = 0;
    }
    int pipes[p][2];
    for (i = 0; i < p; i++) {
        if (pipe(pipes[i]) == -1) {
            printf("No se pudo crear este pipe\n");
            return 1;
        }
    }
    for(i = 0; i < p-1;i++){
        pids[i]= fork();

        //Se verifica que el proceso hijo se haya creado correctamente
        if(pids[i]<0){
        printf("No se ha podido crear el proceso hijo\n");
		exit(EXIT_FAILURE);
        }
        
        //proceso hijo
        if(pids[i]==0){
            printf("Proceso hijo %d creado \n", i+1);
            for (j = 0; j < p; j++) {
                //Si estamos en un indice distinto, cerramos el pipe de lectura
                //para evitar errores, si no, lo mantenemos abierto para usarlo
                if (i != j) {
                    close(pipes[j][0]);
                }
                //Se hace algo parecido para el pipe de escritura, pero se evalua
                //con el indice i + 1
                if (i + 1 != j) {
                    close(pipes[j][1]);
                }
            }
            //Se lee lo que hay en el pipe actual, retornando un error
            //en caso de que la lectura falle

            /*
            SE DEJA COMENTADO ESTA PARTE DEL CODIGO DEBIDO A QUE
            NO DEJA QUE LA EJECUCION DEL RESTO DEL PROGRAMA SIGA
            if (read(pipes[i][0], arreglo, sizeof(int)*n) == -1) {
                printf("Error al leer\n");
                return 2;
            }
            */
            //ahora segun la cantidad de particulas recorremos todo el arreglo
            //calculando la energia depositada en cada celula segun la energia de
            //de cada particula y su posicion con la implementacion de la formula
            //presentada en el enunciado
            for (l=0; l < nParticulas;l++){
                fscanf(archivoEnergia, "%d" , &posicion);
                fscanf(archivoEnergia, "%f" , &energia);
                //printf("Posicion: %d Energia: %f \n", posicion,energia);
                for(k = 0; k < n; k++){
                energiaD = (1000*energia)/(n*sqrt(abs(posicion-k)+1));
                if (energiaD >= MIN_ENERGY){
                    arreglo[k] += energiaD;
                    }
                }   
            }
            //Ahora se escribe en el siguiente pipe el arreglo, retornando un error
            //en el caso en que la escritura falle
            if (write(pipes[i + 1][1], arreglo, sizeof(int)*n) == -1) {
                printf("Error al escribir\n");
                return 3;
            }
            
            
            //cerramos el pipe de lectura actual y el de escritura siguiente
            close(pipes[i][0]);
            close(pipes[i + 1][1]);
            //Con este retorno nos aseguramos de que los procesos ejecuten el 
            //ciclo mas de lo necesario, creando asi mas hijos
            return 1;
        }
    }
    //Esperamos a que todos los procesos hijos se terminen de ejecutar
    for(i = 0; i < p-1;i++){
        wait(NULL);
    }

    //PROCESO PADRE

    int proceso1;
    proceso1 = nParticulas + resto;;
    printf("Proceso hijo %d creado \n",p);
    for (i=0; i < proceso1;i++){
        fscanf(archivoEnergia, "%d" , &posicion);
        fscanf(archivoEnergia, "%f" , &energia);
        //printf("Posicion: %d Energia: %f \n", posicion,energia);
        for(k = 0; k < n; k++){
            energiaD = (1000*energia)/(n*sqrt(abs(posicion-k)+1));
            if (energiaD >= MIN_ENERGY){
                arreglo[k] += energiaD;
            }
        }   
    }
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
    fprintf(archivoSalida, "%d %f \n",posicion,max);
    //ahora nuevamente recorremos el archivo escribiendo cada una de las energias
    //registradas con su posicion respectiva
    for(i=0;i<n;i++){
        fprintf(archivoSalida, "%d %f \n",i,arreglo[i]);
    }
    fclose(archivoEnergia);
    fclose(archivoSalida);
    return 0;
}

