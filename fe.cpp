#include <stdio.h>
#include <iostream>
#include <dirent.h>
#include <termios.h>
#include "ls.h"

#define clear() printf("\033[H\033[J") //Clears the screen.

using namespace std ;

int main(int argc, char const *argv[])
{
	
	clear() ;

	int nlines ;
	int counter = 0 ;

	nlines = ls("/Users/sandeepkumargupta") ;
	nlines-- ;

	struct termios tio ;
	char c ;

	tcgetattr(fileno(stdin), &tio) ;

	tio.c_lflag &= ~ICANON ;
	tio.c_lflag &= ~ECHO ;
	tio.c_cc[VMIN] = 1 ;
	tio.c_cc[VTIME] = 0 ;

	tcsetattr(fileno(stdout), TCSANOW, &tio) ;

	printf("\033[490A");

	do
	{

		while(((c = getchar()) == '\033'  ) )
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

		

	}while(c !='q') ;

	clear() ;


	




	return 0;
}