#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <string.h>
//-----------------------------
#include <pthreadUtils.h>
#include <Pipes.h>
#include <pipeHandler.h>
#ifndef SW
#include "SockPipes.h"
#include "vhdlCStubs.h"
#else
#include "aa_c_model.h"
#endif

void Exit(int sig)
{
	fprintf(stderr, "## Break! ##\n");
	exit(0);
}

const float eps = 1e-6;
int eq(float f1, float f2){
	return (f1 > f2 ? f1 - f2 : f2 - f1) < eps;
}

void swap(float *x, float *y) {
   float temp;
   temp = *x;
   *x = *y;
   *y = temp;
   return;
}

const int N = 16;
const int lim = 10;
void gauss(float a[N][N+1], float ans[N]){
    for (int col = 0,row = 0; col < N; ++col){
        for(int i = 0; i < N; ++i){
            if(i != row) {
                float c = a[i][col] / a[row][col];
                for (int j = col; j <= N; ++j)
                    a[i][j] -= a[row][j] * c;
            }
		}
        ++row;
    }
    for (int i = 0; i < N; ++i)
		ans[i] = a[i][N] / a[i][i];
}

int main(int argc, char* argv[])
{
	int _err_ = 0;
	signal(SIGINT,  Exit);
  	signal(SIGTERM, Exit);

#ifdef SW
	start_daemons(NULL, 0);
#endif
	
	
	float A[N][N+1];
	float B[N];
	float result[N];
	int i,j;
	for(i = 0; i < N; i++){
		for(j = 0;j <= N;j++){
			A[i][j] = rand() % lim;
		}
	}
	
	gauss(A,B);
	
	for(i = 0; i < N; i++){
		for(j = 0;j <= N;j++){
			write_float32("input_data",A[i][j]);
		}
	}
	
	for (i = 0; i < N; i++){
		result[i] = read_float32("output_data");
	}
	
	_err_ = 0;
	
	for (i = 0; i < N; i++){
		if(!eq(B[i],result[i])){
			_err_ = 1;
		}
	}
	
	fprintf(stderr,"All done: %s\n", _err_ ? "Failure :-(" : "Success :-)");
	return(0);
}

