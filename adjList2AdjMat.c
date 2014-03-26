#include "mex.h"
#include "matrix.h"

/**
 * Author: lintseju
 * Date: 2014/03/26
 *
 * Convert adjacent list to adjacent matrix
 *
 * Input: a m by n matrix L stores edges information in adjacent list, and a scalar opt indicate the processing cases.
 * L(i,j) is the jth neighbor node of node i, if L(i,j) == -1, then igore this entry.
 * opt = 0 or no opt: directed graph, and set M(i,i) = 0 for all i
 * opt = 1: undirected graph, and set M(i,i) = 0 for all i
 * opt = 2: directed graph, and set M(i,i) = 1 for all i
 * opt = 3: undirected graph, and set M(i,i) = 1 for all i
 *
 * Output: a m by m matrix M stores edges information in adjacent matrix.
 * M(i,j) = 1 if there is an edge from node i to node j, otherwise M(i,j) = 0.
 *
 * Sample usage:
 * list = [2 3 4;-1 -1 -1;-1 -1 -1;-1 -1 -1];
 * matrix = list2AdjMat(list)
 * matrix =
 *
 *   0     1     1     1
 *   0     0     0     0
 *   0     0     0     0
 *   0     0     0     0
 * matrix = list2AdjMat(list, 3)
 * matrix =
 *
 *   1     1     1     1
 *   1     1     0     0
 *   1     0     1     0
 *   1     0     0     1
 *
 */

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int i, j, m = mxGetM(prhs[0]), n = mxGetN(prhs[0]), idx;
    double *list = mxGetPr(prhs[0]), *matrix;
    double opt;
    /*Set opt*/
    if(nrhs == 2)
        opt = mxGetScalar(prhs[1]);
    else
        opt = 0;
    
    plhs[0] = mxCreateDoubleMatrix(m, m, mxREAL);
    matrix = mxGetPr(plhs[0]);
    for(i = 0;i < m * m;i++)
        matrix[i] = 0;
    
    for(i = 0;i < m;i++){
        for(j = 0;j < n;j++){
            idx = list[i + j * m];
            if(idx > 0){
                /*idx - 1 because MATLAB index is starting from 1*/
                matrix[i + (idx - 1) * m] = 1;
                /*Undirectede graph*/
                if(opt == 1 || opt == 3)
                    matrix[idx - 1 + i * m] = 1;
            }
        }
    }
    
    /*Set M(i,i)*/
    if(opt >= 2){
        for(i = 0;i < m;i++){
            matrix[i + i * m] = 1;
        }
    }else{
        for(i = 0;i < m;i++){
            matrix[i + i * m] = 0;
        }
    }
    
}
