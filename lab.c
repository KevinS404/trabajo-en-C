//20.495.193-4
//L-3
//Creaccion torres de hanoi: 26/08
//Creacion contagios: 01/09


#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>

// tamaño inicial de una pila
# define INIT_SIZE_STACK  100
# define INIT_SIZE  100

// estructura de pila
typedef struct spila
{
    int * array; // puntero a la localizacion del array.
    int largo; // tamaño maximo de la pila.
    int top; // índice que indica donde está el elemento
             // que se encuentra en el tope de la pila.
}pila;

//Creamos variables necesarias de forma global
pila * torreA;
pila * torreB;
pila * torreC;
int x;

// entrada: ninguna
// salida: Un puntero a una pila de estructura pila.
// objetivo: Crea una pila vacia, le asigna memoria, la 
// rellena y retorna su puntero.
pila * crearPila(){
    pila * p = malloc(sizeof(pila));
    p->array = malloc(INIT_SIZE_STACK*sizeof(int));
    p->largo = INIT_SIZE;
    p->top = -1;
    return p;
}
//entrada: Un puntero a una pila de de estructura pila 
//salida: Retorna 0 o el puntero de top
//objetivo: Consulta si la pila entregada está vacía
int pilaVacia(pila *S){
    if (S->top != 0){
        return(S->top>=0);
    }
    else{
        return printf("error");
    }
    return 0;
}

// entrada: Un puntero a una pila de de estructura pila y un entero
// objetivo: Insertar un elemento al array de la estructura pila.
void insertar(pila * S, int x){
    if (S->top + 1 > S->largo)
    {
        S->largo = 2*S->largo;
        S->array = realloc(S->array, S->largo * sizeof(int));
        if (S->array == NULL)
        {
            printf("Error");
        }
        
    }
    
    S->top = S->top + 1;
    S->array[S->top] = x;
}


// 
// entrada: Un puntero a una pila de estructura pila y un puntero a un entero
// salida: Retorna 1 o 0 dependiendo si puede o no realizar la extraccion de un elemento
// objetivo: Si se puede realizar la accion entonces esta funcion realizara un pop del elemento
// en la pila entregada
int extraer(pila * S, int * x){
    if (S->top == -1)
    {
        return 0; // esta vacia la pila
    }
    else
    {
        S->top = S->top - 1;
        *x = S->array[S->top + 1];
        return 1;
    }
     
}
// entrada: Un puntero a una pila de estructura pila y un entero
// salida: Retorna 1 o 0 dependiendo si puede o no realizar la extraccion de un elemento
// objetivo: Busca el elemento x en la pila entrgada, retorna verdadero o falso si lo encuentra o no
int buscar_pila(pila *S, int x){
    if (pilaVacia(S)== 0){
      return 0;
    }
    else{
        int k;
        for(k=0; k<=S->top; k++){
            if (S->array[k] == x){
            return 1;
            } 
        }
    }   
    return 0;
}


// entrada: Un puntero a una pila de estructura pila.
// objetivo: Se encarga de mostrar que elementos tiene en el momento
// la pila 

void imprimir_pila(pila *S){
    int i;
    for (i = 0; i <= S->top; i++){
        printf("%d ", S->array[i]);
    }
    printf("\n");
}




//entrada: Recibe la cantidad de discos y un puntero de cada una de las pilas de estructura pila
//salida: Basicamente, los discos en la torre C
//objetivo: Mediante recursion se encarga de mover los discos de la torre A a la C, con ayuda
//de la torre B como auxiliar.
void moverDiscos(int discos, pila * original, pila * destino, pila * auxiliar){
    if (discos <= 0){
        return ;
    }
    else{
        moverDiscos(discos - 1, original, auxiliar, destino);
        extraer(original, &x);
        insertar(destino, x); 
        printf("torreA: ");
        imprimir_pila(torreA);
        printf("torreB: ");
        imprimir_pila(torreB);
        printf("torreC: ");
        imprimir_pila(torreC);
        printf("\n");
        moverDiscos(discos-1, auxiliar, destino, original);

    }
    
} 
//entrada: Ninguna
//salida: Ninguna
//objetivo: Esta funcion llama a todas las otras funciones para asi
//mediante recursion poder resolver el problema de las torres de hanoi
void torresDeHanoi(){
    int discos;
    // solicitamos la cantidad de discos
    printf("ingrese la cantidad de discos de la torre:");
    scanf("%d", &discos);
    printf("\n");
    //creamos las torres
    torreA = crearPila();
    torreB = crearPila();
    torreC = crearPila(); 
    //llenamos la primera torre
    for (int i = 0; i < discos; i++){
        insertar(torreA,discos-i);
    }
    printf("torreA: ");
    imprimir_pila(torreA);
    printf("torreB: ");
    imprimir_pila(torreB);
    printf("torreC: ");
    imprimir_pila(torreC);
    printf("\n");
    moverDiscos(discos, torreA, torreC, torreB);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define INIT_SIZE_QUEUE 100
typedef struct scola {
    int head; // el primero de la cola
    int tail; // el lugar desocupado después del último en la cola
    int size; // el largo de la cola
    int capacity; // el largo máximo de la cola
    int *array; // el arreglo que va a contener la cola
} cola;

// entrada: ninguna
// salida: Un puntero a una cola de estructura cola.
// objetivo: Crea una cola vacia, le asigna memoria, la 
// rellena y retorna su puntero.
cola * crear_cola(){
    cola *c = malloc(sizeof(cola));
    c->array = malloc(INIT_SIZE_QUEUE*sizeof(int));
    c->size=0; // largo cero
    c->capacity=INIT_SIZE_QUEUE; // largo máximo inicial
    c->tail=0;
    c->head=0; // se considera vacía si head==tail
    return c;
} // ojo que retorna el puntero

//entrada: Un puntero a una cola de estructura cola.
// salida: Retorna el size de la cola
// objetivo: / pregunta si la cola está llena,si la capacidad actual es igual al tamaño de la cola
int colaLlena(cola *Q){
    return(Q->capacity == Q->size);
}

// entrada: Un puntero a una cola de estructura cola y un entero
// salida: Retorna 1 o 0 dependiendo si puede o no realizar la extraccion de un elemento
// objetivo: encolamos el valor x en Q. Si se acaba el espacio entonces se duplica la capacidad
int encolar(cola * Q, int x){
    if (colaLlena(Q)){ // si esta llena duplicamos capacidad
        Q->capacity=2*Q->capacity; // duplicamos la capacidad
        Q->array=realloc(Q->array,Q->capacity*sizeof(cola));
// en este caso se cumple que head==tail
// movemos lo que está antes de head después del último
       memcpy(Q->array + Q->size, Q->array, Q->head);
        Q->tail = Q->head + Q->size;
            } // después del primero

// ahora se asegura espacio disponible -> encolar
        Q->array[Q->tail] = x;
         // se encola
    if (Q->tail == Q->capacity){ // si se pasó
        Q->tail = 0;
        } // vuelta al inicio
    else{ // si no, puesto disponible en +1
        Q->tail = Q->tail + 1;
        Q->size = Q->size+1;
         } // actualizo el tamaño
}

// se pregunta si la cola está vacía
int colaVacia(cola *Q){
    return(Q->size==0);
}

// entrada: Un puntero a una cola de estructura cola
// salida: se retorna 0 en caso de que la cola este vacia
// y en caso de no estarlo se retorna el elemento X
// objetivo: se saca el primero de la cola y actualizan los números
int desencolar(cola *Q){
    if (colaVacia(Q)){
        return 0;
    }
    else{
        x = Q->array[Q->head]; // el primero
        if (Q->head == Q->capacity){ // si se paso vuelve al inicio
        Q->head = 0;
    }
    else{ // si no se mueve al siguiente
        Q->head = Q->head + 1;
        }
    }
    return x;
}

int main(){
    //creamos una variable para guardar lo que eliga el usuario
    int opcion;
    //printeamos las opciones
    printf("1) torres de hanoi\n");
    printf("2) contagios\n");
    printf("3) salir\n");
    //este ciclo se encarga de que mientras el usuario no eliga salir el programa se seguira ejecutando
    while (opcion != 3){
        printf("ingrese una opcion: ");
        scanf("%d", &opcion);
        //en caso de elegir 1 como opcion, ejecutaremos las torres de hanoi
        if(opcion == 1){
            torresDeHanoi();
            printf("1) torres de hanoi\n");
            printf("2) contagios\n");
            printf("3) salir\n");
            free(torreA);
            free(torreB);
            free(torreC);

        }
        //en caso de elegir 2 como opcion, ejecutaremos el programa de contagios
        else if(opcion == 2){
            char nombre[50];
            printf("1) torres de hanoi\n");
            printf("2) contagios\n");
            printf("3) salir\n");
        }
        //en caso de elegir 3 como opcion, finalizaremos el programa
        else if(opcion == 3){
            printf("Fin del programa\n");
        }
        //esta condicion esta por si el usuario ingresa una opcion que no corresponda
        else{
            printf("OPCION INVALIDA\n");
            printf("ingrese una opcion:\n");
            printf("1 - torres de hanoi\n");
            printf("2 - contagios\n");
            printf("3 - salir\n");
        }
    }
    
    

    return 0;
}