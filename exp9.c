#include<stdio.h>
#include <stdlib.h> 

//estructura que se encarga de guardar la cantidad de monedas de cada 
//nieto, el primer dato guarda la cantidad de monedas de 500,el segundo
//las de 100,el tercero las de 50 y el ultimo las de 10, para finalizar con una
//variable q almacene el total de monedas
typedef struct dinero{
	int cantidad500;
	int cantidad100;
	int cantidad50;
	int cantidad10;
	int monedas;
}dinero;

//funcion para contar el dinero del nieto que se desee en ese momento
//entrada: recibe un struct de tipo dinero
//salida: retorna el valor de la suma de las cantidades que tiene el nieto
int sumaDinero(dinero nieto){
	int dineroTotal = nieto.cantidad500*500 + nieto.cantidad100*100 + nieto.cantidad50*50 + nieto.cantidad10*10;
	return dineroTotal;
}

//esta funcion recibe una de las posibles soluciones y le aplica cada una de las restricciones
//para ver si cumple con el criterio pedido
int restricciones(dinero nietoMayor,dinero nietoMedio, dinero nietoMenor){
	//para cada solucion contaremos el dinero de cada nieto
	int dineroMayor = sumaDinero(nietoMayor);
	int dineroMedio = sumaDinero(nietoMedio);
	int dineroMenor = sumaDinero(nietoMenor);
	//aqui obtenemos el total de dinero para una restriccion
	int total = dineroMayor + dineroMenor + dineroMenor;
    //variable para la suma de monedas entre el mayor y medio
	int maxMonedas = nietoMayor.monedas + nietoMedio.monedas;
	//restriccion para ver si esta todo el dinero
	if(total == 20000){
		//restriccion para ver que el mayor tenga el 50% del dinero
		if(dineroMayor >= 10000){
			//restriccion para ver que el del medio tenga el 20% del dinero
			if(dineroMedio >= 4000){
				//restriccion para ver que el menor tenga la mayor cantidad de monedas
				if(maxMonedas <=330){
					printf("Solucion Encontrada \n\n");
					return 1;
				}
			}
		}
	}
	else{
		//esto se retorna en caso de no cumplir alguna restriccion
		return 0;
	}
}
//funcion que genera soluciones y la verifica para ver si dejarla o no en la estructura de soluciones
int generarSolucion(dinero nietoMayor, dinero nietoMedio,dinero nietoMenor){
	//en este caso optimizaremos dandole siempre todas las monedas de 100 y de 50
	//al mayor, dado que esto cumple con darle al menos el 50% del dinero, deja ventana
	//para darle la mayoria de monedas al hermano pequeño y nos quitamos el problema de
	//que el algoritmo busque durante mucho tiempo todas las combinaciones que funcionen
	//nieto mayor
	nietoMayor.cantidad100 = 50;
	nietoMayor.cantidad50 = 100;
	nietoMayor.cantidad500 = 0; 
	nietoMayor.cantidad10 = 0;
	nietoMayor.monedas = 150;
	//nieto medio
	nietoMedio.cantidad100 = 0;
	nietoMedio.cantidad50 = 0;
	nietoMedio.monedas = 0;
	//nieto menor
	nietoMenor.cantidad100 = 0;
	nietoMenor.cantidad50 = 0;
	nietoMenor.monedas = 0;
	//ahora solo queda ver como distrubuir las monedas restantes
	int i,j,k,l;
	int verificador;

	//repartir monedas de 500 al del medio
	for(i=10;i>0;i--){
		nietoMedio.cantidad500 = i;
		nietoMedio.monedas = nietoMedio.monedas + i;
		for(j=0;j<10;j++){
			nietoMenor.cantidad500 = j;
			nietoMenor.monedas = nietoMenor.monedas + j;
			for(k=0;k<501;k++){
				nietoMedio.cantidad10 = k;
				nietoMedio.monedas = nietoMedio.monedas + k;
					for(l=0;l<501;l++){
						nietoMenor.cantidad10 = l;
						nietoMenor.monedas = nietoMenor.monedas + l;
						int totalMonedas = nietoMayor.monedas + nietoMedio.monedas +nietoMenor.monedas;
						if(totalMonedas == 660){
							printf("%d %d %d %d \n",nietoMayor.cantidad500, nietoMayor.cantidad100,nietoMayor.cantidad50,nietoMayor.cantidad10);
							printf("%d %d %d %d \n",nietoMedio.cantidad500, nietoMedio.cantidad100,nietoMedio.cantidad50,nietoMedio.cantidad10);
							printf("%d %d %d %d \n",nietoMenor.cantidad500, nietoMenor.cantidad100,nietoMenor.cantidad50,nietoMenor.cantidad10);
							verificador = restricciones(nietoMayor,nietoMedio,nietoMenor);
							printf("valor verificador: %d \n",verificador);
							//devolvemos la  cantidad de monedas a 0
							nietoMedio.monedas = 0;
							nietoMenor.monedas = 0;
							if(verificador == 1){	
								printf("La cantidad mostrada pertenece a la cantidad de monedas de 500,100,50 y 10 \n");
								printf("Nieto mayor: %d %d %d %d \n",nietoMayor.cantidad500, nietoMayor.cantidad100,nietoMayor.cantidad50,nietoMayor.cantidad10);
								printf("Nieto medio: %d %d %d %d \n",nietoMedio.cantidad500, nietoMedio.cantidad100,nietoMedio.cantidad50,nietoMedio.cantidad10);
								printf("Nieto menor: %d %d %d %d \n",nietoMenor.cantidad500, nietoMenor.cantidad100,nietoMenor.cantidad50,nietoMenor.cantidad10);
								verificador = restricciones(nietoMayor,nietoMedio,nietoMenor);
								return 1;
							}
						}	
					}	
				}
			}
	
	}


	return 0;
}

int main(){
	//genero 1 estructura para cada nieto
    dinero nietoMayor;
	dinero nietoMedio;
	dinero nietoMenor;
	int solucion = generarSolucion(nietoMayor,nietoMedio,nietoMenor);
	return 0;
}
