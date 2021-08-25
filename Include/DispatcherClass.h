/*
 * DispatcherClass.h
 *
 *  Created on: Aug 10, 2021
 *      Author: e212602
 */

#ifndef DISPATCHERCLASS_H_
#define DISPATCHERCLASS_H_

#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>

#include "../Include/FileClass.h"
#include "../Include/DirectoryClass.h"
#include "../Include/ProcessorClass.h"
#include "../Include/SolutionEntity.h"

class Dispatcher
{
private:

	Processor **pePtr;
	unsigned int numPE;
	unsigned int N;
	SolutionEntity *sol;
	SolutionEntity *fsol;
	char **fptr;
	unsigned int factor;
	int BackTrack;
	double GlobalCost;

public:
	Dispatcher(unsigned int ws,unsigned int fact, char *dir);
	~Dispatcher();
	void SetUpProc(char *dir);
	void Start(void);
	void GetProcInfo(void);
	double EvPriority(unsigned int id);
	void Proposed_Scheduler(unsigned int remSize);
	void PrintSolution(void);
};



#endif /* DISPATCHERCLASS_H_ */
