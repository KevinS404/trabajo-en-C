

typedef struct particula
{
    int posicion;
    int energia;
} particula;

extern void niceprint(int N, float *Energy, float Maximum);

pthread_mutex_t mutex;
pthread_mutex_t mutexParticula;
pthread_cond_t lleno, vacio;
particula * particulas;
float * particulasTotal;

int indexador = -1;
int tamanioGlobal;

// Entrada: Nombre del archivo con las particulas, la cantidad de lineas y el tamaño del buffer
// Funcionamiento: Lee el archivo de entrada y ademas coloca las particulas 
// en un buffer compartido
// Salida: -
void leerArchivo(char * nombreEntrada, int cantidadParticulas, int tamanioBuffer);
// Entrada: Se pasa como puntero void la cantidad de particulas que tiene que calcular cada hebra
// Funcionamiento: Cada hebra recogera sus particulas, hara el calculo y lo 
// escribira en el arreglo global 
// Salida: -
void * funcionConsumidora(void * params);
// Entrada: Nombre del archivo de salida, arreglo que representa al material y
// entero con el tamaño del arreglo
// Funcionamiento: Calcula el maximo del arreglo y escribe todo el arreglo en el archivo
// Salida: El numero con la energia mayor
float escribirArchivos(char * nombreSalida,float * arreglo, int tamanio);
