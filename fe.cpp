#include <stdio.h>
#include <iostream>
#include <dirent.h>
#include "ls.h"

using namespace std ;

int main(int argc, char const *argv[])
{
	ls("/Users/sandeepkumargupta") ;
	
	return 0;
}