#include<stdio.h>
#include<stdlib.h>
#define INIT_SIZE_STACK 100 // tamaño inicial de una pila
// el tipo de dato de una pila
typedef struct spila {
	int * array; // puntero a la localización del arreglo.
	int size; // tamaño máximo de la pila.
	int top; // índice que indica donde está el elemento que se encuentra en el tope de la pila.
} pila;
// creación de una pila vacía
pila* crear_pila(){
	pila *p = malloc(sizeof(pila));
	p->array = malloc(INIT_SIZE_STACK*sizeof(int));
	p->size=INIT_SIZE_STACK;
	p->top=-1; // se considera vacía si top es la posición -1
return p; // ojo que retorna el puntero
}

// consulta si la pila está vacía
int pilaVacia(pila *S){
	if (S->top != 0){
		return(S->top>=0);
	}
	else{
		return -1;
	}
	return 0;
}

// efectúa un push de x en la pila S
int insertar(pila *S, int x){
// lo siguiente duplica el tamaño del arreglo en caso que falte espacio
	if (S->top+1>S->size){
		S->size=2*S->size;
		S->array=realloc(S->array,S->size*sizeof(int));
	}
	if (S->array == NULL){ // no hay pila
		S->top = S->top + 1;
		S->array[S->top] = x;
		return -1;
}
	return 0;
}
// efectúa un pop de la pila S dejando el resultado en *x
// retorna verdadero o falso dependiendo si la pila está vacía
int extraer(pila *S, int *x){
	if (pilaVacia(S)==0){
		return 0; // retorna falso si no se puede extraer
	}  
	else{
		S->top = S->top - 1;
		*x= S->array[S->top + 1];
		return 1;
	}
}


// busca el elemento x en la pila *S, retorna verdadero o falso si lo encuentra o no
int buscar_pila(pila *S, int x){
	if (pilaVacia(S)== 0){
		return (0);
	}
	else{
		int k;
		for(k=0; k<=S->top; k++){
			if (S->array[k] == x){
			return(1);
			} 
		}
	}	
	return 0;
}
// imprime la pila
int imprimir_pila(pila *S){
	int i;
	for(i=0;i<100;i++){
		printf("%d, ",S[i]);
	}

	return 0;
}
int main(){
	pila torre[3];
    int i,n;
    printf("Ingrese el tamano de las torres\n");
    scanf("%d",&n);
    printf("%d\n",n);
    int j = n;
    torre[1].size = n;
    for(i=0;i<n;i++){
    	torre[1].array[i] == j;
    	j = j - 1;
    }
    for(i=0;i<n;i++){
		printf("%d, ",torre[1].array[i]);
	}

	return 0;
}

