
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <vector>



#include "ls.h"

using namespace std ;

#define clear() printf("\033[H\033[J") //Clears the screen.

int main(int argc, char const *argv[])
{
	char home[5000], path[5000];
	 getcwd(home,2000) ;

	strcpy(path,home);

	clear() ;
	
	struct termios tio ;

	label : tcgetattr(fileno(stdin), &tio) ;	

	tio.c_lflag &= ~ICANON ;
	tio.c_lflag &= ~ECHO ;
	tio.c_cc[VMIN] = 1 ;
	tio.c_cc[VTIME] = 0 ;

	tcsetattr(fileno(stdout), TCSANOW, &tio) ; // Shifting to Non-canonical.



	curse(home,path) ;

	cout<<"\033[490B";
	cout<<"$" ;

	tcgetattr(fileno(stdin), &tio) ;

	tio.c_lflag |= ECHO ;

	tcsetattr(fileno(stdout), TCSANOW, &tio) ;



	
char c ;
vector<char> v ;



while((c = getchar()) != '\033')
{
	v.push_back(c) ;
}

	return 0;
}