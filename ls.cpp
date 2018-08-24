#include "ls.h"
#include <iostream>
#include <cstdio>
#include <dirent.h>
#include <sys/stat.h>
#include <iomanip>
#include <ctime>
#include <pwd.h>
#include <grp.h>


using namespace std ;

int ls(char bf[])
{

	DIR *dir ;
	struct dirent *file ;
	struct stat mystat ;
	int nlines = 0 ;

	char buf[512] ;
	char lastmodtime[100] ;
	long long int siz ;

	dir = opendir(bf) ;
	

	while((file = readdir(dir)) != NULL)
	{
		sprintf(buf, "%s/%s", bf, file->d_name);  // Storing the path of the file in buf.
		stat(buf, &mystat) ;
		strftime(lastmodtime, 50, "%b %d %H:%M", localtime(&mystat.st_mtime)); // get last modified time in required format.

		struct passwd *un = getpwuid(mystat.st_uid); //To get user name.
		struct group  *gn = getgrgid(mystat.st_gid); //To get group name.


		siz = mystat.st_size ; //siz stores size of file/directory in bytes.

		

		//Print file permissions.

		cout<<((S_ISDIR(mystat.st_mode)) ? "d" : "-")
		    <<( (mystat.st_mode & S_IRUSR) ? "r" : "-")
		    <<( (mystat.st_mode & S_IWUSR) ? "w" : "-")
		    <<( (mystat.st_mode & S_IXUSR) ? "x" : "-")
		    <<( (mystat.st_mode & S_IRGRP) ? "r" : "-")
		    <<( (mystat.st_mode & S_IWGRP) ? "w" : "-")
		    <<( (mystat.st_mode & S_IXGRP) ? "x" : "-")
		    <<( (mystat.st_mode & S_IROTH) ? "r" : "-")
		    <<( (mystat.st_mode & S_IWOTH) ? "w" : "-")
		    <<setw(27)<<left<<( (mystat.st_mode & S_IXOTH) ? "x" : "-") ;

		//Print remaining values.

		cout<<setw(27)<<left<<un->pw_name ;
		cout<<setw(27)<<left<<gn->gr_name ;

		cout<<setw(27)<<left<<file->d_name ;
		if(siz < 1000)
			cout<<setw(4)<<right<<siz<<setw(27)<<left<<"B" ;
		else if(siz > 1000 && siz < 100000)
			cout<<setw(4)<<right<<setprecision(3)<<(float)siz/1000<<setw(27)<<left<<"K" ;
		else if(siz >100000 && siz < 100000000 )
			cout<<setw(4)<<right<<setprecision(3)<<(float)siz/1000000<<setw(27)<<left<<"M" ;
		cout<<setw(27)<<left<< lastmodtime <<endl ;

		nlines++ ;

	}

	return nlines ;
}
	