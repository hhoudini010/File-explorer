
#include <cstdlib>
#include <stdio.h>
#include <vector>

#ifndef ls_h
#define ls_h

int ls(char[], std::vector <std::string> &vec ) ;
void curse(char a[], char b[], std::vector <std::string> &vec, char curdir[]) ;
void cre_dir(char *fname1, char *dpath1) ;
void create_file(char *fname2, char *dpath2) ;
void copy(std::vector <std::string> &temp, char *curdir) ;
void remo(std::string dpath) ;
void remod(std::string dpath1) ;

#endif