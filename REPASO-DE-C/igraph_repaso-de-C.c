/* Código que demuestra algunos puntos de C*/
// compilo con gcc igraph_repaso-de-C.c `pkg-config --libs --cflags igraph` -o igraph_repaso-de-C.x
// ejecuto con, por ejemplo, ./igraph_repaso-de-c.x 300

//Con "#include" puedo incorporar códigos ajenos, algunos vienen por default con C
//stdio viene de "standard in/out" y contiene la función "printf"
#include <stdio.h> // para usar printf()
#include <stdlib.h> //para usar rand()
#include <math.h> // para usar floor()
#include <time.h> // para usar time()
#include <igraph.h> //para usar igraph_t etc.

//función que toma un valor racional y devuelve un entero al azar entre 1 y 1000
int myrandomnumber(float somefloat){
  int temporal, result;
  long int r;

  r = rand(); 			//numero entre 0 y RAND_MAX (un número grande)
  temporal = (int) floor(somefloat); // sacamos la mantisa y convertimos a entero con un cast
  result = (int) fabs((r % 10000) * somefloat) % 1000; //bajamos el valor de r, lo multiplicamos por nuestro entero y lo volvemos a bajar, positivo

  //printf("in myrandomnumber: rand %li temporal %d result %d\n", r, temporal, result);

  return(result + 1); //sumamos uno para descartar que devuelva ceros
}

// este programa usa la función de números aleatorios para generar una lista de enlaces y con ella un grafo
int main(int argc, char *argv[]){
  
  int i, c, u, v;
  igraph_t g;
  
  srand(time(NULL));  // inicializamos el generador de números aleatorios, podemos usar srand(42),
		      // donde 42 es arbitrario, si queremos siempre el mismo número random
  
  c = myrandomnumber(atol(argv[1])); //llamo a la función que está arriba con el argumento que paso en línea de comandos
  fprintf(stderr, "el entero aleatorio es %d\n", c); // imprimo el valor en pantalla

  // a partir de c, construyo una lista de links y la pongo en un archivo
  // abro un puntero FILE para mi archivo, como escritura
  FILE *mi_file;
  mi_file = fopen("/tmp/edge_list.txt", "w");

  // con este loop genero los enlaces y lo pongo en el archivo recién abierto
  v = c;
  for(i=0; i<c; i++){
    u = myrandomnumber(v);
    v = myrandomnumber(u); 
    fprintf(mi_file, "%d %d\n", u, v);
  }
  fclose(mi_file); 		//cierro el *FILE, lo voy a reusar luego como lectura

  //abro de nuevo, pero como lectura
  mi_file = fopen("/tmp/edge_list.txt", "r");
  //armo un objeto igraph_t leyendo los links del archivo
  igraph_read_graph_edgelist(&g, mi_file, 0, 0); //3er argumento 0 (ver descripción de la función en el manual)
  fclose(mi_file);				 //cierro el *FILE

  //llamo a esta función para sacar posibles enlaces repetidos y autoenlaces
  igraph_simplify(&g, 1, 1, 0); //último argumento 0 (ver descripción de la función en el manual)

  //saco en pantalla algunas cantidades sobre el grafo, links, |V|, y |E|
  fprintf(stderr, "\n----Los links son: \n");
  igraph_write_graph_edgelist(&g, stderr);
  //
  fprintf(stderr, "\n---- |V|=%d, |E|=%d\n", igraph_vcount(&g), igraph_ecount(&g));
  igraph_destroy(&g);
  
  return 0;
} 
