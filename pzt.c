#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct estado estado;

struct estado{
	int *izq; // arreglo binario de 4 elementos [p,z,t,j]
	int *der; // arreglo del lado
	int idEstado; // la numeracion unica del estado
	int estadoAnterior; // la numeracion del estado anterior
	char * transicion;  // un string que marca la transicion
};


int correlativo; // el correlativo que me indica el próximo idEstado


// Funciones de listas
estado crearEstado( int *izq, int * der, int anterior, char * t); // crea un estado
estado * agregarEstado(estado * lista, int * elementos, estado estado); // inserta elemento
estado * sacarElemento(estado * lista, int * elementos); // elimina primer elemento
int estaEstado(estado * lista, int elementos, estado b); // revisa si se encuenta en lista
void mostrarSolucion(estado * lista, int ultimo); // imprime los pasos

// funciones chequear transicion 
int verificarCM(estado estadoActual); // cruzar con misionero
int verificarCC(estado estadoActual); // cruzar con canibal
int verificarCyM(estado estadoActual); // cruzar con M y C
int verificar2M(estado estadoActual); // cruzar 2 misioneros
int verificar2C(estado estadoActual); //cruzar 2 can

// funciones de transicion
estado cruzarM(estado estadoActual); // cruzar Mis
estado cruzarC(estado estadoActual); //cruzar Can
estado cruzarCyM(estado estadoActual); // cruzar c y m
estado cruzar2M(estado estadoActual); // cruzar 2 m

// funciones generales
int esFinal(estado b);  // si es solucion
void imprimirEstado(estado b); // para imprimir
int iguales_estado(estado a, estado b); // si a y b son el mismo estado 
estado estadoInicial(); // genera un estado inicial, usa crear estado

// implementaciones


/////////// La COLA //////////////////



estado crearEstado(int *izq, int *der, int anterior, char * t){
	estado nuevoEstado;
	nuevoEstado.izq = izq;
	nuevoEstado.der = der;
	nuevoEstado.idEstado = correlativo;
	nuevoEstado.estadoAnterior = anterior;
	nuevoEstado.transicion = t;
	correlativo = correlativo + 1;
	return nuevoEstado;
}

// crea una nuevo arreglo de largo *elementos+1
// incrementa *elementos
estado * agregarEstado(estado * lista, int * elementos, estado estadoActual){
	estado * nuevaLista = (estado *)malloc(sizeof(estado)*(*elementos+1));
	for (int i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estadoActual; // copia el contenido de elementos
	*elementos = *elementos+1; // notar que incrementa este contador externo
	free(lista); // libera el arreglo antiguo
	return nuevaLista;
}

// crea un nuevo arreglo de tamaño menor y copia
// el antiguo en el
estado * sacarElemento(estado * lista, int * elementos){
	estado * nuevaLista = (estado *)malloc(sizeof(estado)*(*elementos-1));
	for (int i = 1; i < *elementos; ++i){
		nuevaLista[i-1]=lista[i];
	}
	*elementos = *elementos-1; // notar que se decrementa el contador
	free(lista);
	return nuevaLista;
}

// Verifica si el estado se encuentra en el arreglo
int estaEstado(estado * lista, int elementos, estado b){
	for (int i = 0; i < elementos; ++i){
        if (iguales_estado(lista[i],b)) // revisamos si el estado b es igual al elemento de la lista
          return(1);
	}
    return(0);
}

//////////CHEQUEAR TRANSICIONES///////////////////
//entrada: un struct de tipo estado
//salida: retorna 1 en caso de cumplirse y 0 si no cumple
//objetivo: verifico si puedo cruzar misionero
// debe haber misioneros disponibles y a su vez que el numero de canibales no supere 
// al numero de misioneros
int verificarCM(estado estadoActual){
	if(estadoActual.izq[1]-1 >= 0 && estadoActual.izq[0]<=estadoActual.izq[1]-1){
		//el 1 es para moverse a la derecha
		return 1;
	}
	if(estadoActual.der[1]-1 >= 0 && estadoActual.der[0]<=estadoActual.der[1]-1){
		// el 2 es para moverse a la izquierda
		return 2;
	}
	else{
		return 0;
	}

}


// verifico si puedo cruzar canibal
// debe haber canibales disponobles y que el numero de estes no 
//vaya a superar a los misioneros del otro lado

int verificarCC(estado estadoActual){
	if(estadoActual.izq[0]-1>=0 && estadoActual.der[0]+1<=estadoActual.der[1]){
		//el 1 es para moverse a la derecha
		return 1;
	}
	else if(estadoActual.der[0]-1>=0 && estadoActual.izq[0]+1<=estadoActual.izq[1]){
		// el 2 es para moverse a la izquierda
		return 2;
	}
	else{
		return 0;
	}

    
}

// verifico si puedo cruzar 1 canibal y un misionero
// debe haber de ambos disponibles
// y que no queden mas canibales que misioneros
int verificarCyM(estado estadoActual){
	if(estadoActual.izq[0]-1>=0 && estadoActual.izq[1]-1 >= 0 && estadoActual.izq[0]-1 <= estadoActual.izq[1]-1 && estadoActual.der[0]+1 <= estadoActual.der[1]+1){
		return 1;
	}
	else if(estadoActual.der[0]-1>=0 && estadoActual.der[1]-1 >= 0 && estadoActual.der[0]-1 <= estadoActual.der[1]-1&& estadoActual.izq[0]+1 <= estadoActual.izq[0]+1){
		return 2;
	}
	else{
		return 0;
	}
	
	
}

// verificar si puedo mover 2 misioneros
// debe haber misioneros
// y no deben quedar mas canibales que misioneros
int verificar2M(estado estadoActual){
	if(estadoActual.izq[1]-2 >= 0 && estadoActual.izq[1]-2 >= estadoActual.izq[0]){
		return 1;
	}
	if(estadoActual.der[1]-2 >= 0 && estadoActual.der[1]-2 >= estadoActual.der[0]){
		return 2;
	}
	else{
		return 0;
	}
}
//verificar si puedo mover 2 canibales
//debe haber canibales
//y su numero no debe superar el del lado contrario
int verificar2C(estado estadoActual){
	if(estadoActual.izq[0]-2 >= 0 && estadoActual.der[0]+2 <= estadoActual.der[0]){
		return 1;
	}
	else if((estadoActual.der[0]-2 >= 0 && estadoActual.izq[0]+2 <= estadoActual.izq[0])){
		return 2;
	}
	else{
		return 0;
	}

}

///////////TRANSICIONES//////////////////

//cruzar misionero
estado cruzarM(estado estadoActual){
    int *izq=malloc(sizeof(int)*3);
    int *der=malloc(sizeof(int)*3);
    memcpy(izq,estadoActual.izq,sizeof(int)*3);
   	memcpy(der,estadoActual.der,sizeof(int)*3);
   	int verificador = verificarCM(estadoActual);
   	//verificamos si se puede mover uno a la derecha
   	if(verificador == 1){
   		estadoActual.izq[1] = estadoActual.izq[1]-1;
   		estadoActual.der[1] = estadoActual.der[1]+1;
   		estadoActual.der[2] = 1;

   	}
   	//si no, verificamos si se puede mover a la izquierda
   	else if(verificador == 2){
   		estadoActual.der[1] =estadoActual.der[1]-1;
   		estadoActual.izq[1] =estadoActual.izq[1]+1;
   		estadoActual.izq[2] = 1;
   	}
	return crearEstado(izq, der, estadoActual.idEstado, "cruzarM");
}


// cruzar canibal
estado cruzarC(estado estadoActual){
    int *izq=malloc(sizeof(int)*3);
    int *der=malloc(sizeof(int)*3);
    memcpy(izq,estadoActual.izq,sizeof(int)*3);
    memcpy(der,estadoActual.der,sizeof(int)*3);
    int verificador = verificarCC(estadoActual);
    //verificamos si se puede mover uno a la derecha
   	if(verificador == 1){
   		estadoActual.izq[0] = estadoActual.izq[0]-1;
   		estadoActual.der[0] = estadoActual.der[0]+1;
   		estadoActual.der[2] = 1;
   	}
   	//si no, verificamos si se puede mover a la izquierda
   	else if(verificador == 2){
   		estadoActual.der[0] =estadoActual.der[0]-1;
   		estadoActual.izq[0] =estadoActual.izq[0]+1;
   		estadoActual.izq[2] = 1;
   	}
   
	return crearEstado(izq, der, estadoActual.idEstado, "cruzarC");
}

// cruzar misionero y canibal
estado cruzarCyM(estado estadoActual){
    int *izq=malloc(sizeof(int)*3);
    int *der=malloc(sizeof(int)*3);
    memcpy(izq,estadoActual.izq,sizeof(int)*3);
    memcpy(der,estadoActual.der,sizeof(int)*3);
    int verificador = verificarCyM(estadoActual);
    //verificamos si se puede mover ambos a la derecha
    if(verificador == 1){
    	estadoActual.izq[0] = estadoActual.izq[0]-1;
    	estadoActual.izq[1] = estadoActual.izq[1]-1;
    	estadoActual.der[0] = estadoActual.der[0]+1;
    	estadoActual.der[1] = estadoActual.der[1]+1;
    	estadoActual.der[2] = 1;
    }
    //verificamos si se puede mover ambos a la izquierda
    if(verificador == 2){
    	estadoActual.der[0] = estadoActual.izq[0]-1;
    	estadoActual.der[1] = estadoActual.izq[1]-1;
    	estadoActual.izq[0] = estadoActual.der[0]+1;
    	estadoActual.izq[1] = estadoActual.der[1]+1;
    	estadoActual.izq[2] = 1;

    }
	return crearEstado(izq, der, estadoActual.idEstado, "cruzarCyM");
}


//cruzar 2 misioneros
estado cruzar2M(estado estadoActual){
    int *izq=malloc(sizeof(int)*3);
    int *der=malloc(sizeof(int)*3);
    memcpy(izq,estadoActual.izq,sizeof(int)*3);
    memcpy(der,estadoActual.der,sizeof(int)*3);
    int verificador = verificar2M(estadoActual);
    if(verificador == 1){
    	estadoActual.izq[1] =estadoActual.izq[1]-2;
    	estadoActual.der[1]= estadoActual.der[1]+2;
    	estadoActual.der[2] = 1;
    }
    else if(verificador == 2){
    	estadoActual.der[1] =estadoActual.der[1]-2;
    	estadoActual.izq[1]= estadoActual.izq[1]+2;
    	estadoActual.izq[2] = 1;
    }
   
	return crearEstado(izq, der, estadoActual.idEstado, "cruzar2M");
}
//cruzar 2 canibales
estado cruzar2C(estado estadoActual){
    int *izq=malloc(sizeof(int)*3);
    int *der=malloc(sizeof(int)*3);
    memcpy(izq,estadoActual.izq,sizeof(int)*3);
    memcpy(der,estadoActual.der,sizeof(int)*3);
    int verificador = verificar2C(estadoActual);
    if(verificador == 1){
    	estadoActual.izq[0] = estadoActual.izq[0]-2;
    	estadoActual.der[0] = estadoActual.der[0]+2;
    	estadoActual.der[2] = 1;
    }
    if(verificador == 2){
    	estadoActual.der[0] = estadoActual.der[0]-2;
    	estadoActual.izq[0] = estadoActual.izq[0]+2;
    	estadoActual.izq[2] = 1;
    }

	return crearEstado(izq, der, estadoActual.idEstado, "cruzar2C");
}

//////////FUNCIONES GENERALES///////////////////
// verifica si es la solucion 
int esFinal(estado b){
	if(b.der[0] == 3 && b.der[1] == 3 && b.der[2] == 1){
		return 1;
	}
	else{
		return 0;
	}
  
}

// imprime un estado en particular
void imprimirEstado(estado b){
	printf("IZQ:%d %d %d, DER:%d %d %d \n ", b.izq[0],b.izq[1],b.izq[2],b.der[0], b.der[1], b.der[2]);
}

// muestra los pasos para llegar a la solucion pero al revez
void mostrarSolucion(estado * lista, int ultimo){
	printf("Los pasos son, del ultimo al primero: \n");
	while(lista[ultimo].idEstado != 0){
		printf("%s\n", lista[ultimo].transicion);
		ultimo = lista[ultimo].estadoAnterior;
	}
}

// revisa si ambos estados continen la misma configuracion
int iguales_estado(estado a, estado b) {
  return(a.izq[0]==b.izq[0] &&
         a.izq[1]==b.izq[1] &&
         a.izq[2]==b.izq[2] &&
         a.der[0]==b.der[0] &&
         a.der[1]==b.der[1] &&
         a.der[2]==b.der[2] 
        );
}

// crea el estado inicial
estado estadoInicial() {
    int *izq=malloc(sizeof(int)*3),*der=malloc(sizeof(int)*3);
    izq[0]=izq[1]=3;
    izq[2]= 1;
    der[0]=der[1]=der[2]=0;
    return(crearEstado(izq,der, 0, ""));
}

///////////PRINCIPAL//////////////////
int main(){
	correlativo = 0;
	int canAbiertos = 0;
	int canCerrados = 0;
	estado bActual, bSiguiente;
	estado * abiertos = (estado *)malloc(sizeof(estado)*canAbiertos);
	estado * cerrados = (estado *)malloc(sizeof(estado)*canCerrados);
	//creamos el inicial
	estado inicial = estadoInicial();
	abiertos = agregarEstado(abiertos, &canAbiertos, inicial);
    // mientras existan estados por revisar (abiertos)
	while(canAbiertos > 0){
		bActual = abiertos[0]; // sacamos el primero de la lista de los pendientes(abiertos)
		abiertos = sacarElemento(abiertos, &canAbiertos); // eliminamos el primero de la lista
		cerrados = agregarEstado(cerrados, &canCerrados, bActual); // agregamos a los revisados 
		if(esFinal(bActual) == 1){ // es la solucion buscada?
			printf("Se encontro la solucion\n");
			mostrarSolucion(cerrados,canCerrados-1);
			return 0;
		}else{ // si no es solucion, reviso todas las transiciones posibles

			//cruzarM Puedo cruzar el pato?
			if(verificarCM(bActual) == 1){
				bSiguiente = cruzarM(bActual); // genero el estado
                // verifico si no se paso por el anteriormente
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    // si es un nuevo estado nunca antes visto lo agrego
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1; // lo descarto si no
				}
			}
			//cruzarC Puedo cruzar el zorro?
			if(verificarCC(bActual) == 1){
				bSiguiente = cruzarC(bActual); // genero el estado
                // verifico si se paso por el anteriormente
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    // si es un nuevo estado nunca antes visto lo agrego
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1; // lo descarto si no
				}
			}

			//cruzarCyM Puedo cruzar el trigo?
			if(verificarCyM(bActual) == 1){
				bSiguiente = cruzarCyM(bActual); // genero el estado
                // verifico si se paso por el anteriormente
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    // si es un nuevo estado nunca antes visto lo agrego
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;  // lo descarto si no
				}
			}

			//cruzar2M Puede cruzar Juan solo?
			if(verificar2M(bActual) == 1){
				bSiguiente = cruzar2M(bActual); // genero el estado
                // verifico si se paso por el anteriormente
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    // si es un nuevo estado nunca antes visto lo agrego
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1; // lo descarto si no
				}
			}


		} // fin del else caso que no era solucion

        // imprimiendo como estan las colas
		printf("ABIERTOS:\n");
		for (int i = 0; i < canAbiertos; ++i){   
			imprimirEstado(abiertos[i]);
		}
		printf("CERRADOS:\n");
		for (int i = 0; i < canCerrados; ++i){
			imprimirEstado(cerrados[i]);
		}
		printf("__________________________________\n");

	} // vuelvo a revisar si es que quedan pendientes (abiertos)

	return 0;
}

