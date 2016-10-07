#include <igraph.h>

int main(void) {
  igraph_real_t avg_path;
  igraph_t sfgraph;
  igraph_t graph;
  igraph_vector_t dimvector;
  igraph_vector_t edges;
  int i;

  /*SF graph variables*/
  igraph_integer_t n;
  igraph_real_t power;
  igraph_integer_t m;
  const igraph_vector_t *outseq;
  igraph_bool_t outpref;
  igraph_real_t A;
  igraph_bool_t directed;
  igraph_barabasi_algorithm_t algo;
  const igraph_t *start_from;

  n=7e3;
  power = 2.5;
  m = 3;

  igraph_barabasi_game(&sfgraph,
		       n,
		       power, 
		       m,
		       NULL,
		       0,
		       1,
		       0,
		       IGRAPH_BARABASI_PSUMTREE,
		       // IGRAPH_BARABASI_BAG, 
		       NULL);
  
  igraph_vector_init(&dimvector, 2);
  VECTOR(dimvector)[0]=30;
  VECTOR(dimvector)[1]=30;
  igraph_lattice(&graph, &dimvector, 0, IGRAPH_UNDIRECTED, 0, 1);

  igraph_rng_seed(igraph_rng_default(), 42);
  igraph_vector_init(&edges, 20);
  for (i=0; i<igraph_vector_size(&edges); i++) {
    VECTOR(edges)[i] = rand() % (int)igraph_vcount(&graph);
  }

  igraph_average_path_length(&sfgraph, &avg_path, IGRAPH_UNDIRECTED, 1);
  printf("Average path length (lattice):            %f\n", (double) avg_path);

  igraph_add_edges(&graph, &edges, 0);
  igraph_average_path_length(&sfgraph, &avg_path, IGRAPH_UNDIRECTED, 1);
  printf("Average path length (randomized lattice): %f\n", (double) avg_path);
  
  igraph_vector_destroy(&dimvector);
  igraph_vector_destroy(&edges);
  igraph_destroy(&sfgraph);

  return 0;
}




