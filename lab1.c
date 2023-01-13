#include<stdio.h>
#include<stdlib.h>



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

pila * torreA;
pila * torreB;
pila * torreC;
int x;

// creación de una pila vacía
pila * crearPila(){
    pila * p = malloc(sizeof(pila));
    p->array = malloc(INIT_SIZE_STACK*sizeof(int));
    p->largo = INIT_SIZE;
    p->top = -1;
    return p;
}
// consulta si la pila está vacía
int pilaVacia(pila *S){
    if (S->top != 0){
        return(S->top>=0);
    }
    else{
        return printf("error");
    }
    return 0;
}


// efectúa un push de x en la pila S
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

// efectúa un pop de la pila S dejando el resultado en *x
// retorna verdadero o falso dependiendo si la pila está vacía
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
// busca el elemento x en la pila *S, retorna verdadero o falso si lo encuentra o no
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


void imprimir_pila(pila *S){
    int i;
    for (i = 0; i <= S->top; i++){
        printf("%d, ", S->array[i]);
    }
    printf("\n");
    
}

// funcion general que muestra como se mueven los discos.
void mostrarTorres(){
    printf("torreA:");
    imprimir_pila(torreA);
    printf("torreB:");
    imprimir_pila(torreB);
    printf("torreC:");
    imprimir_pila(torreC);
    printf("\n");
}

//Esta funcion se encarga de
void moverDiscos(int cantidadDeDiscos, pila * origen, pila * destino, pila * auxiliar){
    if (cantidadDeDiscos <= 0){
        return ;
    }
    else{
        moverDiscos(cantidadDeDiscos - 1, origen, auxiliar, destino);
        extraer(origen, &x);
        insertar(destino, x); 
        mostrarTorres();
        moverDiscos(cantidadDeDiscos - 1, auxiliar, destino, origen);
    }
    
} 

void torreDeHanoi(){
    int cantidadDeDiscos;
    // solicitamos la cantidad de discos
    printf("ingrese la cantidad de discos de la torre:");
    scanf("%d", &cantidadDeDiscos);
    //creamos las torres
    torreA = crearPila();
    torreB = crearPila();
    torreC = crearPila(); 

    //llenamos la primera torre
    for (int i = 0; i < cantidadDeDiscos; i++){
        insertar(torreA, cantidadDeDiscos - i);
    }
    
   
    moverDiscos(cantidadDeDiscos, torreA, torreC, torreB);
}

int main(){
    int opcion;
    printf("1) torres de hanoi\n");
    printf("2) contagios\n");
    printf("3) salir\n");
    while (opcion != 3){
        printf("ingrese una opcion: ");
        scanf("%d", &opcion);
        if(opcion == 1){

            torreDeHanoi();
            printf("1) torres de hanoi\n");
            printf("2) contagios\n");
            printf("3) salir\n");
        }
           
        else if(opcion == 2){
            printf("contagios\n");
            printf("1) torres de hanoi\n");
            printf("2) contagios\n");
            printf("3) salir\n");
        }
        else if(opcion == 3){
            printf("Fin\n");
        }

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