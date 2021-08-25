/*
 * FileClass.h
 *
 *  Created on: Aug 5, 2021
 *      Author: e212602
 */

#ifndef FILECLASS_H_
#define FILECLASS_H_

#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>

class File
{
	private:
		char *fName;	// path to file
		ifstream ifs;
		ofstream ofs;
		ios_base::openmode fmode;

	public:

		File (char *fn,ios_base::openmode mode);
		~File();

		unsigned int numOfEntry();
		void goToBegin();
		bool ReadLine (unsigned int *s, double *d );
		bool WriteLine (unsigned int *s, double *d );
		bool GetNameLength(unsigned int x,unsigned int *l);
		void GetName(unsigned int x,char *ptr);

};





#endif /* FILECLASS_H_ */
