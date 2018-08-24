#include <stdio.h>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <termios.h>
#include <sys/stat.h>
#include "ls.h"

#define clear() printf("\033[H\033[J") //Clears the screen.
char path[60000] = "/Users/sandeepkumargupta/Desktop" ;


using namespace std ;

vector <string> vec, forward, backward ; //vec for storing file names in current directory.


int main(int argc, char const *argv[])
{
	


	int nlines ;	   // Stores number of files/directories in a directory.
	int counter = 0 ;  // counter to help in cursor movement.

	struct termios tio ;
	

	char tempfiln[300] ;
	char c ;

	tcgetattr(fileno(stdin), &tio) ;	

	tio.c_lflag &= ~ICANON ;
	tio.c_lflag &= ~ECHO ;
	tio.c_cc[VMIN] = 1 ;
	tio.c_cc[VTIME] = 0 ;

	tcsetattr(fileno(stdout), TCSANOW, &tio) ; // Shifting to Non-canonical.



	label : clear() ;
	nlines = ls(path, vec) ;
	struct stat me ;
	if(nlines != 0){
	nlines-- ;
	counter = 0 ;

	printf("\033[490A");

	int flag = 0 ;

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
			string s = vec[counter] ;

			strcpy(tempfiln,s.c_str()) ;
			sprintf(path, "%s/%s", path,tempfiln);    // Path created.
			stat(path, &me) ;

			 if((S_ISDIR(me.st_mode)))    //Check for directory.
				goto label ;
		}
	}
	clear() ;
}
	




	return 0;
}