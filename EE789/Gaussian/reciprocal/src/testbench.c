#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
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

int main(int argc, char* argv[])
{
	int _err_ = 0;
	signal(SIGINT,  Exit);
  	signal(SIGTERM, Exit);

#ifdef SW
	start_daemons(NULL, 0);
#endif

	
	float idx;
	for(idx = 1; idx < 127; idx++)
	{
		float result;
#ifdef SW
		divider(idx,&result);
#else
		result = divider(idx);
#endif
		float correct;
		correct = 1.0 / idx;
		if(!eq(correct,result))
		{
			fprintf(stderr,"Error: Got 1 / %f = %f, expected %f.\n", idx, result, correct);
			_err_ = 1;
		}
	}
	
	fprintf(stderr,"All done: %s\n", _err_ ? "Failure :-(" : "Success :-)");
	return(0);
}
