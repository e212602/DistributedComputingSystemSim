/*
 * DispatcherClass.cpp
 *
 *  Created on: Aug 15, 2021
 *      Author: e212602
 */



#include "../Include/DispatcherClass.h"


Dispatcher::Dispatcher(unsigned int ws,unsigned int fact, char *dir)
{
	N = ws;
	factor = fact;
	SetUpProc(dir);
	sol = new SolutionEntity(pePtr);
	if(sol == NULL)
	{
		cout << "Failed to allocate Solution Entity" << endl;
		exit(-1);
	}

	fsol = new SolutionEntity(pePtr);
	if(fsol == NULL)
	{
		cout << "Failed to allocate final Solution Entity" << endl;
		exit(-1);
	}

}

Dispatcher::~Dispatcher()
{
	unsigned int i;

	delete sol;
	delete fsol;
	for(i=0;i<numPE;i++)
	{
		delete pePtr[i];
	}
	delete[] pePtr;
}

void Dispatcher::SetUpProc(char *dir)
{
	unsigned int i;
	File *fd;
	dirClass dirObj(dir);
	numPE = dirObj.CountFiles();
	fptr = dirObj.AccessFiles();

	pePtr = new Processor*[numPE];
	if(pePtr == NULL)
	{
		cout << "Failed to allocate Processor" << endl;
		exit(-1);
	}

	for(i=0;i<numPE;i++)
	{
		fd = new File(fptr[i],ifstream::in);
		pePtr[i] = new Processor(i,fd,factor);
		delete fd;
	}

	for(i=0;i<numPE;i++)
		pePtr[i]->SetPriority(EvPriority(i));


}


void Dispatcher::GetProcInfo(void)
{
	unsigned int i;
	for(i=0;i<numPE;i++)
	{
		cout << "This is " << pePtr[i]->GetName() <<" My initial priority is " << pePtr[i]->GetPriority() << endl;
	}
}

void Dispatcher::Start(void)
{
	unsigned int remSize;
	GetProcInfo();
	BackTrack = 1000;
	GlobalCost = 1000;
	remSize = N;
	Proposed_Scheduler(remSize);
}



double Dispatcher::EvPriority(unsigned int id)
{
	double stot=0;
	unsigned int i;
	for(i=0;i<numPE;i++)
	{
		stot+=pePtr[i]->GetMaxSpeed();
	}

	return (pePtr[id]->GetMaxSpeed()*((double) N) / stot);
}

void Dispatcher::Proposed_Scheduler(unsigned int remSize)
{
	unsigned int pe=0,i,n;
	double tmp_prty=0;
	Task *TaskPool;
	if(remSize > 0)
	{
		/*Pick Processing Element*/
		for(i=0;i<numPE;i++)
			if(tmp_prty < pePtr[i]->GetPriority())
			{
				pe = i;
				tmp_prty = pePtr[i]->GetPriority();
			}

		/*Pick Task that has maximum speed*/
		TaskPool = pePtr[pe]->AccessTaskTable();
		n = pePtr[pe]->GetNumTask();
		for(i=0;i<n;i++)
		{
			if(TaskPool[i].size <= remSize)
			{
				sol->InsertNode(TaskPool[i].size, pe);
				if(sol->GetCost() > GlobalCost)
				{
					sol->RemoveTopNode();
					continue;
				}
				if(BackTrack > 0)
				{
					Proposed_Scheduler(remSize-TaskPool[i].size);
					BackTrack--;
				}
				sol->RemoveTopNode();
			}
		}

	}
	else
	{
		GlobalCost = sol->GetCost();
		*fsol = *sol;
	}


}

void Dispatcher::PrintSolution(void)
{
	fsol->printSolution(numPE);
}
