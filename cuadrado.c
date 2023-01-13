#include <stdio.h>
#include <stdlib.h>

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

int main(){
    
    cuadradoMagico();

    

    return 0;
}