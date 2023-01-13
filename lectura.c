#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct cancion cancion;
typedef struct genero genero;
typedef struct artista artista;
typedef struct preferencia preferencia;
typedef struct playlist playlist;
//nombre, duracion, id artista, id genero, popularidad
struct cancion{
    char nombre[30];
    char duracion[10];
    int min;
    int segundos;
    int idArtista;
    int genero;
    int popularidad;
};

//idArtista nombre
struct artista{
    int id;
    char nombre[20];
};
//idGenero nombre
struct genero{
    int id;
    char nombre[20];
};




void ordenarDatos(FILE *canciones, FILE * generos,FILE * artistas,FILE * preferencias, int cantidadCan, int cantidadGen, int cantidadArt){
    //creamos tantas estructuras de cancion como canciones hayan
    cancion cancionN[cantidadCan];
    int i,j;
    char separador[] = ":";
    //guardamos los datos del archivo de canciones en las estructuras
    for(i= 0;i < cantidadCan;i++){
        fscanf (canciones, "%s %s %d %d %d",cancionN[i].nombre,cancionN[i].duracion,&cancionN[i].idArtista,&cancionN[i].genero,&cancionN[i].popularidad);
        char * token = strtok(cancionN[i].duracion,separador);
        cancionN[i].min = atoi(token);
        token = strtok(NULL,"");
        cancionN[i].segundos = atoi(token);
    }
    //mostramos por pantalla estas canciones
    for(j= 0;j < cantidadCan;j++){
        printf("%s %d:%d %d %d %d \n",cancionN[j].nombre,cancionN[j].min,cancionN[j].segundos,cancionN[j].idArtista,cancionN[j].genero,cancionN[j].popularidad);
    }
    printf("\n\n");
    //creamos tantas estructuras de artista como artistas haya
    artista artistaN[cantidadArt];
    for(i= 0;i < cantidadArt;i++){
        fscanf (artistas, "%d %s \n",&artistaN[i].id, artistaN[i].nombre);
    }
    //mostramos por pantalla
    for(i= 0;i < cantidadArt;i++){
        printf( "%d %s \n",artistaN[i].id, artistaN[i].nombre);
    }
    printf("\n \n");
    //creamos tantas estructuras de genero como generos haya
    genero generoN[cantidadGen];
    for(i= 0;i < cantidadGen;i++){
        fscanf (generos, "%d %s \n",&generoN[i].id, generoN[i].nombre);
    }
    //mostramos por pantalla
    for(i= 0;i < cantidadGen;i++){
        printf( "%d %s \n",generoN[i].id, generoN[i].nombre);
    }

    //ahora buscamos almacenar la duracion deseada que tendra la playlist
    int minutos;
    int segundos;
    char duracionLista[10];
    fscanf(preferencias,"%s",duracionLista);
    char * token = strtok(duracionLista,separador);
    minutos = atoi(token);
    token = strtok(NULL," ");
    segundos = atoi(token);
    printf("Duracion estimada de la playlist es de %d:%d ",minutos,segundos);

  
}



int main(){
    //creamos variables para cada archivo
    FILE * canciones;
    FILE * generos;
    FILE * artistas;
    FILE * preferencias;
 
    canciones = fopen("canciones.in", "r");
    generos = fopen("generos.in", "r");
    artistas = fopen("artistas.in", "r");
    preferencias = fopen("preferencias.in", "r");
    //variables para guardar la cantidad de artistas,canciones y generos
    int cantidadCan,cantidadGen,cantidadArt;
    //se almacena la cantidad de artistas mediante fscanf
    fscanf(artistas, "%d" , &cantidadArt);
    printf("cantidad de artistas: %d\n ", cantidadArt);
    //se almacena la cantidad de generos mediante fscanf
    fscanf(generos, "%d" , &cantidadGen);
    printf("cantidad de generos: %d\n ", cantidadGen);
    //se almacena la cantidad de canciones mediante fscanf
    fscanf(canciones, "%d" , &cantidadCan);
    printf("cantidad de canciones: %d\n ", cantidadCan);
    printf("\n");
    ordenarDatos(canciones,generos,artistas,preferencias,cantidadCan,cantidadGen,cantidadArt);
    
    //nos aseguramos de cerrar los archivos
    fclose(canciones);
    fclose(generos);
    fclose(artistas);
    fclose(preferencias);
    return 0;
}
