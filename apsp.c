#include "mex.h"
#include "matrix.h"

/*
 * Author: lintseju
 * Data: 2013/10/22
 *
 * This is implementation of Floyd-Warshall algorithm for finding all pair
 * shortest path.
 *
 * Input:
 * Dense matrix that element (i,j) indicate the weighting of edge (i,j).
 * Use "inf" if there is no edge between node i and j.
 *
 * Output:
 * Dense matrix that element (i,j) indicate the shortest path distance 
 * between node i and j.
 * 
 * Sample usage:
 * g = [0 1 inf;1 0 1.2;inf 1.2 0];
 * apsp(g)
*/

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int i, j, k, n = mxGetN(prhs[0]);
    double *input = mxGetPr(prhs[0]), *output;
    
    /*create output*/
    plhs[0] = mxCreateDoubleMatrix(n, n, mxREAL);
    output = mxGetPr(plhs[0]);
    for(i = 0;i < n * n;i++)
        output[i] = input[i];

    /*calculate all pair shortest path*/
    for(k = 0;k < n;k++){
        for(i = 0;i < n;i++){
            for(j = 0;j < n;j++){
                if(output[i + k * n] + output[k + j * n] < output[i + j * n])
                    output[i + j * n] = output[i + k * n] + output[k + j * n];
            }
        }
    }

}