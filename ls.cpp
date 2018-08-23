#include "ls.h"
#include <iostream>
#include <cstdio>
#include <dirent.h>
#include <sys/stat.h>
#include <iomanip>


using namespace std ;

void ls(char bf[])
{

	DIR *mydir ;
	struct dirent *myfile ;
	struct stat mystat ;

	char buf[512] ;

	mydir = opendir(bf) ;
	string s ;
	

	while((myfile = readdir(mydir)) != NULL)
	{
		sprintf(buf, "%s/%s", bf, myfile->d_name);
		cout<<setw(50)<<left<<myfile->d_name ;

		s = myfile->d_name ;

		stat(buf, &mystat) ;

		cout<<setw(50)<<left<<mystat.st_size<<endl ;
		cout<<endl ;

	}
}
	