#include <stdio.h>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <termios.h>
#include <sys/stat.h>
#include "ls.h"

#define clear() printf("\033[H\033[J") //Clears the screen.


using namespace std ;
string path = "/Users/sandeepkumargupta/Desktop" ;


vector <string> vec, forward, backward ; //vec for storing file names in current directory.


int main(int argc, char const *argv[])
{
	


	int nlines ;	   // Stores number of files/directories in a directory.
	int counter = 0 ;  // counter to help in cursor movement.

	string curdir = "Desktop" ; // To print current directory
	struct termios tio ;
	

	char tempfiln[7000] ;
	strcpy(tempfiln,path.c_str()) ;
	char c ;

	tcgetattr(fileno(stdin), &tio) ;	

	tio.c_lflag &= ~ICANON ;
	tio.c_lflag &= ~ECHO ;
	tio.c_cc[VMIN] = 1 ;
	tio.c_cc[VTIME] = 0 ;

	tcsetattr(fileno(stdout), TCSANOW, &tio) ; // Shifting to Non-canonical.


	string s ;

	label : clear() ;
	cout<<curdir<<endl ;
	nlines = ls(tempfiln, vec) ;
	struct stat me ;
	if(nlines != 0){
	nlines-- ;


	counter = 0 ;

	


	printf("\033[%dA", nlines+1);


	while((c = getchar()) != 'q')		// Quit application on kbhit q ;
	{

		if(c == '\033')
		{
			c = getchar() ;
			c = getchar() ;

			if(c == 'A')
			{
				if(counter != 0)
				{
					cout<<"\033[1A" ;
					counter-- ;
				}
			}
			else if(c == 'B')
			{
				if(counter != nlines)
				{
					cout<<"\033[1B";
					counter++ ;
				}
			}
			

		}

		if(c == '\n')									//Enter key pressed
		{
			 s = vec[counter] ;
			 if((s.compare("..") == 0))
			 {
			 	int len = path.length() ;
			 	for(int i = len-1 ; path[i] != '/'; i--)
			 		len-- ;
			 	path.resize(len-1) ;

			 	len = path.length() ;
			 	for(int i = len-1 ; path[i] != '/'; i--)
			 		len-- ;

			 	curdir.assign(path,len,path.length()-len) ;

			 }
			 else if(s.compare(".") == 0)
			 	;
			 else{
			 	path = path + "/" + vec[counter] ;
			 	curdir = vec[counter] ;
			 }

			 strcpy(tempfiln, path.c_str()) ;
			 stat(tempfiln, &me) ;

			 if((S_ISDIR(me.st_mode)))    //Check for directory.
				goto label ;
		}
	}
	clear() ;
}
	




	return 0;
}