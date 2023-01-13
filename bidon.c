#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct nodo{
	int num;
	struct nodo *hijoIzquierdo;
	struct nodo *hijoDerecho;
};
typedef struct nodo nodo;

nodo * crearNodo(int num){
	nodo* nuevoNodo = (nodo*)malloc(sizeof(nodo));
	nuevoNodo->num = num;
	nuevoNodo->hijoIzquierdo = NULL;
	nuevoNodo->hijoDerecho = NULL;
	return nuevoNodo;
}
nodo * insertar(nodo * raiz, nodo * nuevoNodo){
	if(raiz == NULL){
		raiz == nuevoNodo;
	}
	else{
		nodo * aux = raiz;
		noodo * auxAnterior = aux;
		while(aux != NULL){
			if(aux->num > nuevoNodo->num){
				auxAnterior = aux;
				aux = aux->hijoIzquierdo;
			}
			else{
				auxAnterior = aux;
				aux = aux->hijoDerecho;
			}
		}
		if(auxAnterior->num > nuevoNodo->num){
			auxAnterior->hijoIzquierdo = nuevoNodo;
		}
		else{
			auxAnterior->hijoDerecho = nuevoNodo;
		}
	}
	return raiz;
}
int contarNodos(nodo * raiz){
	int contador = 1;
	if(raiz == NULL){
		return 0;
	}
	else{
		contador += contarNodos(raiz->hijoIzquierdo);
		contador += contarNodos(raiz->hijoDerecho);
		return contador;
	}

}

int main(){
	srand(time(NULL));
	nodo * raiz = NULL;
	int i,num;
	int cant = rand() % 101;
	printf("cant: %d \n",cant);
	for(i=0;i<cant;i++){
		num= rand() % 101;
		raiz = insertar(raiz,crearNodo(num));
		printf("%d",num);
	}
	printf("\n \n");
	int totalNodos = contarNodos(raiz);
	printf("\n\nCantidad total de nodos: %d \n",totalNodos);
	return 0;
}