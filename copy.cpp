
#include <vector>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls.h"

using namespace std ;

void copy(vector <string> &temp, char *curdir)
{
	int siz = temp.size() ;
	vector <string> temp1 ;

	// char curdir[1000] ;               // Current directory.

	DIR *dr ;
	struct dirent *file ;

	string curdir1 = curdir ;


	char fname1[100], dpath1[1000] ;
	struct stat mystat ;
	string dpath = temp[siz-1] ;             //Destination path
	strcpy(dpath1,dpath.c_str()) ;

	string fname ;

	for (int i = 0; i < siz-1; ++i)
	{

		fname = temp[i] ;

		curdir1 = curdir1 + '/' + fname ;
			strcpy(curdir,curdir1.c_str()) ;

		strcpy(fname1,fname.c_str()) ;

		stat(curdir, &mystat) ;

		if(S_ISREG(mystat.st_mode))
		{
			//Handle file copy.
			FILE *in, *out ;
			int c ;
			dpath = dpath + '/' + fname ;
			strcpy(dpath1,dpath.c_str()) ;

			in = fopen(curdir,"rb") ;
			out = fopen(dpath1,"wb") ;

			while((c = fgetc(in)) != EOF)
				fputc(c,out) ;

			fclose(in) ;
			fclose(out) ;

			int len = curdir1.length() ;
				for(int i = len-1 ; curdir1[i] != '/'; i--)
			 		len-- ;
			 	curdir1.resize(len-1) ;
			 	strcpy(curdir,curdir1.c_str()) ;

			 	int len1 = dpath.length() ;
				for(int i = len1-1 ; dpath[i] != '/'; i--)
			 		len1-- ;
			 	dpath.resize(len1-1) ; 
			 	strcpy(dpath1,dpath.c_str()) ;

		}

		else if(S_ISDIR(mystat.st_mode))
		{

			cre_dir(fname1,dpath1) ;

			dpath = dpath + '/' + fname ;
			strcpy(dpath1,dpath.c_str()) ;
			

			dr = opendir(curdir) ;

			readdir(dr);
			readdir(dr) ;

			temp1.clear() ;

			while((file = readdir(dr)) != NULL)
			{
				temp1.push_back(file->d_name) ;
			}
			temp1.push_back(dpath) ;

			if(temp1.size() > 1)
			copy(temp1,curdir) ;

			int len = curdir1.length() ;
				for(int i = len-1 ; curdir1[i] != '/'; i--)
			 		len-- ;
			 	curdir1.resize(len-1) ;
			 	strcpy(curdir,curdir1.c_str()) ;


			int len1 = dpath.length() ;
				for(int i = len1-1 ; dpath[i] != '/'; i--)
			 		len1-- ;
			 	dpath.resize(len1-1) ; 
			 	strcpy(dpath1,dpath.c_str()) ;




		}
	}
	


}