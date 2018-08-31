
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <cstring>

#include "ls.h"

using namespace std ;

#define clearscr() printf("\033[H\033[J") //Clears the screen.

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

	label : clearscr() ; 

	tcgetattr(fileno(stdin), &tio) ;	

	tio.c_lflag &= ~ICANON ;
	tio.c_lflag &= ~ECHO ;
	tio.c_cc[VMIN] = 1 ;
	tio.c_cc[VTIME] = 0 ;

	tcsetattr(fileno(stdout), TCSANOW, &tio) ; // Shifting to Non-canonical.

	curse(home,path,vec,curdir) ;

	cout<<"\033[490B";
	cout<<"$" ;


	
char c ;

string comm_name ;

string p ;



while((c = getchar()) != 'q')
{
	if(c=='\033')
	{
		goto label ;
	}
	else if(c=='\n')
	{
		string as, df ;
		
		//coinput.str(std::string());

		

		stringstream coinput(p) ;
		 coinput>>comm_name ;

		if(comm_name.compare("create_dir") == 0 || comm_name.compare("create_file") == 0)
		{
			
			cout<<endl ;
			string fname,dpath ;
			coinput>>fname ;
			coinput>>dpath ;
			
			
			string hm = home ;
			char dpath1[5000],fname1[500] ;

			if(dpath.compare(".") == 0)
				dpath = hm ;
			else
				dpath = hm + "/" + dpath ;

			strcpy(dpath1,dpath.c_str()) ;
			strcpy(fname1,fname.c_str()) ;

		

			if(comm_name.compare("create_dir") == 0)
				cre_dir(fname1,dpath1) ;
			else
				create_file(fname1,dpath1) ;

			p.clear() ;
			
		}

		else if(comm_name.compare("copy") == 0)
		{	

			vector <string> temp ;
			string hel ;

			while(coinput>>hel)
				temp.push_back(hel) ;

			string hm = home ;
			int len = temp.size() ;

			string dpath = hm + '/' + temp[len-1] ;
			temp[len-1] = dpath ;

			// for(int i = 0 ; i < temp.size(); i++)
			// 	cout<<temp[i]<<endl ;

			copy(temp,path) ;
			getcwd(path,sizeof(path)) ;
			p.clear() ;


		}

		
		

		clearscr() ;
		cout<<"\033[490A";
		cout<<curdir<<endl ;
		ls(path,vec) ;
		cout<<"\033[490B";
		cout<<"$" ;


	}
	else
	{
		p.push_back(c) ;
		cout<<c ;
	}
	
}

	return 0;
}