
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <vector>



#include "ls.h"

using namespace std ;

#define clear() printf("\033[H\033[J") //Clears the screen.

vector <string> vec ; //vec for storing file names in current directory.

int main(int argc, char const *argv[])
{
	char home[5000], path[5000];
	 getcwd(home,2000) ;

	strcpy(path,home);

	char curdir[500] ;

	{
		int len = strlen(path) ;
		int j = 0 ;

		for(int i = len-1; path[i] != '/' ; i--)
		{
			len-- ;
		}

		for(j = 0 ; len < strlen(path); )
		{
			curdir[j++] = path[len++] ;
		}

	}

	
	
	struct termios tio ;

	label : clear() ; 

	tcgetattr(fileno(stdin), &tio) ;	

	tio.c_lflag &= ~ICANON ;
	tio.c_lflag &= ~ECHO ;
	tio.c_cc[VMIN] = 1 ;
	tio.c_cc[VTIME] = 0 ;

	tcsetattr(fileno(stdout), TCSANOW, &tio) ; // Shifting to Non-canonical.

	curse(home,path,vec,curdir) ;

	cout<<"\033[490B";
	cout<<"$" ;


	
char c, comm_name[50], fname[1000], pname[5000] ;
vector<char> v ;



while((c = getchar()) != 'q')
{
	if(c=='\033')
	{
		goto label ;
	}
	else if(c=='\n')
	{
		clear() ;
		cout<<"\033[490A";
		cout<<curdir<<endl ;
		ls(path,vec) ;
		cout<<"\033[490B";
		cout<<"$" ;
	}
	else
	{
		v.push_back(c) ;
		cout<<c ;
	}
	
}

	return 0;
}