#include <stdio.h>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<unistd.h>
#include <stack>
#include "ls.h"

#define clear() printf("\033[H\033[J") //Clears the screen.


using namespace std ;


stack <string> back, forw ;

void curse(char *home1, char *path1, vector <string> &vec, char *curdir1)
{

	string path = path1 ;
	string home = home1 ;

	

	int pathlen = home.length() ;
	int nlines ;	   // Stores number of files/directories in a directory.
	int counter = 0 ;  // counter to help in cursor movement.

	string curdir = curdir1  ; // To print current directory

	

	char tempfiln[7000] ;
	strcpy(tempfiln,path.c_str()) ;
	chdir(tempfiln) ;
	char c ;

	

	string s ;

	//label : clear() ;
	label :cout<<curdir<<endl ;
	//cout<<path1<<endl ;
	nlines = ls(tempfiln, vec) ;
	struct stat me ;
	if(nlines != 0){
	nlines-- ;


	counter = 0 ;

	int flag = 0 ;


	printf("\033[%dA", nlines+1);


	while((c = getchar()) != 'q')		// Quit application on kbhit q ;
	{
		if(c == ':')
			return ;
		 flag = 0 ;

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
			else if( c == 'C')
			{
				if(forw.empty())
					continue ;
				else
				{
					back.push(path) ;
					path = forw.top() ;
					strcpy(path1,path.c_str()) ;
					forw.pop() ;
					flag = 1 ;
					goto label2 ;
				}
			}

			else if(c == 'D')
			{
				if(back.empty())
					continue ;
				else
				{
					forw.push(path) ;
					path = back.top() ;
					strcpy(path1,path.c_str()) ;
					back.pop() ;
					flag = 1 ;
					goto label2 ;
				}
			}
			

		}

		else if(c == 'h')
		{
			back.push(path) ;
			path = home ;
			strcpy(path1,path.c_str()) ;
			//curdir = "Desktop" ;
			goto label3 ;
		}

		else if( (c == 127) && path.length() > pathlen)
		{
			
			 	int len = path.length() ;
			 	for(int i = len-1 ; path[i] != '/'; i--)
			 		len-- ;
			 	path.resize(len-1) ;
			 	strcpy(path1,path.c_str()) ;

			 	len = path.length() ;
			 	for(int i = len-1 ; path[i] != '/'; i--)
			 		len-- ;

			 	curdir.assign(path,len,path.length()-len) ;
			 	strcpy(curdir1,curdir.c_str()) ;
			 	goto label3 ;
		}

		else if(c == '\n')									//Enter key pressed
		{
			 s = vec[counter] ;
			 if((s.compare("..") == 0) && path.length() > pathlen)
			 {
			 	back.push(path) ;
			 	int len = path.length() ;
			 	for(int i = len-1 ; path[i] != '/'; i--)
			 		len-- ;
			 	path.resize(len-1) ;
			 	strcpy(path1,path.c_str()) ;

			 	len = path.length() ;
			 	for(int i = len-1 ; path[i] != '/'; i--)
			 		len-- ;

			 	curdir.assign(path,len,path.length()-len) ;
			 	strcpy(curdir1,curdir.c_str()) ;

			 }
			 else if(s.compare(".") == 0)
			 	;
			 else{

			 	if(s.compare("..") != 0){
			 	back.push(path) ;
			 	path = path + "/" + vec[counter] ;
			 	strcpy(path1,path.c_str()) ;
			 	curdir = vec[counter] ;
			 	strcpy(curdir1,curdir.c_str()) ;
			 }
			 
			 }

			label2 :if(flag == 1)
			{
				int len = path.length() ;
			 	for(int i = len-1 ; path[i] != '/'; i--)
			 		len-- ;

			 	curdir.assign(path,len,path.length()-len) ;
			 	strcpy(curdir1,curdir.c_str()) ;
			}
			label3: strcpy(tempfiln, path.c_str()) ;
			stat(tempfiln, &me) ;
			chdir(tempfiln) ;
			 

			 if((S_ISDIR(me.st_mode)))    //Check for directory.
			 {
			 	clear() ;
				goto label ;
			}
			else
			{
				int len = path.length() ;
				for(int i = len-1 ; path[i] != '/'; i--)
			 		len-- ;
			 	path.resize(len-1) ;
			 	strcpy(path1,path.c_str()) ;

				char tempfiln1[500] ;
				pid_t pid ;
				 strcpy(tempfiln1, vec[counter].c_str()) ;
				// ret = chdir(tempfiln1) ;
				// if(ret == 0){
				pid = fork();
				if (pid == 0) 
  				execl("/usr/bin/open", "open",tempfiln1 , (char *)0);

  				
				
			}
		}
	}
	clear() ;
}
	

}