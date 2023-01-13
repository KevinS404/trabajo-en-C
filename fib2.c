#include <stdio.h>
#include <time.h>
void fibonacciIterativo(){
    int i, n, siguienteN;
    int termino1 = 0;
    int termino2 = 1;
    printf("ingrese un numero para la sucesion: ");
    scanf("%d", &n);
    printf("La serie es: ");

    for (i = 1; i <= n; ++i) {
        //printf("%d, ", termino1);
        siguienteN = termino1 + termino2;
        termino1 = termino2;
        termino2 = siguienteN;
    }
    printf("%d\n, ", siguienteN);
}
int fibonacciRecursivo(int n){
   
    if(n==0 || n==1){/*Caso base */
        return n;
    }
    else{
        return fibonacciRecursivo(n-2) + fibonacciRecursivo(n-1);
    }

}
int main() {
    time_t ini1,fin1,ini2,fin2;
    int r1,r2;
    int n;
    printf("ingrese un numero para la sucesion: ");
    scanf("%d", &n);
    ini1 = time(NULL);
    int solucion = fibonacciRecursivo(n);
    printf("solucion: %d \n",solucion);
    fin1 = time(NULL);
    printf("\nRecursivo: %f \n", difftime(fin1,ini1));
    
    
    ini2 = time(NULL);
    fibonacciIterativo();
    fin2 = time(NULL);
    printf("\nIterativo: %f \n", difftime(fin2,ini2));
    

    return 0;
}