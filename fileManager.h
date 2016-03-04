#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <stdio.h>
#include <sys/types.h> 
#include <dirent.h> 
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/**
*	isRegularFile takes in a string name of a path and will
*	return an integer value 0 if it is not a regular file 
*	and an integer vale 1 if it is a regular file.
**/
int isRegularFile(const char* path);

/**
*	Returns 1 if a file exists, returns 0 if it does not.
**/
int Exists(const char* path);

/**
*	bufferSize determines the amount of characters contained
*	in a file and returns the size of type long int.
**/
long int bufferSize(FILE* fp);

/**
*	fileToString will take in a pointer to a FILE and will
*	construct a single array out of the contents of the file.
**/
char* fileToStringSTDIO(const char* path);

/**
*	fileToString will take in a pointer to a FILE and will
*	construct a single array out of the contents of the file.
**/
char* fileToStringSYSTEM(const char* path);
#endif
