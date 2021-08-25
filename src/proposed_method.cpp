//============================================================================
// Name        : proposed_method.cpp
// Author      : Mahmoud Alasmar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <vector>
#include <sys/time.h>
#include <time.h>
#include <cstring>

#include "../Include/DispatcherClass.h"

int main(int argc, char** argv) {

	int N,fact;
	if(argc != 4)
	{
		cout << "Incorrect argument format" << endl;
		exit(-1);
	}

	N = atoi(argv[1]);
	fact = atoi(argv[2]);

	struct timeval start, end;

	gettimeofday(&start, NULL);
	Dispatcher disp(N,fact,argv[3]);
	gettimeofday(&end, NULL);

	double tstart = start.tv_sec + start.tv_usec/1000000.;
	double tend = end.tv_sec + end.tv_usec/1000000.;
	double t_sec = (tend - tstart);

	disp.Start();

	disp.PrintSolution();
	cout << "Total Execution Time (sec) For Finding The Solution = " << t_sec << endl;
	return 0;
}
