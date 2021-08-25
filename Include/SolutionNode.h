/*
 * SolutionNode.h
 *
 *  Created on: Aug 6, 2021
 *      Author: e212602
 */

#ifndef SOLUTIONNODE_H_
#define SOLUTIONNODE_H_

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

class SolutionNode
{
private:
	unsigned int TaskWorkload;
	unsigned int destProc;
	double CostStamp;
	SolutionNode *prevNode;
	SolutionNode *nxtNode;

public:
	SolutionNode(unsigned int w,unsigned int dp=0,SolutionNode *prev=NULL,SolutionNode *nxt=NULL);
	~SolutionNode();
	SolutionNode *GetPrevNode(void);
	SolutionNode *GetNxtNode(void);
	void SetNxtNode(SolutionNode *nxt);
	void SetPrevNode(SolutionNode *prev);
	unsigned int GetWorkload(void);
	unsigned int GetDestProc(void);
	void SetCostStamp(double c);
	double GetCostStamp(void);


};


#endif /* SOLUTIONNODE_H_ */
