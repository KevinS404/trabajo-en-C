#include <iostream>

using namespace std;

int main()
{
    int fecha[99],hora[99],a,i;
    string tipo[99],entrega[99];
    bool verificador[5]= true;
    while(verificador == true){
      cout<<"\n ingrese opcion:";
      cout<<"\n \t 1:ingresar nueva casilla";
      cout<<"\n\t 2: imprimir registro";
      cout<<"\n\t 3:salir:";
      cin>>a;
 
      if(a==1){
          for(int i=0; i<=99;i++){
            cout<<"\n\n ingrese fecha formato ddmmaaaa"<<endl;
            cin>>fecha[i];
            cout<<"\t ingrese tipo de documento: "<<endl;
            cin>>tipo[i];
            cout<<"\t ingrese entrega: "<<endl;
            cin>>entrega[i];
            cout<<"\t ingrese hora: "<<endl;
            cin>>hora[i];
            }
      }

      else if(a==2){
          for(int i=0;i<=99;i++){
            cout<<fecha[i]<<"\t"<<tipo[i]<<"\t"<<entrega[i]<<"\t"<<hora[i]<<endl;
          }
      }
        
      else if(a == 3){
        cout<<"\n FIN DEL PROGRAMA."<<endl;
        verficador = false;
      }
      else{
        cout<<"\n INGRESAR UNA OPCION VALIDA"<<endl;
      }
        
    }
          
    
    
    
        
    
    
    
    
    return 0;
}