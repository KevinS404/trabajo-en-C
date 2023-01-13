#include<stdio.h>
//formato de la solucion

typedef struct soluciones{
	//la solucion se representara con una matriz de 3x4,donde
	//la fila 1 mostrara las monedas que recibe el nieto mayor
	//la fila 2 mostrara las del medio y la fila 3 las del menor
	//las columnas 1 al 4 hacen referencia a las monedas de 
	//500,100,50 y 10 respectivamente que se le da a cada nieto
	int ** solucion[3][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0}}
}respuesta;

//estructura que se encarga de guardar la cantidad de monedas de cada 
//nieto, el primer dato guarda la cantidad de monedas de 500,el segundo
//las de 100,el tercero las de 50 y el ultimo las de 10, para finalizar con una
//variable q almacene el total de monedas
typedef struct persona{
	int cantidad500;
	int cantidad100;
	int cantidad50;
	int cantidad10;
	int monedas = cantidad500+cantidad100+cantidad50+cantidad10;
}dinero;

//funcion para contar el dinero del nieto que se desee en ese momento
int sumaDinero(dinero nieto){
	int dineroTotal = nieto.cantidad500*500 + nieto.cantidad100*100 + nieto.cantidad50*50 + nieto.cantidad10*10;

	return dineroTotal;
}

//esta funcion recibe una de las posibles soluciones y le aplica cada una de las restricciones
//para ver si cumple con el criterio pedido
int restricciones(int ** solucion,dinero nietoMayor,dinero nietoMedio, dinero nietoMenor){
	//para cada solucion contaremos el dinero de cada nieto
	int dineroMayor = sumarDinero(nietoMayor);
	int dineroMedio = sumaroDinero(nietoMedio);
	int dineroMenor = sumarDinero(nietoMenor);
	//aqui obtenemos el total de dinero para una restriccion
	int total = dineroMayor + dineroMenor + dineroMenor;
	//aca obtenemos el total de monedas para otra restriccion
	int totalMonedas = nietoMayor.monedas + nietoMedio.monedas +nietoMenor.monedas;
    //variable para la suma de monedas entre el mayor y medio
	int maxMonedas = nietoMayor.monedas + nietoMedio.monedas
	//primera restriccion: que la cantidad de monedas entre los 3 no exceda 660
	if(totalMonedas <= 660){
	//desde aqui anidamos las restricciones para descartar en el momento que no se cumpla alguna
	//segunda restriccion: que la suma de los 3 no exceda los 20.000
		if(total <= 20.000){
			//tercera restriccion :que el mayor tenga al menos 50% del dinero
			if(dineroMayor >= 10000){
				//cuarta restriccion: que el del medio tengoa al menos 20% del dinero
				if(dineroMedio >= 4000){
					//a partir de aqui se genera el criterio de optimizacion para evitar la mayoria de casos
					//donde si bien se cumplen las restricciones establecidad en el enunciado, no cumplen con
					//otras que no estan textuales
					//quinta restriccion: que entre el mayor y el medio tengan al menos 14.000 entre ambos
					if((dineroMayor+dineroMedio)>= 14.000){
						//sexta restriccion:que entre el mayor y medio tengan menos de la mitdad de monedas
						//esto para asegurarse que el menor tengo la mayoria de monedas
						if(maxMonedas <330){
							return 1;
						}
					}
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
void generaSolucion(respuesta solucion, dinero nietoMayor, dinero nietoMedio, nietoMenor){
	//en este caso optimizaremos dandole siempre todas las monedas de 100 y de 50
	//al mayor, dado que esto cumple con darle al menos el 50% del dinero, deja ventana
	//para darle la mayoria de monedas al hermano pequeño y nos quitamos el problema de
	//que el algoritmo busque durante mucho tiempo todas las combinaciones que funcionen
	nietoMayor.cantidad100 = 50;
	nietoMayor.cantidad50 = 100;
	//ahora solo queda ver como distrubuir las monedas restantes
	int i
	//en este caso i<510 por la cantidad de mondas que queda
	for(i=0;i<510;i++){
		distribuir de manera aleatoria las mondas para el nieto menor y medio
	}

}
void mostrarSolucion(respuesta matriz){
	int i,j
	printf("Solucion: ")
	for(i=0;i<3;i++){
		for(j=0;j<4;j++){
			printf("%d ",matriz.solucion[i][j]);
		}
	}
	printf("\n");
}
int main(){
	//genero 1 estructura para cada nieto
	dinero nieto[3];
	//por ahora dejamos una representacion de las posibles soluciones
	//siendo el 50 solo una idea
	int i,verificador;
	for( i = 0;i<50;i++){
		respuesta solucion[i];
		generaSolucion(solucion[i],nieto[1],nieto[2],nieto[3]);
		//una vez generada la solucion revisamos si esta cumple con las restricciones
		verificador = restricciones(solucion[i]);
		//si no cumple, la sacamos de las posibles soluciones
		if(verificador == 0){
			sacamos esta solucion de las posibles soluciones

		}
	}
	//en este apartado printeamos las soluciones posibles 
	int j;
	for(j=0;j<50;j++){
		mostrarSolucion(solucion[i]);
	}
	return 0;
}