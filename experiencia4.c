#include <stdio.h>
#include <stdlib.h>

int main(){
    // se pide el largo para el arreglo
    int largo;
    printf("ingrese el largo de la palabra:\n");
    scanf("%d", &largo);

    //se crea el arreglo
    char palabra[largo];
    printf("ingrese la palabra:\n");
    scanf("%s",&palabra);
    // el segundo largo de la matriz es la cantidad de permutaciones
    // y esa cantidad es el factorial del largo
    int largopermutacion = 1; 
    int distancia = largo;
    while (1 < distancia)
    {
        largopermutacion = largopermutacion * distancia;
        distancia--;
    }
    printf("esta es la cantidad de permutaciones:\n");
    printf("%d\n", largopermutacion);



    // creamos la matriz
    
    char ** matriz = (char**)malloc(sizeof(char*)*(largopermutacion));

    for (int i = 0; i < largopermutacion; i++)
    {
        matriz[i] = (char*)malloc(sizeof(char)*(largo));
    }
    
    // empezamos a permutar
    int cont = 0;
    if (largo == 2)
    {   
         for (int i = 0; i < largo; i++)
        {
            for (int x = 0; x < largo; x++)
            {   
                if (x != i)
                {
                    matriz[cont][0] = palabra[i];
                    matriz[cont][1] = palabra[x];
                    cont++;
                }
                
            }
            
        }

    }
    if (largo == 3) 
    {
        for (int i = 0; i < largo; i++)
        {
            for (int x = 0; x < largo; x++)
            {   
                if (x != i)
                {
                    for (int y = 0; y < largo; y++)
                    {
                        if (y != x && y != i)
                        {
                            matriz[cont][0] = palabra[i];
                            matriz[cont][1] = palabra[x];
                            matriz[cont][2] = palabra[y];
                            cont++;

                        }
                        
                    }
                }
            }  
        }
    }

    if (largo == 4) 
    {
        for (int i = 0; i < largo; i++)
        {
            for (int x = 0; x < largo; x++)
            {   
                if (x != i)
                {
                    for (int y = 0; y < largo; y++)
                    {
                        if (y != x && y != i)
                        {
                            for (int z = 0; z < largo; z++)
                            {
                                if (z != y && z != x && z != i)
                                {
                                    matriz[cont][0] = palabra[i];
                                    matriz[cont][1] = palabra[x];
                                    matriz[cont][2] = palabra[y];
                                    matriz[cont][3] = palabra[z];
                                    cont++;
                                    
                                }
                                
                            }

                        }
                        
                    }
                }
            }  
        }
    }
    

    if (largo == 5)
    {
        for (int i = 0; i < largo; i++)
        {

            for (int x = 0; x < largo; x++)
            {
                if (i != x)
                {   
                    for (int y = 0; y < largo; y++)
                    {
                        if (y != x && y != i)
                        {
                            for (int z = 0; z < largo; z++)
                            {
                                if (z != i && z != x && z != y)
                                {
                                    for (int w = 0; w < largo; w++)
                                    {
                                        if (w != i && w != x && w != y && w != z)
                                        {
                                            matriz[cont][0] = palabra[i];
                                            matriz[cont][1] = palabra[x];
                                            matriz[cont][2] = palabra[y];
                                            matriz[cont][3] = palabra[z];
                                            matriz[cont][4] = palabra[w];
                                            cont++;
                                            
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
  
    if (largo == 6)
    {
        for (int i = 0; i < largo; i++)
        {

            for (int x = 0; x < largo; x++)
            {
                if (i != x)
                {   
                    for (int y = 0; y < largo; y++)
                    {
                        if (y != x && y != i)
                        {
                            for (int z = 0; z < largo; z++)
                            {
                                if (z != i && z != x && z != y)
                                {
                                    for (int w = 0; w < largo; w++)
                                    {
                                        if (w != i && w != x && w != y && w != z)
                                        {
                                            for (int r = 0; r < largo; r++)
                                            {
                                                if (r != i && r != x && r != y && r != z && r != w)
                                                {
                                                    matriz[cont][0] = palabra[i];
                                                    matriz[cont][1] = palabra[x];
                                                    matriz[cont][2] = palabra[y];
                                                    matriz[cont][3] = palabra[z];
                                                    matriz[cont][4] = palabra[w];
                                                    matriz[cont][5] = palabra[r];
                                                    cont++;
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
    
    // se muestran las permutaciones
    for (int i = 0; i < largopermutacion; i++)
    {   
        printf("\n");
        for (int x = 0; x < largo; x++)
        {
            printf(" %c", matriz[i][x]);
        }
            
    }
    

    // se libera memoria
    for (int i = 0; i < largopermutacion; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
    
    
    
    return 0;
}