/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2006-2012  Gabor Csardi <csardi.gabor@gmail.com>
   334 Harvard st, Cambridge MA, 02139 USA
   
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

// small function to print elements of a vector in stdout (terminal screen)
void print_vector(igraph_vector_t *v, FILE *f) {
  long int i;
  for (i=0; i<igraph_vector_size(v); i++) {
    fprintf(f, " %li", (long int) VECTOR(*v)[i]);
  }
  fprintf(f, "\n");
}

int main() {

  // define variables
  igraph_t g;
  igraph_vector_t v;
  int ret;

  // build a small network by defining edge list vector
  igraph_vector_init(&v, 8);
  VECTOR(v)[0]=0; VECTOR(v)[1]=1;
  VECTOR(v)[2]=1; VECTOR(v)[3]=2;
  VECTOR(v)[4]=2; VECTOR(v)[5]=3;
  VECTOR(v)[6]=2; VECTOR(v)[7]=2;
  //create graph
  igraph_create(&g, &v, 0, 1);

  //output neighbors associated to k_out
  igraph_neighbors(&g, &v, 2, IGRAPH_OUT);
  igraph_vector_sort(&v);
  print_vector(&v, stdout);

  //output neighbors associated to k_in
  igraph_neighbors(&g, &v, 2, IGRAPH_IN);
  igraph_vector_sort(&v);
  print_vector(&v, stdout);

  //output neighbors associated to k
  igraph_neighbors(&g, &v, 2, IGRAPH_ALL);
  igraph_vector_sort(&v);
  print_vector(&v, stdout);
 
  igraph_vector_destroy(&v);
  igraph_destroy(&g);
  return 0;
}
