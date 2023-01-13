#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct estados{
	//cantidad de misioneros al lado izquierdo
	int misionerosIzquierda;
	//cantidad de misioneros al lado derecho
	int misionerosDerecha;
//cantidad de canibales al lado derecho
	int canibalesIzquierda;
	//cantidad de canibales al lado derecho
	int canibalesDerecha;
	//si el bote esta o no
	int bote;

}estado;
void transiciones(estado estadoActual);


//El estado final es cuando todos estan al lado derecho, includio el bote
int esFinal(estado estadoActual){
	if(estadoActual.canibalesDerecha==3 && estadoActual.misionerosDerecha == 3 && estadoActual.bote == 1){
		return 1;
	}
	else{
		return 0;
	}
}
void imprimirSolucion(estado estadoActual){
	printf("%d | %d | %d",estadoActual.canibalesDerecha,estadoActual.misionerosDerecha,estadoActual.bote);
	printf("\n");

}
estado crearEstado(int misIzquierda, int canIzquierda, int misDerecha, int canDerecha, int posicion){
	estado nuevoEstado;
	nuevoEstado.misionerosIzquierda = misIzquierda;
	nuevoEstado.canibalesIzquierda = canIzquierda;
	nuevoEstado.misionerosDerecha = misDerecha;
	nuevoEstado.canibalesDerecha = canDerecha;
	nuevoEstado.bote = posicion;
	imprimirSolucion(nuevoEstado);
	transiciones(nuevoEstado);
}



void transiciones(estado estadoActual){
	//verificamos que no sea el estado final
	if(esFinal(estadoActual) == 1){
		printf("SOLUCION DEL PROBLEMA:\n");
		imprimirSolucion(estadoActual);
	}
	else{
		//enviar 2 canibales al lado derecho
		if((estadoActual.misionerosIzquierda == 3 || estadoActual.misionerosIzquierda == 0) && estadoActual.canibalesIzquierda-2 >=0 && estadoActual.bote == 0){
			crearEstado(estadoActual.misionerosIzquierda,estadoActual.canibalesIzquierda-2,estadoActual.misionerosDerecha,estadoActual.canibalesDerecha+2,1);
		}
		//enviar 1 canibal al lado izquierdo
		else if((estadoActual.misionerosDerecha == 3 || estadoActual.misionerosDerecha == 0) && estadoActual.canibalesDerecha-1 >=0 && estadoActual.bote == 1){
			crearEstado(estadoActual.misionerosIzquierda,estadoActual.canibalesIzquierda+1,estadoActual.misionerosDerecha,estadoActual.canibalesDerecha-1,0);
		}
		//enviar 2 misioneros al lado derecho
		else if((estadoActual.misionerosIzquierda == 3 || estadoActual.misionerosIzquierda == 0) && estadoActual.misionerosIzquierda-2 >=0 && estadoActual.canibalesIzquierda <=1 && estadoActual.bote == 0){
			crearEstado(estadoActual.misionerosIzquierda-2,estadoActual.canibalesIzquierda,estadoActual.misionerosDerecha+2,estadoActual.canibalesDerecha,1);
		}
		//envia 1 canibal y 1 misionero al lazo izquierdo
		else if((estadoActual.misionerosIzquierda == estadoActual.canibalesIzquierda )&& estadoActual.canibalesDerecha<3 && estadoActual.bote == 1){
			crearEstado(estadoActual.misionerosIzquierda+1,estadoActual.canibalesIzquierda+1,estadoActual.misionerosDerecha-1,estadoActual.canibalesDerecha-1,0);
		}
		
	}
}


//Funcion que inicia el problema del bote
void misionerosYcanibales(){
	//El lado B siempre esta con todas sus variables en 0 al iniciar
	estado estadoActual = crearEstado(3,3,0,0,0);
}


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
            misionerosYcanibales();
            printf("1) Canibales y misioneros\n");
    		printf("2) Cuadrado Magico\n");
    		printf("3) salir\n");
        }
        //en caso de elegir 2 como opcion, ejecutaremos el programa de contagios
        else if(opcion == 2){
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