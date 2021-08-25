/*
 * SolutionEntity.cpp
 *
 *  Created on: Aug 15, 2021
 *      Author: e212602
 */

#include "../Include/SolutionEntity.h"

SolutionEntity::SolutionEntity(Processor **ptr)
{
	TopPtr = NULL;
	rootPtr = NULL;
	numNodes = 0;
	CurrentCost = 0;
	pePtr = ptr;
}

SolutionEntity::~SolutionEntity()
{
	while(numNodes != 0)
		RemoveTopNode();
}

void SolutionEntity::InsertNode(unsigned int w,unsigned int dp)
{
	SolutionNode *SNode;

	SNode = new SolutionNode(w,dp,TopPtr,NULL);
	if(SNode == NULL)
	{
		cout << "Failed to allocate Solution Node" << endl;
		exit(-1);
	}

	if(numNodes == 0)
		rootPtr = SNode;
	else
		TopPtr->SetNxtNode(SNode);


	TopPtr = SNode;
	numNodes++;

	pePtr[dp]->UpdateCompTime(w);
	pePtr[dp]->UpdatePriority(w);

	if(CurrentCost < pePtr[dp]->GetComptTime())
		CurrentCost = pePtr[dp]->GetComptTime();

	TopPtr->SetCostStamp(CurrentCost);
/*	cout << "Task of size " << w << " is assigned to " << pePtr[dp]->GetName() << ", The cost is " << CurrentCost << endl;*/

}

void SolutionEntity::RemoveTopNode(void)
{
	SolutionNode *tmpPtr;
	tmpPtr = TopPtr->GetPrevNode();
	pePtr[TopPtr->GetDestProc()]->RetCompTime(TopPtr->GetWorkload());
	pePtr[TopPtr->GetDestProc()]->RetPriority(TopPtr->GetWorkload());
	delete TopPtr;
	TopPtr = tmpPtr;
	numNodes--;
	if(TopPtr == NULL)
	{
		CurrentCost = 0;
/*		cout << "Empty Solution " << endl;*/
	}
	else
	{
		CurrentCost = TopPtr->GetCostStamp();
/*		cout << "Task of size " << TopPtr->GetWorkload() << " is removed from " << pePtr[TopPtr->GetDestProc()]->GetName() << ", The cost is " << CurrentCost << endl;*/
	}



}

SolutionNode *SolutionEntity::GetTopNode(void)
{
	return TopPtr;
}

SolutionNode *SolutionEntity::GetRootNode(void)
{
	return rootPtr;
}

double SolutionEntity::GetCost(void)
{
	return CurrentCost;
}

void SolutionEntity::printSolution(unsigned int nump)
{
	SolutionNode *tmpNode;
	unsigned int numProc,max_ws=0;
	unsigned int **tmpBuff;
	unsigned int i,j;
	numProc = nump;
	for(i=0;i<numProc;i++)
		if(max_ws < pePtr[i]->GetNumTask())
			max_ws = pePtr[i]->GetNumTask();

	tmpBuff = new unsigned int*[numProc];
	for(i=0;i<numProc;i++)
		tmpBuff[i] = new unsigned int[max_ws];

	for(i=0;i<numProc;i++)
		for(j=0;j<max_ws+1;j++)
			tmpBuff[i][j] = 0;

	tmpNode = rootPtr;
	cout << "This solution has a cost of " << CurrentCost << endl;
	for(i=0;i<numNodes;i++)
	{
		//cout << "Assign Task of workload " << tmpNode->GetWorkload() << " to Processor " << pePtr[tmpNode->GetDestProc()]->GetName() << endl;
		tmpBuff[tmpNode->GetDestProc()][tmpNode->GetWorkload()]++;
		tmpNode = tmpNode->GetNxtNode();
	}

	for(i=0;i<numProc;i++)
	{
		cout << pePtr[i]->GetName() << ": ";
		for(j=0;j<max_ws+1;j++)
		{
			if(tmpBuff[i][j] != 0)
				cout << j << "x" << tmpBuff[i][j] << "\t" ;
		}
		cout << endl;
	}


	for(i=0;i<numProc;i++)
		delete tmpBuff[i];

	delete[] tmpBuff;
}

SolutionEntity& SolutionEntity::operator= (const SolutionEntity& rhs)
{

	SolutionNode *SNode;
	SolutionNode *tmpNode;
	unsigned int i;
	while(numNodes != 0)
	{
		tmpNode = TopPtr->GetPrevNode();
		delete TopPtr;
		TopPtr = tmpNode;
		numNodes--;
		if(TopPtr == NULL)
			CurrentCost = 0;
		else
			CurrentCost = TopPtr->GetCostStamp();
	}

	numNodes = rhs.numNodes;
	CurrentCost = rhs.CurrentCost;
	tmpNode = rhs.rootPtr;
	for(i=0;i<numNodes;i++)
	{
		SNode = new SolutionNode(tmpNode->GetWorkload(),tmpNode->GetDestProc(),TopPtr,NULL);
		if(SNode == NULL)
		{
			cout << "Failed to allocate Solution Node" << endl;
			exit(-1);
		}
		if(i==0)
			rootPtr = SNode;
		else
			TopPtr->SetNxtNode(SNode);

		TopPtr = SNode;
		tmpNode = tmpNode->GetNxtNode();
	}

	return *this;
}

