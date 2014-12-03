#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_sort.h>
#include "spanning_tree.hpp"
#include "write_spanning_tree.hpp"
#include "rng.h"
#include "timer.h"

int main(int argc, char **argv)
{
	long n   = 10;
	int dim = 3;
	int nngb = 20;
	float bsq = 10000000000.0;
	int weight;
	float w;
  int fac = 100000000;

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
    {
			//data[i][k] = rng_gaussian(0.0,1.0);
			//data[i][k] = rng_levy(1.0);
			data[i][k] = rng_levy(1.1);
			//data[i][k] = rng_tdist(500.0);
      //data[i][k] = rng_uniform(0.0,1.0);
      //data[i][k] = pow(data[i][k],6);
    }


	//save data to file
	sprintf(fname,"points.txt");
	fp = fopen(fname,"w");
	fprintf(fp,"%ld\n",n);
	for(long i=0;i<n;i++)
		fprintf(fp,"%e\t%e\t%e\n",data[i][0],data[i][1],data[i][2]);
	fclose(fp);
	sprintf(fname,"points.dat");
	fp = fopen(fname,"w");
	fwrite(&n,1,sizeof(int),fp);
	for(long i=0;i<n;i++)
	{
		fwrite(&data[i][0],1,sizeof(float),fp);
		fwrite(&data[i][1],1,sizeof(float),fp);
		fwrite(&data[i][2],1,sizeof(float),fp);

	}
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



	FILE *fpi = fopen("index.txt","w");
	for(long i=0;i<mst.size();i++)
	{		
		w = fac*mst[i].dis;
		weight = (int) floor(w);
		//if(fmod(w,1)>0.5)
		//	weight++;
		//fprintf(fpi,"%ld\t%ld\t%d\n",mst[i].idx_A,mst[i].idx_B,i+1);
		fprintf(fpi,"%ld\t%ld\n",mst[i].idx_A,mst[i].idx_B);

	}
	fclose(fpi);

/*
	for(long i=0;i<mst.size();i++)
	{
		w = fac*mst[i].dis;
		weight = (int) floor(w);
		//if(fmod(w,1)>0.5)
		//	weight++;
		printf("%ld\t%ld\t%d\n",mst[i].idx_A,mst[i].idx_B,weight);
		printf("%ld\t%ld\t%d\n",mst[i].idx_A,mst[i].idx_B,weight);

	}
*/
	//destroy the tree
	destroy_spanning_tree();

	//end program
	return 0;
}
