#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct pzt pzt;

struct pzt{
	int *izq; // aqui vamos a almacenar [p,z,t,j] ejemplo [0,0,1,0]
	int *der; // ejemplo: [1,1,0,1]

	int idEstado;
	int estadoAnterior;
	char * transicion;
};

int correlativo;


// Funciones de listas
pzt crearEstado(int *izq, int *der, int anterior, char * t);
pzt * agregarEstado(pzt * lista, int * elementos, pzt estado);
pzt * sacarElemento(pzt * lista, int * elementos);
int estaEstado(pzt * lista, int elementos, pzt b);
void mostrarSolucion(pzt * lista, int ultimo);

// funciones chequear transicion: CP,CZ,CT,CJ 
int verificarCP(pzt estado); // cruzar el pato

// funciones de transicion
pzt CP(pzt estado);

// funciones generales
int esFinal(pzt b);
void imprimirEstado(pzt b);

// implementaciones


///////////LISTAS//////////////////
pzt crearEstado(int *izq, int *der, int anterior, char * t){
	pzt nuevoEstado;

	nuevoEstado.izq = izq;
	nuevoEstado.der = der;

	nuevoEstado.idEstado = correlativo;
	nuevoEstado.estadoAnterior = anterior;
	nuevoEstado.transicion = t;
	correlativo = correlativo + 1;
	return nuevoEstado;
}

pzt * agregarEstado(pzt * lista, int * elementos, pzt estado){
	pzt * nuevaLista = (pzt *)malloc(sizeof(pzt)*(*elementos+1));
	for (int i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	*elementos = *elementos+1;
	free(lista);
	return nuevaLista;
}

pzt * sacarElemento(pzt * lista, int * elementos){
	pzt * nuevaLista = (pzt *)malloc(sizeof(pzt)*(*elementos-1));
	for (int i = 1; i < *elementos; ++i){
		nuevaLista[i-1]=lista[i];
	}
	*elementos = *elementos-1;
	free(lista);
	return nuevaLista;
}

int sonIguales(pzt a, pzt b) {
  return( (a.izq[0]==b.izq[0]) &&
          (a.izq[1]==b.izq[1]) &&
          (a.izq[2]==b.izq[2]) &&
          (a.izq[3]==b.izq[3]) &&
          (a.der[0]==b.der[0]) &&
          (a.der[1]==b.der[1]) &&
          (a.der[2]==b.der[2]) &&
          (a.der[3]==b.der[3]) 
        );
}

// si b esta en la lista
int estaEstado(pzt * lista, int elementos, pzt b){
	for (int i = 0; i < elementos; ++i){
      if (sonIguales(lista[i],b))
			return 1;
	}
    return 0;
}


//////////CHEQUEAR TRANSICIONES///////////////////
// Si se puede cruzar con el Pato
// cuando esta el pato en lado del rio donde esta Juan
int verificarCP(pzt estado){
	if(estado.izq[3] ==1){ // si Juan esta a la izquierda
	  return(estado.izq[0]==1); // si el pato (0) esta
	} else { // Juan esta a la derecha
	  return(estado.der[0]==1); // si el pato (0) esta
    }
}

// Si se puede cruzar con el Zorro
// cuando esta el zorro en lado del rio donde esta Juan
// y no esta junto pato con trigo
int verificarCZ(pzt estado){
	if(estado.izq[3] ==1){ // si Juan esta a la izquierda
	  return(estado.izq[1]==1 && !(estado.izq[0]==1 && estado.izq[2]==1)); // si el pato (0) esta
	} else { // Juan esta a la derecha
	  return(estado.der[1]==1 && !(estado.der[0]==1 && estado.der[2]==1)); // si el pato (0) esta
    }
}

// Si se puede cruzar con el Trigo
// cuando esta el trigo en lado del rio donde esta Juan
// y no esta junto pato con zorro
int verificarCT(pzt estado){
	if(estado.izq[3] ==1){ // si Juan esta a la izquierda
	  return(estado.izq[2]==1 && !(estado.izq[0]==1 && estado.izq[1]==1)); // si el pato (0) esta
	} else { // Juan esta a la derecha
	  return(estado.der[2]==1 && !(estado.der[0]==1 && estado.der[1]==1)); // si el pato (0) esta
    }
}
// Si se puede cruzar Juan solo
// y no esta junto pato con zorro o pato con trigo
int verificarCJ(pzt estado){
	if(estado.izq[3] ==1){ // si Juan esta a la izquierda
	  return(!(estado.izq[0]==1 && estado.izq[2]) && !(estado.izq[0]==1 && estado.izq[1]==1)); // no pt ni pz
	} else { // Juan esta a la derecha
	  return(!(estado.der[0]==1 && estado.der[2]==1)&& !(estado.der[0]==1 && estado.der[1]==1)); // 
    }
}
///////////TRANSICIONES//////////////////
pzt CP(pzt estado){
    // se debe definir y llenar arreglos izq y der
    // cruzar el pato junto con juan
    int *izq=malloc(sizeof(int)*4), *der=malloc(sizeof(int)*4);
    memcpy(izq, estado.izq, sizeof(int)*4);
    memcpy(der, estado.der, sizeof(int)*4);
    if (izq[3]==1) { // Juan esta a la izquierda
      izq[3]=0; der[3]=1;
      izq[0]=0; der[0]=1;
    } else {// entonces esta a la derecha
      izq[3]=1; der[3]=0;
      izq[0]=1; der[0]=0;
    }
	return crearEstado(izq, der, estado.idEstado, "CP");
}

pzt CZ(pzt estado){
    // se debe definir y llenar arreglos izq y der
    // cruzar el zorro junto con juan
    int *izq=malloc(sizeof(int)*4), *der=malloc(sizeof(int)*4);
    memcpy(izq, estado.izq, sizeof(int)*4);
    memcpy(der, estado.der, sizeof(int)*4);

    if (izq[3]==1) { // Juan esta a la izquierda
      izq[3]=0; der[3]=1;
      izq[1]=0; der[1]=1;
    } else {// entonces esta a la derecha
      izq[3]=1; der[3]=0;
      izq[1]=1; der[1]=0;
    }

	return crearEstado(izq, der, estado.idEstado, "CZ");
}

pzt CT(pzt estado){
    // se debe definir y llenar arreglos izq y der
    // cruzar el trigo junto con juan
    int *izq=malloc(sizeof(int)*4), *der=malloc(sizeof(int)*4);
    memcpy(izq, estado.izq, sizeof(int)*4);
    memcpy(der, estado.der, sizeof(int)*4);

    if (izq[3]==1) { // Juan esta a la izquierda
      izq[3]=0; der[3]=1;
      izq[2]=0; der[2]=1;
    } else {// entonces esta a la derecha
      izq[3]=1; der[3]=0;
      izq[2]=1; der[2]=0;
    }

	return crearEstado(izq, der, estado.idEstado, "CT");
}

pzt CJ(pzt estado){
    // se debe definir y llenar arreglos izq y der
    // cruzar a juan solo
    int *izq=malloc(sizeof(int)*4), *der=malloc(sizeof(int)*4);
    memcpy(izq, estado.izq, sizeof(int)*4);
    memcpy(der, estado.der, sizeof(int)*4);

    if (izq[3]==1) { // Juan esta a la izquierda
      izq[3]=0; der[3]=1;
    } else {// entonces esta a la derecha
      izq[3]=1; der[3]=0;
    }

	return crearEstado(izq, der, estado.idEstado, "CJ");
}
//////////FUNCIONES GENERALES///////////////////
int esFinal(pzt b){ // si es solucion
  return( b.der[0] && b.der[1] && b.der[2] && b.der[3] );
}

void imprimirEstado(pzt b){
	printf("Id:%d; IZQ:%d%d%d%d, DER:%d%d%d%d; T:%s, IdAnt:%d\n", b.idEstado, b.izq[0], b.izq[1], b.izq[2], b.izq[3], b.der[0], b.der[1], b.der[2], b.der[3], b.transicion, b.estadoAnterior);
}


void mostrarSolucion(pzt * lista, int ultimo){
	printf("Los pasos son, del ultimo al primero: \n");
	while(lista[ultimo].idEstado != 0){
		printf("%s\n", lista[ultimo].transicion);
		ultimo = lista[ultimo].estadoAnterior;
	}
}


///////////PRINCIPAL//////////////////
int main(){
	correlativo = 0;
	int canAbiertos = 0;
	int canCerrados = 0;
	pzt bActual, bSiguiente;
	pzt * abiertos = (pzt *)malloc(sizeof(pzt)*canAbiertos);
	pzt * cerrados = (pzt *)malloc(sizeof(pzt)*canCerrados);
    // Crear el estado inicial
    int *izq=malloc(sizeof(int)*4), *der=malloc(sizeof(int)*4);
    izq[0]=1; izq[1]=1; izq[2]=1; izq[3]=1;
    der[0]=0; der[1]=0; der[2]=0; der[3]=0;  
	pzt inicial = crearEstado(izq, der, correlativo, "");
	abiertos = agregarEstado(abiertos, &canAbiertos, inicial);
	while(canAbiertos > 0){
		bActual = abiertos[0]; 
		abiertos = sacarElemento(abiertos, &canAbiertos);
		cerrados = agregarEstado(cerrados, &canCerrados, bActual);
		if(esFinal(bActual) == 1){ // Aqui se encontro la solucion
			printf("Llegue\n");
			mostrarSolucion(cerrados,canCerrados-1);
			return 0;
		}else{ // si no es solucion

			//CP: se puede cruzar el pato?
			if(verificarCP(bActual) == 1){
				bSiguiente = CP(bActual); // cruzamos el pato
                // se verifica si NO fue visitado el estado
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			 }
             
			//CZ: se puede cruzar el zorro?
			if(verificarCZ(bActual) == 1){
				bSiguiente = CZ(bActual); // cruzamos el zorro
                // se verifica si NO fue visitado el estado
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			 }
			//CT: se puede cruzar el trigo?
			if(verificarCT(bActual) == 1){
				bSiguiente = CT(bActual); // cruzamos el trigo
                // se verifica si NO fue visitado el estado
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			 }
			//CJ: se puede cruzar juan solo?
			if(verificarCJ(bActual) == 1){
				bSiguiente = CJ(bActual); // cruzamos el trigo
                // se verifica si NO fue visitado el estado
				if((estaEstado(abiertos,canAbiertos,bSiguiente) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			 }
                

		} // fin de else




		printf("ABIERTOS:\n");
		for (int i = 0; i < canAbiertos; ++i) {
			imprimirEstado(abiertos[i]);
		}
		printf("CERRADOS:\n");
		for (int i = 0; i < canCerrados; ++i) {
			imprimirEstado(cerrados[i]);
		}
		printf("____________________________________\n");
	} // vuelve a buscar un estado pendiente y lo revisa

	return(0);
}

