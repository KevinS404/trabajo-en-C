#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <math.h>
#include "funciones.h"


#define MIN_ENERGY 0.001
#define CONSTANT 1000


int main(int argc, char *const argv[])
{

	char * nombreEntrada;
    char * nombreSalida;

    int  tamanio = 0, contador = 0, flag = 0, hebras = 0, lineas = 0, buffer = 0;
    int flagN = 0,flagh = 0,flagc = 0,flagi = 0, flago = 0,flagb = 0;


    // Funcion getopt para obtener los argumentos de la linea de comando
    while((contador = getopt(argc, argv,"N:c:i:o:b:h:D")) != -1)
    {
        switch (contador)
        {
        case 'N': // Numero de celdas
            tamanio = atoi(optarg);
            flagN = 1;
            break;
        case 'h': // Numero de hebras
            hebras = atoi(optarg);
            flagh = 1;
            break;
        case 'c': // Numero de lineas archivo de entrada
            lineas = atoi(optarg);
            flagc = 1;
            break;
        case 'i': // Nombre del archivo de entrada
             nombreEntrada = optarg;
             flagi = 1;
            break;
        case 'o': // Nombre del archivo de salida
            nombreSalida = optarg;
            flago = 1;
            break;
        case 'b': // Numero de buffer
            buffer = atoi(optarg);
            flagb = 1;
            break;
        case 'D':
            flag = 1;
            break;
            
        case '?':
            if (optopt == 'N' || optopt == 'i'|| optopt == 'o' || optopt == 'c' || optopt == 'h'|| optopt == 'b')
            {
                fprintf(stderr, "Option -%c requiere un argumento.\n",optopt);
            }
            else if (isprint(optopt))
            {
                fprintf(stderr, "Option -%c desconocida.\n",optopt);
            }
            else{
                fprintf(stderr, "Option -%x no reconocida.\n",optopt);
            }
            return 1;
        default:
            abort();
            break;
        }
    }
    
    // Comprobacion de parametros y argumentos
    if (flagN == 0 || flagi == 0 || flago == 0 || flagh == 0 || flagc == 0 || flagb == 0)
    {
        printf("Falta de parametros o argumentos -N, -i o -o.\n");
        return 1;
    }

    if (lineas < hebras)
    {
        printf("LA CANTIDAD DE HEBRAS DEBE SER MENOR O IGUAL A LA CANTIDAD DE LINEAS \n");
        return 1;
    }

    if (buffer == 0 || hebras == 0)
    {
        printf("BUFFER Y HEBRAS TIENEN QUE SER MAYOR QUE 0\n");
        return 1;
    }

    printf(" N = %d \n lineas = %d \n nombreEntrada = %s \n nombreSalida = %s \n buffer = %d \n hebras = %d \n"
    	,tamanio,lineas,nombreEntrada,nombreSalida,buffer,hebras );
	
    // Se inicializan las hebras
    pthread_t hebras_creadas[hebras];

    // Se crea el arreglo que contendra el resultado final
    // Que es global
    particulasTotal = (float *)malloc(sizeof(float)*tamanio);
    
    // Se inicializan los mutex y variables de condicion
    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_init(&mutexParticula,NULL);
    pthread_cond_init(&lleno,NULL);
    pthread_cond_init(&vacio,NULL);

    int cantidadParticulas;
    int cociente = lineas/hebras;
    int resto = lineas%hebras;

    // Se da un valor a la variable global tamanioGlobal
    tamanioGlobal = tamanio;
     
    // Se crean las hebras
    for (int i = 0; i < hebras; ++i)
    {

        if(i + 1 == hebras){

            cantidadParticulas = cociente + resto;
            if(0 != pthread_create(&hebras_creadas[i],NULL,&funcionConsumidora,(void *)&cantidadParticulas)){
                printf("NO SE CREO LA HEBRA -------------------\n");
                return 1;
            }
        }
        else{
            
            int cantidadParticulas2 = cociente;
            if(0 != pthread_create(&hebras_creadas[i],NULL,&funcionConsumidora,(void *)&cantidadParticulas2)){
                printf("NO SE CREO LA HEBRA -------------------\n");
                return 1;
            }
        }
        
    }  

    // Comienza a leer el archivo
    leerArchivo(nombreEntrada,lineas,buffer);

     
	// Se espera a cada hebra
	for (int i = 0; i < hebras; ++i)
	{

		pthread_join(hebras_creadas[i],NULL);
	}

	// Se destruyen los mutex y variables de condicion
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutexParticula);
    pthread_cond_destroy(&lleno);
    pthread_cond_destroy(&vacio);


    float mayor;
    // Se escribe el resultado final
    mayor = escribirArchivos(nombreSalida,particulasTotal,tamanio);

    // Segun el parametro dado -D se muestra por stdout
    if(flag == 1)
        niceprint(tamanio,particulasTotal,mayor);

    free(particulasTotal);
    free(particulas);

	return 0;
}

// Entrada: Nombre del archivo con las particulas, la cantidad de lineas y el tamaño del buffer
// Funcionamiento: Lee el archivo de entrada y ademas coloca las particulas 
// en un buffer compartido
// Salida: -
void leerArchivo(char * nombreEntrada, int cantidadParticulas, int tamanioBuffer){
    // Abrir el archivo
    FILE * archivo = fopen(nombreEntrada,"r");
    if (archivo == NULL) // Comprobacion del fichero
    {
        printf("Error al abrir el archivo de entrada");
        exit(1);
    }
    else{
        int posicion, energia;

        // Se crea el arreglo compartido con el tamaño del buffer 
        particulas  = (particula *)malloc(sizeof(particula)*tamanioBuffer);


        int i = 0;
        while (i <= cantidadParticulas)
        {
            pthread_mutex_lock(&mutex);

            
            while((indexador+1) == tamanioBuffer ){
                pthread_cond_wait(&lleno,&mutex);
            }

            // Se lee la energia y posicion
            // Comprobando que no sea el ultimo ciclo
            if (i != cantidadParticulas)
            {
                indexador++;
                fscanf(archivo,"%d %d",&posicion , &energia);
                particulas[indexador].energia = energia;
                particulas[indexador].posicion = posicion;
            }
            

            // Se avisa que existen particulas
            pthread_cond_signal(&vacio);
            pthread_mutex_unlock(&mutex);
            

            i++;

        }


        fclose(archivo);
    }
}

// Entrada: Se pasa como puntero void la cantidad de particulas que tiene que calcular cada hebra
// Funcionamiento: Cada hebra recogera sus particulas, hara el calculo y lo 
// escribira en el arreglo global 
// Salida: -
void * funcionConsumidora(void * params){

    int * cantidadParticulas;
    cantidadParticulas = (int*)params;

    particula * arregloParticulas = (particula *)malloc(sizeof(particula)*(*cantidadParticulas));

    
    int i = 0;
    while (i < *cantidadParticulas)
    {
        pthread_mutex_lock(&mutex);
        // Caso que no hayan mas particulas en el arreglo
        while(indexador == -1){ 
            pthread_cond_wait(&vacio,&mutex);
        }
        
        //Obtiene la particula del arreglo "particulas"
        arregloParticulas[i].posicion = particulas[indexador].posicion;
        arregloParticulas[i].energia = particulas[indexador].energia; 
                        
        indexador--; // Se resta la cantidad de particulas en el arreglo
        pthread_cond_signal(&lleno);

        pthread_mutex_unlock(&mutex);

        i++;
    }

    //calcular las particulas con nuevo mutex
     pthread_mutex_lock(&mutexParticula);
     
    // Por cada particula se calcula la energia en todo el material
    for (int i = 0; i < *cantidadParticulas; i++)
    {   
    
        for (int j = 0; j < tamanioGlobal; j++)
        {   
            // Se realiza el calculo
            float numerador = CONSTANT * arregloParticulas[i].energia;
            float denominador = tamanioGlobal * sqrt(abs(arregloParticulas[i].posicion - j)+ 1);
            float resultado = numerador/denominador;

            
            if(resultado >= MIN_ENERGY){ // Sumar solo si sobrepasa el minimo de energia
                particulasTotal[j] = particulasTotal[j] + resultado;
            }
        }      
    }
    pthread_mutex_unlock(&mutexParticula);
    free(arregloParticulas);

 
}

// Entrada: Nombre del archivo de salida, arreglo que representa al material y
// entero con el tamaño del arreglo
// Funcionamiento: Calcula el maximo del arreglo y escribe todo el arreglo en el archivo
// Salida: El numero con la energia mayor
float escribirArchivos(char * nombreSalida,float * arreglo, int tamanio){

    FILE * archivo = fopen(nombreSalida,"w");
    if(archivo == NULL){ // Verificacion del archivo
        printf("NO SE A PODIDO ABRIR EL ARCHIVO");
        exit(1);
    }
    else{
        float mayor = arreglo[0]; // Se asigna un mayor
        int indiceMayor = 0; // Un indice para saber donde se encuentra el mayor

        // Se busca el mayor
        for (int i = 0; i < tamanio; i++)
        {
            if(arreglo[i] > mayor){
                mayor = arreglo[i];
                indiceMayor = i;
            }
            
        }
        // Se escribe el mayor en el archivo
        fprintf(archivo,"%d %f \n", indiceMayor, mayor);
        for (int i = 0; i < tamanio; i++)
        {
            // Se escribe todo el arreglo en el archivo
            fprintf(archivo,"%d %f \n", i, arreglo[i]);
        }
        fclose(archivo);
        return mayor;
    }
    
}


