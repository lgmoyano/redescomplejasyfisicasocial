/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2007-2012  Gabor Csardi <csardi.gabor@gmail.com>
   334 Harvard street, Cambridge, MA 02139 USA
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA 
   02110-1301 USA

*/

#include <igraph.h>

int igraph_vector_between(const igraph_vector_t* v, const igraph_vector_t* lo,
		const igraph_vector_t* hi) {
	return igraph_vector_all_le(lo, v) && igraph_vector_all_ge(hi, v);
}

void test_unweighted() {
  igraph_t g;
  igraph_vector_t edges, eb;
  long int i;
  long int no_of_edges;
  igraph_vector_t modularity, weights, membership;
  igraph_matrix_t merges;

  igraph_vector_init(&modularity,0);
  igraph_matrix_init(&merges,0,0);
  igraph_vector_init(&weights,0);
  igraph_vector_init(&membership,0);

  /* Zachary Karate club */
  igraph_small(&g, 0, IGRAPH_UNDIRECTED, 
	       0,  1,  0,  2,  0,  3,  0,  4,  0,  5,
	       0,  6,  0,  7,  0,  8,  0, 10,  0, 11,
	       0, 12,  0, 13,  0, 17,  0, 19,  0, 21,
	       0, 31,  1,  2,  1,  3,  1,  7,  1, 13,
	       1, 17,  1, 19,  1, 21,  1, 30,  2,  3,
	       2,  7,  2,  8,  2,  9,  2, 13,  2, 27,
	       2, 28,  2, 32,  3,  7,  3, 12,  3, 13,
	       4,  6,  4, 10,  5,  6,  5, 10,  5, 16,
	       6, 16,  8, 30,  8, 32,  8, 33,  9, 33,
	       13, 33, 14, 32, 14, 33, 15, 32, 15, 33,
	       18, 32, 18, 33, 19, 33, 20, 32, 20, 33,
	       22, 32, 22, 33, 23, 25, 23, 27, 23, 29,
	       23, 32, 23, 33, 24, 25, 24, 27, 24, 31,
	       25, 31, 26, 29, 26, 33, 27, 33, 28, 31,
	       28, 33, 29, 32, 29, 33, 30, 32, 30, 33,
	       31, 32, 31, 33, 32, 33,
	       -1);  


  /* fast greedy algorithm */
  igraph_community_fastgreedy(&g, 0, &merges, &modularity, 
			      /*membership=*/ &membership);
  //show_results(&g, &modularity, &merges, stdout); 

  printf("Membership vector from the fast greedy algorithm:\n");
  for (i=0; i<igraph_vcount(&g); i++) {
    printf("%.0lf ", VECTOR(membership)[i]);
  }
  printf("\n");
  printf("\n");
  
  /* edge betweenness */

  igraph_vector_init(&edges, 0);
  igraph_vector_init(&eb, 0);
  igraph_community_edge_betweenness(&g, &edges, &eb, 0 /*merges */,
				    0 /*bridges */, /*modularity=*/ 0,
				    /*membership=*/ 0,
				    IGRAPH_UNDIRECTED,
				    /*weights=*/ 0);
  
  printf("Edges in the Zachary Karate Club network:\n");
  no_of_edges=igraph_ecount(&g);
  for (i=0; i<no_of_edges; i++) {
    printf("%li ", (long int)VECTOR(edges)[i]);
  }
  printf("\n");
  printf("\n");

  printf("Edge betweenness values for the Zachary Karate Club network:\n");
  for (i=0; i<no_of_edges; i++) {
    printf("%.2f ", VECTOR(eb)[i]);
  }
  printf("\n");
  printf("\n");

  igraph_vector_destroy(&eb);
  igraph_vector_destroy(&edges);
  igraph_destroy(&g);
}

#define EPS 1e-4

void test_weighted() {
  igraph_t g;
  long int i;
  long int no_of_edges;
  igraph_vector_t edges, eb, weights;
  igraph_real_t weights_array[] = { 4, 1, 3, 2, 5, 8, 6, 7 };

  igraph_vector_t modularity, membership;
  igraph_matrix_t merges;

  igraph_vector_init(&modularity,0);
  igraph_matrix_init(&merges,0,0);
  igraph_vector_init(&membership,0);

  printf("A smaller example:\n");
  
  /* Small graph as follows: A--B--C--A, A--D--E--A, B--D, C--E */
  igraph_small(&g, 0, IGRAPH_UNDIRECTED, 
      0, 1, 0, 2, 0, 3, 0, 4, 1, 2, 1, 3, 2, 4, 3, 4, -1);
  igraph_vector_view(&weights, weights_array, igraph_ecount(&g));

  igraph_vector_init(&edges, 0);
  igraph_vector_init(&eb, 0);

  /* fast greedy algorithm */
  igraph_community_fastgreedy(&g, 0, &merges, &modularity, 
			      /*membership=*/ &membership);
  //show_results(&g, &modularity, &merges, stdout); 

  printf("Membership vector from the fast greedy algorithm:\n");
  for (i=0; i<igraph_vcount(&g); i++) {
    printf("%.0lf ", VECTOR(membership)[i]);
  }
  printf("\n");
  printf("\n");

  igraph_community_edge_betweenness(&g, &edges, &eb, 0 /*merges */,
				    0 /*bridges */, /*modularity=*/ 0,
				    /*membership=*/ 0,
				    IGRAPH_UNDIRECTED,
				    &weights);
  
  printf("These are all the edges:\n");
  no_of_edges=igraph_ecount(&g);
  for (i=0; i<no_of_edges; i++) {
    printf("%li ", (long int)VECTOR(edges)[i]);
  }
  printf("\n");
  printf("\n");
  
  printf("These are the betweenness values:\n");
  for (i=0; i<no_of_edges; i++) {
    printf("%.2f ", VECTOR(eb)[i]);
  }
  printf("\n");
  printf("\n");

  igraph_vector_destroy(&eb);
  igraph_vector_destroy(&edges);
  igraph_destroy(&g);
}

// main calls the two funcions above
int main() {
  test_unweighted();
  test_weighted();
  return 0;
}
