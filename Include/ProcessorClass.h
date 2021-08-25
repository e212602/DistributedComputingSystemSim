/*
 * ProcessorClass.h
 *
 *  Created on: Aug 10, 2021
 *      Author: e212602
 */

#ifndef PROCESSORCLASS_H_
#define PROCESSORCLASS_H_

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
#include "../Include/Parameters.h"

class Processor
{
private:
	int id;
	char  *CoreName;
	double priority;
	double compTime;
	Task *TaskPool;
	unsigned int num_tsk;
	double max_sp;

public:
	Processor(int pe=0,File *fd=NULL,unsigned int factor=0);
	~Processor();
	double GetPriority(void);
	void UpdatePriority(unsigned int w);
	double GetComptTime(void);
	void UpdateCompTime(unsigned int w);
	char *GetName(void);
	void SetProcName(char *s=NULL);
	void SetPriority(double pr);
	void ConstructTaskPool(File *fd=NULL,unsigned int factor=0);
	Task *AccessTaskTable(void);
	void SortTasks(void);
	void FindMaxSpeed(void);
	double GetMaxSpeed(void);
	unsigned int GetNumTask(void);
	void RetPriority(unsigned int w);
	void RetCompTime(unsigned int w);

};



#endif /* PROCESSORCLASS_H_ */
