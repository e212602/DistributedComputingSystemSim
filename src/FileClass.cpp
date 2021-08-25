/*
 * FileClass.cpp
 *
 *  Created on: Aug 15, 2021
 *      Author: e212602
 */


#include "../Include/FileClass.h"

File::File (char *fn,ios_base::openmode mode )
{
	fName = fn;
	fmode = mode;
	if(fmode == ifstream::in)
	{
		ifs.open (fName, fmode);
		if (!ifs.is_open())
		{
			cerr << "ERROR: \"" << fName << "\" cannot be openned" << endl;
			exit(1);
		}
	}
	else
	{
		ofs.open (fName, fmode);
		if (!ofs.is_open())
		{
			cerr << "ERROR: \"" << fName << "\" cannot be openned" << endl;
			exit(1);
		}
	}
}

File::~File()
{
	if(fmode == ifstream::in)
		ifs.close();
	else
		ofs.close();

}


unsigned int File::numOfEntry()
{
	string str;
	unsigned int cnt=0;
	goToBegin();
	while(!ifs.eof())
	{
		getline(ifs,str);
		cnt++;
	}
	return cnt-1;
}

void File::goToBegin()
{
	if(fmode == ifstream::in)
	{
		ifs.clear();
		ifs.seekg (0, ios::beg);
	}
	else
	{
		ofs.clear();
		ofs.seekp (0, ios::beg);
	}
}

bool File::ReadLine(unsigned int *s, double *d)
{
	string str;
	if(getline(ifs,str))
	{
		istringstream iss(str);
		if(!(iss >> *s >> *d))
		{
			cout << "Incorrect Format in file" << fName << endl;
			exit(-1);
		}
		return true;
	}
	else
	{
		cout << "cannot get line" << str << endl;
		return false;
	}
}

bool File::WriteLine (unsigned int *s, double *d )
{
	if(!(ofs << *s << " " << *d << "\n"))
	{
		cout << "Error Writing to file" << fName << endl << flush;
		return false;
	}
	else
	{
		return true;
	}
}

bool File::GetNameLength(unsigned int x,unsigned int *l)
{
	if(*(fName+x) == '.' )
		return true;

	if(GetNameLength(x+1,l))
		*l = *l + 1;
	else
		return false;

	if(*(fName+x) == '/')
		return false;
	else
		return true;

}

void File::GetName(unsigned int x,char *ptr)
{
	unsigned int ofst1=0;
	while(*(fName+ofst1) != '.' )
		ofst1++;

	x--;
	*(ptr+x) = '\0';
	while(x > 0)
	{
		ofst1--;
		x--;
		*(ptr+x) = *(fName+ofst1);
	}
}
