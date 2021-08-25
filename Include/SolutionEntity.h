/*
 * SolutionEntity.h
 *
 *  Created on: Aug 10, 2021
 *      Author: e212602
 */

#ifndef SOLUTIONENTITY_H_
#define SOLUTIONENTITY_H_

#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>

#include "../Include/SolutionNode.h"
#include "../Include/ProcessorClass.h"

class SolutionEntity
{
private:
	SolutionNode *TopPtr;
	SolutionNode *rootPtr;
	unsigned int numNodes;
	double CurrentCost;
	Processor **pePtr;
public:
	SolutionEntity(Processor **ptr);
	~SolutionEntity();
	void InsertNode(unsigned int w,unsigned int dp);
	void RemoveTopNode(void);
	SolutionNode *GetTopNode(void);
	SolutionNode *GetRootNode(void);
	double GetCost(void);
	void printSolution(unsigned int nump);
	SolutionEntity& operator= (const SolutionEntity& rhs);
};


#endif /* SOLUTIONENTITY_H_ */
