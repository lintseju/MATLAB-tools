#include "mex.h"
#include "matrix.h"
#include <float.h>

/*
 * Author: lintseju
 * Date: 2013/12/05
 *
 * This is MATLAB mex implementation of brute force nearest neighbor search. The
 * distance is calculated in 2 norm.
 *
 * Input:
 * A m by n matrix for data set and 1 by n vector for query.
 *
 * Output:
 * A scalar, the index of the nearest neighbor in data. And a 1 by n vector, the 
 * nearest neighbor.
 * 
 * Sample usage:
 * >> data = rand(10000,5);
 * >> query = rand(1,5);
 * >> tic;[idx nearestNeighbor] = nnSearchMEX(data,query);toc;
 * Elapsed time is 0.000446 seconds.
 * >> tic;idx = knnsearch(data,query);toc;
 * Elapsed time is 0.031132 seconds.
 *
 * Testing were run on Windows XP with Intel Core2Duo E6550 CPU and 2G RAM
 *
 */

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	int i, j, n = mxGetN(prhs[0]), m = mxGetM(prhs[0]), idx = -1;
	double *data = mxGetPr(prhs[0]), *query = mxGetPr(prhs[1]), *output, *output_idx;
	double min = DBL_MAX, now;

	/*find nearest neighbor by brute force*/
	for(i = 0;i < m;i++){
		now = 0;
		for(j = 0;j < n;j++){
			now += (data[i + j * m] - query[j]) * (data[i + j * m] - query[j]);
		}
		if(min > now){
			min = now;
			idx = i;
		}
	}
	
	/*create output*/
	plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
	plhs[1] = mxCreateDoubleMatrix(1, n, mxREAL);
	output_idx = mxGetPr(plhs[0]);
	output = mxGetPr(plhs[1]);
	for(i = 0;i < n;i++){
		output[i] = data[idx + i * m];
	}
	/*MATLAB index is starting from 1*/
	*output_idx = idx + 1;
}
