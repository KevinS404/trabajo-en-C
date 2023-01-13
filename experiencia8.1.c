#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//Estructura que guardara los estados de las torres.
struct estado{
	//se genera 1 arreglo para cada torre en especifico
	//en t1 estaran los datos iniciales entre 3 y 7.
	int t1[];
	//este arreglo es el que servira para mover los datos entre t1 y t3.
	int t2[];
	//Como queremos guardar los datos en la tercera torre, este arreglo 
	//sera el estado inicial con solo 0s como sus datos almacenados.
	int t3[] = {0,0,0};
	//Esta ultima torre representara el estado final, con la que compararemos en cada transicion
	//basicamente sera una copia de la torre 1 inicial una vez puesto los datos.
	int tfinal[];

};
typedef struct estado estados;

//Con esta funcion nos encargamos de generar los datos de la torre 1
int generarTorre(int t1,int n){
	 srand(time(NULL));
    int * t1 = (int*)malloc(sizeof(int)*n);

    for (int i = 0; i < n; i++){
        t1[i] = rand()%50 + 1;
    }
    return t1;
	
}
// Aqui nos aseguramos de que la torre este en orden antes de iniciar el ejercicio
// aprovechando de copiar estos mismos en la torre que servira para comprobar el
// estado final
int ordenarTorre(int t1,int n, int t4){
	int aux;
	int i,j,k;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			if (t1[j] > t1[i]){
				aux = t1[i];        
				t1[i] = t1[j];           
				t1[j] = aux;            
			}  
		}
	}
	for(k = 0;k < n; k ++){
		t4[k] = t1[k];
	}
	return 0;
}


int main(){
	int n;
	printf("Ingrese cuantos elementos quiere, entre 3 y 7:  ");
	scanf("%d",&n);
	generarTorre(estados.t1,n);
	ordenarTorre(estados.t1,n,estados.t4);
	//Ahora empezamos con las transiciones:
	//Pasar de t1 a t2, t1 a t3, t2 a t1, t2 a t3, t3 a t2 y t3 a t1
    //quedando en total 6 transiciones.
	//Comenzamos confirmando que la t3 este o no en el estado final.
	if (t3 == t4){
		for (int i = 0; i < n; i++){
        printf("%d - ",t3[i]);
    	}
}
	//ahora mediante mas condiciones empiezo a mover elementos entre las torres

	return 0;
}