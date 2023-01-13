//20.495.193-4
//L-3
//Creaccion cubo magico: 15/09
//Creacion canibales y misioneros: 19/09
//la primera parte del codigo corresponde a los misioneros y canibales
//la segunda parte esta separada, correspondiendo a los cuadrados magicos (en su mayor parte)
//al final de todo se encuentra la funcion main que inicia el programa

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int verificarCruzarM(estado estadoActual); // cruzar con misionero
int verificarCruzarC(estado estadoActual); // cruzar con canibal
int verificarCyM(estado estadoActual); // cruzar con M y C
int verificar2M(estado estadoActual); // cruzar 2 misioneros
int verificar2C(estado estadoActual); //cruzar 2 can

// funciones de transicion
estado cruzarM(estado estadoActual); // cruzar misionero
estado cruzarC(estado estadoActual); //cruzar canibal
estado cruzarCyM(estado estadoActual); // cruzar canibal  y misionero
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
          return 1;
	}
    return 0;
}

//////////VERIFICACIONES///////////////////
//entrada:para todas las verificaciones, un struct de tipo estado
//salida: retorna 1 en caso de cumplirse y 0 si no cumple
//objetivo: verifico si puedo hacer el cruze en una transicion

//verifico si puedo cruzar misionero
// debe haber misioneros disponibles y a su vez que el numero de canibales no supere 
// al numero de misioneros
int verificarCruzarM(estado estadoActual){
	//el bote esta en la izquierda
	if(estadoActual.izq[2] == 1){
		//verificamos que al restar la cantidad no sea negativa y que a su vez la cantidad de canibales sea menor o igual
		//en el otro lado
		if(estadoActual.izq[1]-1 >= 0 && estadoActual.der[0] <= estadoActual.der[1] ){
			return 1;
		}	
	}
	//el bote esta en la derecha
	if(estadoActual.der[2] == 1){
		//verificamos que al restar la cantidad no sea negativa y que a su vez la cantidad de canibales sea menor o igual
		//en el otro lado
		if(estadoActual.der[1]-1 >= 0  && estadoActual.izq[0]<= estadoActual.izq[1]){
			return 1;
		}

	}

	else{
		return 0;
	}

}


// verifico si puedo cruzar canibal
// debe haber canibales disponibles y que el numero de estes no 
//vaya a superar a los misioneros del otro lado

int verificarCruzarC(estado estadoActual){
	//si el bote esta en la izquierda
	if(estadoActual.izq[2] == 1){
		//verificamos que al restar la cantidad no sea negativa y que al otro lado la cantidad de misioneros sea menor o igual a 3,
		//y que al incrementar la cantidad de canibales esta no supere a los misioneros
		if(estadoActual.izq[0] - 1 >= 0 &&  estadoActual.der[1] <= 3 && estadoActual.der[0]+1 <= estadoActual.der[1]){
			return 1;
		}
	}
	//el bote esta en la derecha
	else if(estadoActual.der[2] == 1){
		//verificamos que al restar la cantidad no sea negativa y que al otro lado la cantidad de misioneros sea menor o igual a 3,
		//y que al incrementar la cantidad de canibales esta no supere a los misioneros
		if(estadoActual.der[0] - 1 >=0 &&  estadoActual.izq[1] <= 3 && estadoActual.izq[0]+1 <= estadoActual.izq[1]){
			return 1;
		}	
	}
	else{
		return 0;
	}

    
}

// verifico si puedo cruzar 1 canibal y un misionero
// debe haber de ambos disponibles
// y que no queden mas canibales que misioneros
int verificarCyM(estado estadoActual){
	//si el bote esta en la izquierda
	if(estadoActual.izq[2]== 1){
		//verificamos que al disminuir el valor no sea negativo para ambos casos, tambien vemos que los canibales de la izquierda no superen a los misioneros de la izquierda
		if(estadoActual.izq[0] - 1>=0 && estadoActual.izq[1] - 1 >= 0 && estadoActual.izq[0]  <= estadoActual.izq[1]){
			return 1;
		}
	}
	//si el bote esta a la derecha
	if(estadoActual.der[2]== 1){
		//verificamos que al disminuir el valor no sea negativo para ambos casos, tambien vemos que los canibales de la derecha no superen a los misioneros de la derecha
		if(estadoActual.der[0] - 1>=0 && estadoActual.der[1] - 1 >= 0 && estadoActual.der[0]-1 <= estadoActual.der[1]-1){
			return 1;
		}
	}
	else{
		return 0;
	}
	
	
}

// verificar si puedo mover 2 misioneros
// debe haber misioneros
// y no deben quedar mas canibales que misioneros
int verificar2M(estado estadoActual){
	//si el bote esta en la izquierda
	if(estadoActual.izq[2] == 1){
		//verificamos si al disminuir la cantidad no se vuelve negativa y que a su vez esta sea mayor que el numero de canibales
		if(estadoActual.izq[1] - 2 >= 0 && estadoActual.izq[1] - 2 >= estadoActual.izq[0]){
		return 1;
		}
	}
	//si el bote esta en la derecha
	else if(estadoActual.der[2]== 1){
		//verificamos si al disminuir la cantidad no se vuelve negativa y que a su vez esta sea mayor que el numero de canibales
		if(estadoActual.der[1] - 2 >= 0 && estadoActual.der[1] - 2 >= estadoActual.der[0]){
			return 1;
		}
	}
	else{
		return 0;
	}
}
//verificar si puedo mover 2 canibales
//debe haber canibales
//y su numero no debe superar el del lado contrario
int verificar2C(estado estadoActual){
	//si el bote esta en la izquierda y el numero al otro lado es menor que 3
	if(estadoActual.izq[2] == 1 && estadoActual.der[1]<3){
		//verificamos que al disminuir no sea un numero negativo y que el numero de misioneros al otro lado sea mayor o igual a 0
		if(estadoActual.izq[0] - 2 >= 0 && estadoActual.der[1] >= 0){
			return 1;
		}
	}
	//si el bote esta en la derecha y el numero al otro lado es menor que 3
	else if(estadoActual.der[2]== 1 && estadoActual.izq[1]<3){
		//verificamos que al disminuir no sea un numero negativo y que el numero de misioneros al otro lado sea mayor o igual a 0
		if(estadoActual.der[0] - 2 >= 0 && estadoActual.izq[1] >= 0){
			return 1;
		}
	}
	else{
		return 0;
	}

}

///////////TRANSICIONES//////////////////
//entrada: todas reciben como entrada un struct de tipo estado
//salida: struct modificada por la transicion
//objetivo: realizar las transiciones correspondientes al estado
//cruzar misionero
estado cruzarM(estado estadoActual){
    int *izq=malloc(sizeof(int)*3);
    int *der=malloc(sizeof(int)*3);
    memcpy(izq,estadoActual.izq,sizeof(int)*3);
   	memcpy(der,estadoActual.der,sizeof(int)*3);
   	//verificamos si se puede mover uno a la derecha
   	if(estadoActual.izq[2] == 1){
   		estadoActual.izq[1] = estadoActual.izq[1]-1;
   		estadoActual.der[1] = estadoActual.der[1]+1;
   		estadoActual.izq[2] = 0;
   		estadoActual.der[2] = 1;

   	}
   	//si no, verificamos si se puede mover a la izquierda
   	else if(estadoActual.der[2] == 1){
   		estadoActual.der[1] =estadoActual.der[1]-1;
   		estadoActual.izq[1] =estadoActual.izq[1]+1;
   		estadoActual.der[2] = 0;
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

    //verificamos si se puede mover uno a la derecha
   	if(estadoActual.izq[2] == 1){
   		estadoActual.izq[0] = estadoActual.izq[0]-1;
   		estadoActual.der[0] = estadoActual.der[0]+1;
   		estadoActual.izq[2] = 0;
   		estadoActual.der[2] = 1;
   	}
   	//si no, verificamos si se puede mover a la izquierda
   	else if(estadoActual.der[2] == 1){
   		estadoActual.der[0] =estadoActual.der[0]-1;
   		estadoActual.izq[0] =estadoActual.izq[0]+1;
   		estadoActual.der[2] = 0;
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
    //verificamos si se puede mover ambos a la derecha
    if(estadoActual.izq[2] == 1){
    	estadoActual.izq[0] = estadoActual.izq[0]-1;
    	estadoActual.izq[1] = estadoActual.izq[1]-1;
    	estadoActual.der[0] = estadoActual.der[0]+1;
    	estadoActual.der[1] = estadoActual.der[1]+1;
    	estadoActual.izq[2] = 0;
    	estadoActual.der[2] = 1;
    }
    //verificamos si se puede mover ambos a la izquierda
    if(estadoActual.der[2] == 1){
    	estadoActual.der[0] = estadoActual.izq[0]-1;
    	estadoActual.der[1] = estadoActual.izq[1]-1;
    	estadoActual.izq[0] = estadoActual.der[0]+1;
    	estadoActual.izq[1] = estadoActual.der[1]+1;
    	estadoActual.der[2] = 0;
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
    if(estadoActual.izq[2] == 1){
    	estadoActual.izq[1] =estadoActual.izq[1]-2;
    	estadoActual.der[1]= estadoActual.der[1]+2;
    	estadoActual.izq[2] = 0;
    	estadoActual.der[2] = 1;
    }
    else if(estadoActual.der[2] == 1){
    	estadoActual.der[1] =estadoActual.der[1]-2;
    	estadoActual.izq[1]= estadoActual.izq[1]+2;
    	estadoActual.der[2] = 0;
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
    if(estadoActual.izq[2] == 1){
    	estadoActual.izq[0] = estadoActual.izq[0]-2;
    	estadoActual.der[0] = estadoActual.der[0]+2;
    	estadoActual.izq[2] = 0;
    	estadoActual.der[2] = 1;
    }
    else if(estadoActual.der[2] == 0){
    	estadoActual.der[0] = estadoActual.der[0]-2;
    	estadoActual.izq[0] = estadoActual.izq[0]+2;
    	estadoActual.der[2] = 0;
    	estadoActual.izq[2] = 1;
    }

	return crearEstado(izq, der, estadoActual.idEstado, "cruzar2C");
}


// verifica si es la solucion 
int esFinal(estado b){
	if(b.izq[0] == 0 && b.izq[1] == 0 && b.izq[2] == 0 && b.der[0] == 3 && b.der[1] == 3 && b.der[2] == 1){
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
         a.der[2]==b.der[2] );
}

// crea el estado inicial
estado estadoInicial() {
    int *izq=malloc(sizeof(int)*3),*der=malloc(sizeof(int)*3);
    izq[0]=izq[1]=3;
    izq[2]= 1;
    der[0]=der[1]=der[2]=0;
    return(crearEstado(izq,der, 0, ""));
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/*
Función que agrega un elmento a una lista de elementos
Entrada: El conjunto de elementos a donde debo agregar el nuevo elemento
				(Cada elemento es una matriz de enteros, por lo que debe ser una lista de matrices)
			La cantidad de elementos que posee este conjunto (Se pasa por referencia)
			El nuevo elemento a agregar (Una matriz de enteros)
Salida: Un nuevo conjunto de elementos
*/
int *** agregarSolucion(int *** conjunto, int * cantElementos, int ** solucion){
    
	//Se crea el nuevo conjunto de soluciones
	int*** conjuntoNuevo = (int ***)malloc(sizeof(int**)*(*cantElementos+1));
	for (int i = 0; i < *cantElementos+1; ++i){
		conjuntoNuevo[i] = (int **)malloc(sizeof(int *)*3);
		for (int j = 0; j < 3; ++j){
			conjuntoNuevo[i][j] = (int *)malloc(sizeof(int)*3);
		}
	}
	//Se copian las soluciones existentes
	for (int numeroSolucion = 0; numeroSolucion < *cantElementos; ++numeroSolucion){
		for(int ejeX = 0; ejeX < 3; ejeX ++){
			for (int ejeY = 0; ejeY < 3; ++ejeY){
				conjuntoNuevo[numeroSolucion][ejeX][ejeY] = conjunto[numeroSolucion][ejeX][ejeY];
			}
		}
	}
	//Se agrega la nueva solución
	for (int ejeXSolucion = 0; ejeXSolucion < 3; ++ejeXSolucion){
		for (int ejeYSolucion = 0; ejeYSolucion < 3; ++ejeYSolucion){
			conjuntoNuevo[*cantElementos][ejeXSolucion][ejeYSolucion] = solucion[ejeXSolucion][ejeYSolucion];
		}
	}
	*cantElementos = *cantElementos+1;
    //liberamos memoria
	free(conjunto);
	return conjuntoNuevo;
}

// funcion que valida si no es transpuesta
int verificarTraspuesta(int *** conjuntoSol, int ** matriz, int cantidadSoluciones){
    int contadorador = 0;
    for (int i = 0; i < cantidadSoluciones; i++){
        if (matriz[0][0] != conjuntoSol[i][0][0] && matriz[0][1] != conjuntoSol[i][1][0] && matriz[0][2] != conjuntoSol[i][2][0]){
            contadorador++;
        }
        
    }

    if (contadorador ==  cantidadSoluciones){
        return 1;
    }
    return 0;

}



/*
Función que imprime una lista de soluciones.
Entrada: Lista de matrices de enteros
*/
void imprimirSoluciones(int *** soluciones, int cantidadSoluciones){
    int numeroSolucion;
	for(numeroSolucion = 0; numeroSolucion < cantidadSoluciones; numeroSolucion++){
		printf("Solucion N=%d\n", numeroSolucion);
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				printf("%d ", soluciones[numeroSolucion][i][j]);
			}
			printf("\n");
		}
	}
	return;	
}
void cuadradoMagico(){
    //Se crea el conjunto de soluciones
    int contador = 0;
    int *** conjuntoSoluciones = (int ***)malloc(sizeof(int**)*contador);
    
    //Se crea una variable para almacenar las soluciones
    int ** matriz = (int **)malloc(sizeof(int*)*3);
    int i;
    for (i = 0; i < 3; ++i){
        matriz[i] = (int *)malloc(sizeof(int)*3);
    }

 

    int m;
    printf("ingrese el valor m:\n");
    scanf("%d", &m);
    for (int i = m; i > 0; i--){
        for (int j = m; j > 0; j--){
            if (j != i){
                for (int k = m; k > 0; k--){
                    if (k != j && k != i){
                        for (int l = m; l > 0; l--){
                            if (l != k && l != j && l != i){
                                for (int n = m; n > 0; n--){
                                    if ( n!= k && n != j && n != i && n != l){
                                        for (int o = m; o > 0; o--){
                                            if (o!= k && o != j && o != i && o != l && o!= n){
                                                for (int x = m; x > 0; x--){
                                                    if (x!= k && x != j && x != i && x != l && x!= n && x!= o){
                                                        for (int y = m; y > 0; y--){
                                                            if (y!= k && y != j && y != i && y != l && y!= n && y!= o && y!= x){
                                                                for (int z = m; z > 0; z--){
                                                                    if (z!= k && z != j && z != i && z != l && z!= n && z!= o && z!= x && z!= y){
                                                                        int sumaFila1  = i + j + k;
                                                                        int sumaFila2  = l + n + o;
                                                                        int sumaFila3  = x + y + z;
                                                                        int sumaColumna1  = i + l + x;
                                                                        int sumaColumna2  = j + n + y;
                                                                        int sumaColumna3  = k + o + z;
                                                                        int sumaDiagonalAscendente = x + n + k;
                                                                        int sumaDiagonalDescendente = i + n + z;
                                                                        if (sumaFila1 == sumaFila2 && sumaFila1 == sumaFila3)
                                                                        {
                                                                            if (sumaColumna1 == sumaColumna2 && sumaColumna1 == sumaColumna3)
                                                                            {
                                                                               
                                                                                if (sumaColumna1 == sumaFila1)
                                                                                {
        
                                                                                    if (sumaDiagonalAscendente == sumaDiagonalDescendente)
                                                                                    {
                                                                                        
                                                                                        if (sumaDiagonalAscendente == sumaFila1 && sumaDiagonalAscendente == sumaColumna1)
                                                                                        {
                                                                                            if (contador == 3)
                                                                                            {
                                                                                                break;
                                                                                            }
                                                                                            
                                                                                            matriz[0][0] = i;
                                                                                            matriz[0][1] = j;
                                                                                            matriz[0][2] = k;
                                                                                            matriz[1][0] = l;
                                                                                            matriz[1][1] = n;
                                                                                            matriz[1][2] = o;
                                                                                            matriz[2][0] = x;
                                                                                            matriz[2][1] = y;
                                                                                            matriz[2][2] = z;
                                                                                            //aqui se verifica que la matriz no este traspuesta
                                                                                            int verificador = verificarTraspuesta(conjuntoSoluciones, matriz, contador);
                                                                                            //si efectivamente la matriz es una que no esta traspuesta, la agregamos a las soluciones
                                                                                            if (verificador == 1){
                                                                                            
                                                                                                conjuntoSoluciones = agregarSolucion(conjuntoSoluciones, &contador, matriz);
                                                                                            }
                                                                                            //devolvemos el verificador a 0
                                                                                            verificador = 0;
  
                                                                                          
                                                                                        }
                                                                                        
                                                                                        
                                                                                    }
                                                                                }
                                                                                
                                                                                
                                                                            }
                                                                        }
                                                                        sumaFila1 = 0;
                                                                        sumaFila2 = 0;
                                                                        sumaFila3 = 0;
                                                                        sumaColumna1 = 0;
                                                                        sumaColumna2 = 0;
                                                                        sumaColumna3 = 0;
                                                                        
                                                                    }
                                                                }
                                                            }  
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                
            }
        }
        
    }

    imprimirSoluciones(conjuntoSoluciones, contador);
    //nos aseguramos de liberar la memoria
    for (int i = 0; i < 3; i++){
        free(matriz[i]);
    }
    free(matriz);

}

///////////PRINCIPAL//////////////////


int main(){
	//creamos una variable para guardar lo que eliga el usuario
    int opcion;
    //printeamos las opciones
    printf("1) Canibales y misioneros\n");
    printf("2) Cuadrado Magico\n");
    printf("3) salir\n");
    //este ciclo se encarga de que mientras el usuario no eliga salir el programa se seguira ejecutando
    while (opcion != 3){
        printf("ingrese una opcion: ");
        scanf("%d", &opcion);
        //en caso de elegir 1 como opcion, ejecutaremos las torres de hanoi
        if(opcion == 1){
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
				}
				else{ // si no es solucion, reviso todas las transiciones posibles

				//cruzar 2 canibales
				if(verificar2C(bActual) == 1){
					bSiguiente = cruzar2C(bActual); // genero el estado
                	// verifico si no se paso por el anteriormente
					if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    	// si es un nuevo estado nunca antes visto lo agrego
						abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
					}
					else{
						correlativo = correlativo - 1; // lo descarto si no
					}
				}
				//cruzar 1 canibal
				if(verificarCruzarC(bActual) == 1){
					bSiguiente = cruzarC(bActual); // genero el estado
                	// verifico si se paso por el anteriormente
					if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    	// si es un nuevo estado nunca antes visto lo agrego
						abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
					}
					else{
						correlativo = correlativo - 1; // lo descarto si no
				}
			}

				//cruzar canibal y misionero
				if(verificarCyM(bActual) == 1){
					bSiguiente = cruzarCyM(bActual); // genero el estado
                	// verifico si se paso por el anteriormente
					if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    	// si es un nuevo estado nunca antes visto lo agrego
						abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
					}
					else{
						correlativo = correlativo - 1;  // lo descarto si no
					}
				}
			

				//cruzar 2 misioneros
				if(verificar2M(bActual) == 1){
					bSiguiente = cruzar2M(bActual); // genero el estado
                	// verifico si se paso por el anteriormente
					if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    	// si es un nuevo estado nunca antes visto lo agrego
						abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
					}
					else{
						correlativo = correlativo - 1; // lo descarto si no
					}
				}
				//cruzar 2 canibales
				if(verificarCruzarM(bActual) == 1){
					bSiguiente = cruzarM(bActual);
				 	// verifico si se paso por el anteriormente
					if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
                    	// si es un nuevo estado nunca antes visto lo agrego
						abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
					}
					else{
						correlativo = correlativo - 1;  // lo descarto si no
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
        printf("1) Canibales y misioneros\n");
    	printf("2) Cuadrado Magico\n");
    	printf("3) salir\n");
        	
        }
        else if(opcion == 2){
        	cuadradoMagico();
            printf("1) Canibales y misioneros\n");
    		printf("2) Cuadrado Magico\n");
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
            printf("1) Canibales y misioneros\n");
    		printf("2) Cuadrado Magico\n");
    		printf("3) salir\n");
    	}
    }
   	
	return 0;
}

