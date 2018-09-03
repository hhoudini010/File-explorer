
#include <iostream>
#include <sys/stat.h>
#include <cstdio>
#include <cstring>
 #include <fcntl.h>



using namespace std ;

void cre_dir(char *fname1, char *dpath1)
{
	string fname = fname1 ;
	string dpath = dpath1 ;

	char temp1[5000] ;

	fname = dpath + '/' + fname ;

	strcpy(temp1,fname.c_str()) ;

	mkdir(temp1, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH ) ;
}


void create_file(char *fname2, char *dpath2)
{

	string fname = fname2 ;
	string dpath = dpath2 ;
	char temp[5000] ;

	fname = dpath + '/' + fname ;

	strcpy(temp,fname.c_str()) ;

	open(temp, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

}

