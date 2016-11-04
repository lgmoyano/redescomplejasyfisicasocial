/* Código que demuestra algunos puntos de C*/
// compilo con gcc punteros_repaso-de-c.c -o punteros_repaso-de-c.x
// ejecuto con, por ejemplo, ./punteros_repaso-de-c.x 5

//Con "#include" puedo incorporar códigos ajenos, algunos vienen por default con C
//stdio viene de "standard in/out" y contiene la función "printf"
#include <stdio.h> // para usar printf()
#include <stdlib.h> //para usar atoi()

//todos los programas de C tienen que tener una función main()
int main(int argc, char *argv[]){
  //normalmente declaramos variables al principio del código (aunque es posible declarar después también)
  int *pc; 			  // pc es un puntero a un entero, puede contener una dirección de memoria que contenga a su vez un enetero
  int i, c;			  // c puede contener a un entero
  

  //ejemplo basado en http://www.programiz.com/c-programming/c-pointers
  //Ponemos un valor en la variable c, vemos en que dirección de memoria está y verificamos su contenido
  c=22;
  printf("Acabo de inicializar la variable c con el valor 22\n");
  printf("La dirección de memoria de c es %d\n", &c);
  printf("El valor contenido en c es %d\n\n", c);
  printf("--------------------------------------------------\n");

  //Apuntamos el puntero pc hacia c, y repetimos la verificación de memoria y contenido, pero de pc
  pc=&c;
  printf("Copio la dirección de memoria de c al puntero pc o \"apunto pc hacia c\" (estoy inicializando pc)\n");
  printf("Imprimo el valor de pc, que será la dirección de memoria de c: %d\n", pc);
  printf("Imprimo el contenido de memoria a donde apunta pc, o sea el contenido de c: %d\n\n", *pc);
  printf("--------------------------------------------------\n");

  //Cambio el valor de c, y veo si esto se refleja en pc
  c=4384739;
  printf("Cambio el valor de c a %d\n", c);
  printf("Imprimo nuevamente el valor de pc (un valor de memoria): %d\n", pc);
  printf("Imprimo el contenido que está en la memoria a donde pc apunta, o sea, el nuevo valor de c: %d\n\n", *pc);
  printf("--------------------------------------------------\n");

  //Cambio el valor usando el puntero y verifico todo de nuevo, pero usando c
  *pc=atoi(argv[1]); //la función atoi, que la saco de sdtlib.h, convierte una variable char (como se define argv[]) a un entero
  printf("Cambio el contenido al cual pc apunta a %d\n", *pc);
  printf("Imprimo la dirección de memoria de c: %d\n", &c);
  printf("Imprimo el contenido de la variable c: %d\n\n", c);
  printf("--------------------------------------------------\n");
  
  return 0; //la función main tiene que retornar algo, en este caso un 0
}
