/*
 * ProcessorClass.cpp
 *
 *  Created on: Aug 15, 2021
 *      Author: e212602
 */



#include "../Include/ProcessorClass.h"

Processor::Processor(int pe,File *fd,unsigned int factor)
{
	unsigned int len=0;
	id = pe;
	fd->GetNameLength(0, &len);
	CoreName = new char[len];
	fd->GetName(len, CoreName);
	priority = 0;
	compTime = 0;
	num_tsk = fd->numOfEntry();
	TaskPool = new Task[num_tsk];
	ConstructTaskPool(fd,factor);
	FindMaxSpeed();
	SortTasks();
}

Processor::~Processor()
{
	delete[] CoreName;
	delete[] TaskPool;
}
double Processor::GetPriority(void)
{
	return priority;
}

void Processor::UpdatePriority(unsigned int w)
{
	priority-= TaskPool[num_tsk-w].size;
}

double Processor::GetComptTime(void)
{
	return compTime;
}

void Processor::UpdateCompTime(unsigned int w)
{
	compTime+= TaskPool[num_tsk-w].time;
}

char *Processor::GetName(void)
{
	return CoreName;
}

void Processor::SetPriority(double pr)
{
	priority = pr;
}

void Processor::ConstructTaskPool(File *fd,unsigned int factor)
{
	unsigned int i;
	fd->goToBegin();
	for(i=0;i<num_tsk;i++)
	{
		fd->ReadLine(&TaskPool[i].size, &TaskPool[i].time);
		TaskPool[i].speed = ((double) (TaskPool[i].size*factor)) / TaskPool[i].time;
	}

}

Task *Processor::AccessTaskTable(void)
{
	return TaskPool;
}

double Processor::GetMaxSpeed(void)
{
	return max_sp;
}

unsigned Processor::GetNumTask(void)
{
	return num_tsk;
}

void Processor::SortTasks(void)
{
	unsigned int i,j;
	double tmp_max=0,tmp_time=0;
	unsigned int tmp_size=0;
	unsigned int tmp_idx=0;
	for(i=0;i<num_tsk;i++)
	{

		for(j=i;j<num_tsk;j++)
			if(tmp_max < TaskPool[j].speed)
			{
				tmp_size = TaskPool[j].size;
				tmp_max = TaskPool[j].speed;
				tmp_time = TaskPool[j].time;
				tmp_idx = j;
			}

		TaskPool[tmp_idx].size = TaskPool[i].size;
		TaskPool[tmp_idx].speed = TaskPool[i].speed;
		TaskPool[tmp_idx].time = TaskPool[i].time;
		TaskPool[i].size = tmp_size;
		TaskPool[i].speed = tmp_max;
		TaskPool[i].time = tmp_time;
		tmp_max=0;
	}
}

void Processor::FindMaxSpeed(void)
{
	double tmp_max=0;
	unsigned int tmp_indx=0;
	unsigned int i;
	for(i=0;i<num_tsk;i++)
		if(TaskPool[i].speed > tmp_max)
		{
			tmp_max = TaskPool[i].speed;
			tmp_indx = i;
		}

	num_tsk = tmp_indx+1;
	max_sp = tmp_max;

}

void Processor::RetPriority(unsigned int w)
{
	priority+= TaskPool[num_tsk-w].size;
}

void Processor::RetCompTime(unsigned int w)
{
	compTime-= TaskPool[num_tsk-w].time;
}
