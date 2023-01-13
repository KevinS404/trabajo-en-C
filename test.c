#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct nodo nodo;
//Estructura para cada nodo la cual contiene variables para los datos
//del planeta de partida, el de llegada, el tiempo empleado y el combustible necesario
struct nodo{
	char partida[15];
    char destino[15];
    int tiempo;
    int combustible;
};


//funcion que crea los nodos con la informacion de los planetas
//entrada: 2 datos tipo FILE con el archivo del mapa y el combustible
//objetivo: leer los archivos y generar los nodos con los datos corresponden
void crearNodos(FILE * mapa, FILE * combustible){
	//variables para guardar la cantidad de planetas y combustibles
	int cantidadPlanetas,cantidadCom;
	fscanf(mapa, "%d" , &cantidadPlanetas);
	fscanf(combustible, "%d" ,&cantidadCom);
	//mostramos por pantalla la cantidad de planetas y combustibles de la nave
	printf("Cantidad de planetas: %d\n",cantidadPlanetas);
	printf("Combustible disponible: %d\n",cantidadCom);
	int i;
	//creamos tantos nodos como planetas haya
	nodo nodito[cantidadPlanetas];
	//Con un ciclo vamos guardando los datos del archivo en los nodos
	for(i= 0;i < cantidadPlanetas;i++){
       	fscanf (mapa, "%s %s %d %d ",nodito[i].partida,nodito[i].destino,&nodito[i].tiempo,&nodito[i].combustible);
       	
   	}
   	//se genera un array para guardar los posibles planetas para recargar combustible
   	char recargarCombustible[cantidadPlanetas][15];
   	//variable auxiliar para conteo
   	int j = 0;
   	//guardamos en el array cada ubicacion donde es posible recargar combustible
   	while(!feof(combustible)){
   		fscanf(combustible,"%s",recargarCombustible[j]);
   		j = j + 1;
   	}
   	int k;
   	//se muestra por pantalla las ubicaciones para recargar
   	printf("Ubicaciones para recargar combustible: \n");
   	for(k =0;k<j-1;k++){
   		printf("- %s\n",recargarCombustible[k]);
   	}
   	
}

int main(int argc, char* argv[]){
	//si el usuario ingresa los archivos necesarios, entonces se procedera a abrirlos para poder efectuar su lectura
	if(argc == 3){
		//Creamos las variables para cada archivo con los datos 
		FILE * mapa;
		FILE * combustible;
		//Se abren cada archivo en modo de lectura
		mapa = fopen(argv[1], "r");
		combustible = fopen(argv[2], "r");
		crearNodos(mapa,combustible);
		//Nos aseguramos de cerrar los archivos
		fclose(mapa);
		fclose(combustible);
	}
	else{
		printf("Falta ingresar archivos");
	}
	return 0;
}