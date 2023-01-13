#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

typedef struct cancion cancion;
typedef struct genero genero;
typedef struct artista artista;

//estructura de tipo cancion para guardar su nombre, duracion, id artista, id generoy y popularidad
struct cancion{
    char nombre[30];
    char duracion[10];
    int min;
    int segundos;
    int idArtista;
    int genero;
    int popularidad;

};



//estructura de tipo artista para guardar id del artista y su nombre
struct artista{
    int id;
    char nombre[20];
};
//estructura de tipo artista para guardar id del genero y su nombre
struct genero{
    int id;
    char nombre[20];
};

/*
funcion que tiene como objetivo ordenar los datos y generar el archivo de salida.out
entrada: tipo de dato FILE para las canciones,generos, artistas y preferencias, un int para la cantidad de canciones,generos y artistas respectivamente
salida: el archivo salida.out con los datos solicitados
*/

void listarDatos(FILE *canciones, FILE * generos,FILE * artistas,FILE * preferencias, int cantidadCan, int cantidadGen, int cantidadArt){
    //creamos tantas estructuras de cancion como canciones hayan en el archivo
    //haemos lo mismo para los artistas y los generos
    cancion cancionN[cantidadCan];
    artista artistaN[cantidadArt];
    genero generoN[cantidadGen];
    int i,j;
    char separador[] = ":";
    //guardamos los datos del archivo de canciones en las estructuras
    for(i= 0;i < cantidadCan;i++){
        fscanf (canciones, "%s %s %d %d %d",cancionN[i].nombre,cancionN[i].duracion,&cancionN[i].idArtista,&cancionN[i].genero,&cancionN[i].popularidad);
        //aqui se separa la duracion en minutos y segundos para poder usarlos como enteros
        char * token = strtok(cancionN[i].duracion,separador);
        cancionN[i].min = atoi(token);
        token = strtok(NULL,"");
        cancionN[i].segundos = atoi(token);
    }
    //se hace lo mismo para el archivo de artistas y de generos
    for(i= 0;i < cantidadArt;i++){
        fscanf (artistas, "%d %s \n",&artistaN[i].id, artistaN[i].nombre);
    }

  
    for(i= 0;i < cantidadGen;i++){
        fscanf (generos, "%d %s \n",&generoN[i].id, generoN[i].nombre);
    }
   
    //ahora buscamos almacenar la duracion deseada que tendra la playlist, para eso hacemos variables para los minutos y los segundos
    int minutos,segundos;
    //esta variable almacenara como string la duracion que tiene el archivo
    char duracionLista[10];
    fscanf(preferencias,"%s",duracionLista);
    //aqui separamos los minutos de los segundos
    char * token = strtok(duracionLista,separador);
    minutos = atoi(token);
    token = strtok(NULL," ");
    segundos = atoi(token);
    //mostramos por pantalla la duracion estimada
    printf("Duracion estimada de la playlist es de %d:%d ",minutos,segundos);
    //ahora hacemos una lista para almacenar el orden preferido de las preferencias
    int listaPreferencias[cantidadGen];
    printf("\n");
    for(i = 0;i < cantidadGen-1;i++){
        fscanf(preferencias, "%d",&listaPreferencias[i]);
    }
    printf("\n");
      //hacemos listas para ordenar los datos de la salida
    int listaPopularidad[cantidadCan];
    char * listaCanciones[cantidadCan];
    int idGeneros[cantidadCan];
    int idArtistas[cantidadCan];

    // con este ciclo asignamos a cada lista los datos guardados en las estructuras
    for(i = 0;i<cantidadCan;i++){
        listaPopularidad[i] = cancionN[i].popularidad; 
        listaCanciones[i] =  cancionN[i].nombre;
        idGeneros[i] = cancionN[i].genero;
        idArtistas[i] = cancionN[i].idArtista;
    }
    int aux1,aux2,aux3;
    char * aux;
    //ordenamos las canciones por su popularidad
    for (i = 0; i < cantidadCan; ++i) {
        for (j = i + 1; j < cantidadCan; ++j){
            //si la popularidad evaluada en i es menor que la popularidad en j, hacemos el cambio con la ayuda de los auxiliares
            if (listaPopularidad[i] < listaPopularidad[j]){
                aux1 =  listaPopularidad[i];
                listaPopularidad[i] = listaPopularidad[j];
                listaPopularidad[j] = aux1;
                //se intercambia el lugar de los generos
                aux2 = idGeneros[i];
                idGeneros[i] = idGeneros[j];
                idGeneros[j] = aux2;
                //se intercambia el lugar de los artistas
                aux3 = idArtistas[i];
                idArtistas[i] = idArtistas[j];
                idArtistas[j] = aux3;
                //se intercambia el lugar de las canciones
                aux = listaCanciones[i];
                listaCanciones[i] = listaCanciones[j];
                listaCanciones[j] = aux;
            }
        }
    }
    printf("\n");
    //generamos el archivo de salida
    FILE * salida;
    //se abre el archivo en modo de escritura
    salida = fopen("salida.out","w");
    //con la ayuda de un tercer iterado haremos un ciclo para escribir el archivo
    int k;
    for(i= 0;i < cantidadCan;i++){
        for(j = 0; j<cantidadArt;j++){
            for(k = 0; k <cantidadGen; k++){
                //si el id de artista en i es el mismo que en j y a su vez el id de generos en i es el mismo que en k, escribimos la cancion correspondiente
                //en el archivo y la mostramos por pantalla
                if(idArtistas[i] == artistaN[j].id && idGeneros[i] == generoN[k].id){
                //en el caso de que se cumplan ambas condicioens entonces mostramos por pantalla el resultado y lo escribimos tambien en el archivo
                printf("%d;%s;%d:%d;%s;%s \n", listaPopularidad[i],listaCanciones[i],cancionN[i].min,cancionN[i].segundos,artistaN[j].nombre,generoN[k].nombre);
                fprintf(salida,"%d;%s;%d:%d;%s;%s \n", listaPopularidad[i],listaCanciones[i],cancionN[i].min,cancionN[i].segundos,artistaN[j].nombre,generoN[k].nombre);
                }
            }
        }
    }
    //nos aseguramos de cerrar el archivo
    printf("\nel listado de canciones se encuentra en el archivo: salida.out\n");
    fclose(salida);

}



int main(){
    //hacemos variables para medir el tiempo
    time_t inicio,fin;
    //comenzamos el contador en este punto
    inicio = time(NULL);
    //creamos variables para cada archivo
    FILE * canciones;
    FILE * generos;
    FILE * artistas;
    FILE * preferencias;
    //se abren estos archivos en modo de lectura
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
    //se llama a la funcion que genera el archivo de salida
    listarDatos(canciones,generos,artistas,preferencias,cantidadCan,cantidadGen,cantidadArt);
    
    //nos aseguramos de cerrar los archivos
    fclose(canciones);
    fclose(generos);
    fclose(artistas);
    fclose(preferencias);
    //terminamos el contador del tiempo en este punto
    fin = time(NULL);
    printf("\nTiempo de ejecucion: %f\n",difftime(fin,inicio));
    return 0;
}

/*
void dijkstra(int G[MAX][MAX],int n,int startnode);
 
int main()
{
    int G[MAX][MAX],i,j,n,u;
    printf("Enter no. of vertices:");
    scanf("%d",&n);
    printf("\nEnter the adjacency matrix:\n");
    
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&G[i][j]);
    
    printf("\nEnter the starting node:");
    scanf("%d",&u);
    dijkstra(G,n,u);
    
    return 0;
}
 
void dijkstra(int G[MAX][MAX],int n,int startnode)
{
 
    int cost[MAX][MAX],distance[MAX],pred[MAX];
    int visited[MAX],count,mindistance,nextnode,i,j;
    
    //pred[] stores the predecessor of each node
    //count gives the number of nodes seen so far
    //create the cost matrix
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(G[i][j]==0)
                cost[i][j]=INFINITY;
            else
                cost[i][j]=G[i][j];
    
    //initialize pred[],distance[] and visited[]
    for(i=0;i<n;i++)
    {
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }
    
    distance[startnode]=0;
    visited[startnode]=1;
    count=1;
    
    while(count<n-1)
    {
        mindistance=INFINITY;
        
        //nextnode gives the node at minimum distance
        for(i=0;i<n;i++)
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }
            
            //check if a better path exists through nextnode            
            visited[nextnode]=1;
            for(i=0;i<n;i++)
                if(!visited[i])
                    if(mindistance+cost[nextnode][i]<distance[i])
                    {
                        distance[i]=mindistance+cost[nextnode][i];
                        pred[i]=nextnode;
                    }
        count++;
    }
 
    //print the path and distance of each node
    for(i=0;i<n;i++)
        if(i!=startnode)
        {
            printf("\nDistance of node%d=%d",i,distance[i]);
            printf("\nPath=%d",i);
            
            j=i;
            do
            {
                j=pred[j];
                printf("<-%d",j);
            }while(j!=startnode);
    }
}
*/