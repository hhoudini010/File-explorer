
#include <iostream>
#include <stdio.h>
#include <termios.h>


#include "ls.h"

using namespace std ;



int main(int argc, char const *argv[])
{
	
	
	struct termios tio ;

	tcgetattr(fileno(stdin), &tio) ;	

	tio.c_lflag &= ~ICANON ;
	tio.c_lflag &= ~ECHO ;
	tio.c_cc[VMIN] = 1 ;
	tio.c_cc[VTIME] = 0 ;

	tcsetattr(fileno(stdout), TCSANOW, &tio) ; // Shifting to Non-canonical.


	curse() ;
	
	return 0;
}