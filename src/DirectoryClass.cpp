/*
 * DirectoryClass.c
 *
 *  Created on: Aug 15, 2021
 *      Author: e212602
 */



#include "../Include/DirectoryClass.h"



dirClass::dirClass(char *dir)
{
	dName = dir;
	dp = opendir(dir);
	if(dp == NULL)
	{
		cout << "Failed to open dir " << dir << endl;
		exit(-1);
	}
	numFiles = CountFiles();
	len_d = FindLength(dName);
	CreateFileList();
}

dirClass::~dirClass()
{
	unsigned int i;
	for(i=0;i<numFiles;i++)
		delete fptr[i];

	delete[] fptr;
	closedir(dp);
}


void dirClass::CreateFileList(void)
{
	unsigned int cnt,len_f;
	fptr = new char*[numFiles];
	cnt=0;
	ResetDir();
	while((dirp = readdir(dp)) != NULL)
	{
		if(*(dirp->d_name) == '.')
			continue;

		len_f = FindLength(dirp->d_name);
		fptr[cnt] = new char[len_f+len_d];
		ConcatenateStrings(fptr[cnt],dName,dirp->d_name);
		cnt++;
	}


}

unsigned int dirClass::CountFiles(void)
{
	unsigned int cnt=0;
	ResetDir();
	while((dirp = readdir(dp)) != NULL)
		if(dirp->d_type == DT_REG)
		{
			if(*(dirp->d_name) == '.')
				continue;
			cnt++;
		}

	return cnt;

}

void dirClass::ResetDir(void)
{
	seekdir(dp,0); // reset directory
}

unsigned int dirClass::FindLength(char *str)
{
	unsigned int ofst=0;
	while(*(str+ofst) != '\0')
		ofst++;

	return ofst+1;
}

void dirClass::ConcatenateStrings(char *dest,char *s1,char *s2)
{
	unsigned int ofst1=0,ofst2=0;
	while(*(s1+ofst1) != '\0')
	{
		*(dest+ofst1) = *(s1+ofst1);
		ofst1++;
	}

	*(dest+ofst1) = '/';
	ofst1++;

	while(*(s2+ofst2) != '\0')
	{
		*(dest+ofst1) = *(s2+ofst2);
		ofst1++;
		ofst2++;
	}

	*(dest+ofst1) = '\0';

}

char **dirClass::AccessFiles(void)
{
	return fptr;
}
