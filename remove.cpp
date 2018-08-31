#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <cstdio>
#include <unistd.h>
#include "ls.h"

using namespace std ;

void remo(string dpath)
{
	remove(dpath.c_str()) ;
}

void remod(string dpath1)
{
	DIR *dr ;
	struct dirent *file ;
	struct stat mystat ;

	string dpath = dpath1 ;

	stat(dpath.c_str(), &mystat) ;

	if(S_ISDIR(mystat.st_mode))
	{
		dr = opendir(dpath1.c_str()) ;
		readdir(dr) ;
		readdir(dr) ;

		while((file = readdir(dr)) != NULL)
		{
			string temp;
			temp = dpath + "/" + file->d_name ;
			remod(temp.c_str()) ;
		}
		dpath = dpath1 ;
		rmdir(dpath.c_str()) ;

	}
	else
		remo(dpath.c_str()) ;
	


}