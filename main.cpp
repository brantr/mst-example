#include <stdio.h>
#include <stdlib.h>
#include "spanning_tree.hpp"
#include "write_spanning_tree.hpp"
#include "rng.h"
#include "timer.h"

int main(int argc, char **argv)
{
	long n   = 100;
	int dim = 3;
	int nngb = 10;
	float bsq = 10.0;

	double t_a;
	double t_b;

	char fname[200];
	FILE *fp;

	if(argc==2)
		n = atoi(argv[1]);

	//print some info to screen
	printf("n = %ld, dim = %d\n",n,dim);

	//make data
	data.resize(extents[n][dim]);
	for(long i=0;i<n;i++)
		for(int k=0;k<dim;k++)
			data[i][k] = rng_uniform(0.0,1.0);

	//save data to file
	sprintf(fname,"points.txt");
	fp = fopen(fname,"w");
	fprintf(fp,"%ld\n",n);
	for(long i=0;i<n;i++)
		fprintf(fp,"%f\t%f\t%f\n",data[i][0],data[i][1],data[i][2]);
	fclose(fp);

	//build the kdtree
	t_a = timer();
	tree = new kdtree2(data,true);
	t_b = timer();
	printf("Time for tree build = %es.\n",t_b-t_a);

	//produce spanning trees
	t_a = timer();
	//produce_minimum_spanning_tree(data, n, dim, nngb, bsq);
	initialize_spanning_tree(n,dim);
	t_b = timer();
	printf("Time for spanning tree initialization = %es.\n",t_b-t_a);

	t_a = timer();
  construct_spanning_tree(data,n,dim,nngb);

  t_b = timer();
  printf("Time for spanning tree build = %es.\n",t_b-t_a);

	//write spanning trees
  sprintf(fname,"st.dat");
	write_spanning_tree(fname, cgst);


	t_a = timer();
  construct_minimum_spanning_tree(bsq,n);
	t_b = timer();
	printf("Time for minimum spanning tree build = %es.\n",t_b-t_a);

	//write minimum spanning trees
	sprintf(fname,"mst.dat");
	write_spanning_tree(fname, mst);


	//destroy the tree
	destroy_spanning_tree();

	//end program
	return 0;
}