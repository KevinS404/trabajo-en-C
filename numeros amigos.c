#include <stdio.h>
int amigos(int a, int b){
	int i = 1;
	int j = 1;
	int verificador1 = 0;
	int verificador2 = 0;
	while(i < a){
		if(a%i== 0){
			verificador1 = verificador1 + i;
		}
		i = i + 1;

	}
    while(j < b){
    	if(b%j==0){
    		verificador2 = verificador2 + j;
    	}
    	j = j + 1;
    }
    if (verificador2 == a && verificador1 == b){
    	return 1;
    }
    else{
    	return 0;
    }

} 




int main()
{
	int variable1,variable2,respuesta;
	printf("Ingrese los valores que desee verificar: ");
	scanf("%i %i",&variable1,&variable2);
	respuesta = amigos(variable1,variable2); 
        printf("valor respuesta %i\n", respuesta);
	if (respuesta == 1){
		printf("Los numeros %i y %i son amigos",variable1,variable2);
	}
	else{
		printf("Los numeros %i y %i no son amigos",variable1,variable2);
	}
	return 0;
}