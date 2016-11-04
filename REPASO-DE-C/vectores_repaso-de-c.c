/* Código que demuestra algunos puntos de C sobre vectores*/
// compilo con gcc vectores_repaso-de-c.c -o vectores_repaso-de-c.x
// ejecuto con, por ejemplo, ./vectores_repaso-de-c.x 10

//Con "#include" puedo incorporar códigos ajenos, algunos vienen por default con C
//stdio viene de "standard in/out" y contiene la función "printf"
#include <stdio.h> // para usar fprintf()
#include <stdlib.h> //para usar atoi() y atol()

//En este código, mostramos como reservar memoria para un puntero y así hacer un vector
//También vemos como hacer un vector de tamaño fijo sin necesidad de punteros
//Mostramos como se puede direccionar un puntero hacía un vector fijo
//También vemos como usar salidas a archivos o a pantalla
int main(int argc, char *argv[]){
  int i;
  int *vector;
  int N = atoi(argv[1]); 
  int v[N];

  //gestión de la salida del programa
  //abro un puntero FILE 
  FILE * myfilep;
  //salida a un archivo, pero podríamos sacarlo por pantalla con myfile = "stdout";
  myfilep = fopen("/tmp/vectores.txt", "w+");
  //comentar la próxima línea si quiero la salida por archivo
  myfilep = stdout; //stdout es un puntero FILE estándar de C que siempre está abierto (igual que stderr)
  
  //reservo memoria para el vector de enteros vector
  vector = malloc( N * sizeof(int));

  // en un loop pongo valores a vector y los imprimo
  fprintf(myfilep, "imprimo el contenido de vector[]\n");
  for(i=0; i<N; i++){
    vector[i] = N-i;
    fprintf(myfilep, "vector[%d] = %d\n", i, vector[i]);
  }
  fprintf(myfilep, "------------------------------\n");

  // en un loop pongo valores a v y los imprimo
  fprintf(myfilep, "imprimo el contenido de v[]\n");
  for(i=0; i<N; i++){
    v[i] = i;
    fprintf(myfilep, "v[%d] = %d\n", i, v[i]);
  }
  fprintf(myfilep, "------------------------------\n");

  //redirecciono el puntero vector hacia v
  vector = &v[0];
  
  // en un loop pongo los nuevos valores de vector y los imprimo
  fprintf(myfilep, "imprimo el contenido de vector[] que debería ser igual a v[]\n");
  for(i=0; i<N; i++){
    fprintf(myfilep, "vector[%d] = %d\n", i, vector[i]);
  }
  fprintf(myfilep, "------------------------------\n");

  fclose(myfilep); //hay que ser prolijos y cerrar FILEs abiertos ;)
  
  return 0; 
}
