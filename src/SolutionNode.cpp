/*
 * SolutionNode.cpp
 *
 *  Created on: Aug 15, 2021
 *      Author: e212602
 */


#include "../Include/SolutionNode.h"

SolutionNode::SolutionNode(unsigned int w,unsigned int dp,SolutionNode *prev,SolutionNode *nxt)
{
	TaskWorkload = w;
	destProc = dp;
	prevNode = prev;
	nxtNode = nxt;
	CostStamp = 0;
}

SolutionNode::~SolutionNode()
{}


SolutionNode *SolutionNode::GetPrevNode(void)
{
	return prevNode;
}

SolutionNode *SolutionNode::GetNxtNode(void)
{
	return nxtNode;
}

unsigned int SolutionNode::GetWorkload(void)
{
	return TaskWorkload;
}

unsigned int SolutionNode::GetDestProc(void)
{
	return destProc;
}

void SolutionNode::SetCostStamp(double c)
{
	CostStamp = c;
}

double SolutionNode::GetCostStamp(void)
{
	return CostStamp;
}

void SolutionNode::SetNxtNode(SolutionNode *nxt)
{
	nxtNode = nxt;
}

void SolutionNode::SetPrevNode(SolutionNode *prev)
{
	prevNode = prev;
}
