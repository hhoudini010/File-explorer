
#include <iostream>
#include <sys/stat.h>
#include <cstdio>

using namespace std ;

void create_dir(char *fname1, char *dpath1)
{
	string fname = fname1 ;
	string dpath = dpath1 ;

	fname = dpath1 + fname ;

	strcpy(fname1,c_str()) ;

	mkdir(fname1, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH ) ;
}


void create_file(char *fname2, char *dpath2)
{

	chdir(dpath2) ;
	string fname = fname2 ;
	string dpath = dpath2 ;

	fname = dpath+fname ;

	strcpy(fname1,c_str()) ;

	chdir()

	FILE *fp = fopen(fname1,"w") ;
	fclose(fp) ;

}

