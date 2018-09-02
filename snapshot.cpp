#include <iostream>
#include <queue>
#include <dirent.h>
#include <sys/stat.h>
#include "ls.h"

using namespace std ;

void snapshot(string path, string home, string dumpfile)
{
	char dumpfile1[1000], home1[1000] ;
	strcpy(dumpfile1,dumpfile.c_str()) ;
	strcpy(home1,home.c_str()) ;
	create_file(dumpfile1, home1) ;

	queue <string> q ;
	DIR *dr ;
	struct dirent *file ;
	struct stat mystat ;
	string temp1 = home + "/" + dumpfile ;
	FILE *fp ;
	fp = fopen(temp1.c_str(),"wa+") ;
	q.push(path) ;

	while(!q.empty())                                           
	{
		path = q.front()  ;
		q.pop() ;

		fputs(path.c_str(),fp) ;
		
		dr = opendir(path.c_str()) ;
		readdir(dr) ;
		readdir(dr) ;

		fputs("\n\n",fp) ;

		while((file = readdir(dr)) != NULL)
		{
			string temp = path + '/' + file->d_name ;
			stat(temp.c_str(),&mystat) ;

			if(S_ISDIR(mystat.st_mode))
				q.push(temp) ;
			else
			{
				fputs(file->d_name,fp) ;
				fputs("\n",fp) ;
			}
		}

	}

	fclose(fp) ;

}