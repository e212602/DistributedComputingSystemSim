/*
 * DirectoryClass.h
 *
 *  Created on: Aug 11, 2021
 *      Author: e212602
 */

#ifndef DIRECTORYCLASS_H_
#define DIRECTORYCLASS_H_

#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>

class dirClass
{
private:
	DIR *dp;
	struct dirent *dirp;
	char **fptr;
	char *dName;
	unsigned int numFiles;
	unsigned int len_d;

public:
	dirClass(char *dir=NULL);
	~dirClass();
	void CreateFileList(void);
	unsigned int CountFiles(void);
	void ResetDir(void);
	unsigned int FindLength(char *str);
	void ConcatenateStrings(char *dest,char *s1,char *s2);
	char **AccessFiles(void);

};


#endif /* DIRECTORYCLASS_H_ */
