#include "ls.h"
#include <iostream>
#include <cstdio>
#include <dirent.h>
#include <sys/stat.h>
#include <iomanip>
#include <ctime>


using namespace std ;

void ls(char bf[])
{

	DIR *dir ;
	struct dirent *file ;
	struct stat mystat ;

	char buf[512] ;
	char lastmodtime[100] ;

	dir = opendir(bf) ;
	

	while((file = readdir(dir)) != NULL)
	{
		sprintf(buf, "%s/%s", bf, file->d_name);
		stat(buf, &mystat) ;
		strftime(lastmodtime, 50, "%b %d %H:%M", localtime(&mystat.st_mtime));

		cout<<setw(50)<<left<<file->d_name ;
		cout<<setw(50)<<left<<mystat.st_size ;
		cout<<setw(50)<<left<< lastmodtime <<endl ;


		cout<<endl ;

	}
}
	