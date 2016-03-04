#include "fileManager.h"

/**
 * Checks if a given path is a regular file.
 */
int isRegularFile(const char* path)
{	
	struct stat buf;
    	stat(path, &buf);
		
	return S_ISREG(buf.st_mode);
}


/**
 * Check if a file located at a given path exists.
 */
int Exists(const char* path)
{
	int exists = 0;

	if(isRegularFile(path))
	{	
		FILE* fp = fopen(path, "r");
	
		if(fp != NULL)
		{
			exists = 1;
		}
		
		fclose(fp);	
	}

	return exists;
}

/**
 * Returns buffer size.
 */
long int bufferSize(FILE* fp)
{
	long int BUFSIZE = 0;

	//Obtain the size of a file
	fseek(fp, 0, SEEK_END);
	BUFSIZE = ftell(fp);
	rewind(fp);

	return BUFSIZE;
}


/**
 *	Returns buffer size using sys calls.
 */
long int bufferSizeSYS(int fd)
{
	long int BUFSIZE = 0;

	//Obtain the size of a file
	BUFSIZE = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);

	return BUFSIZE;
}

/**
 * Coverts a file located with a given path into a string
 * so that the contents can be worked with without the user needing
 * to do extra work using standard I/O.
 */
char* fileToStringSTDIO(const char* path)
{

	char* string = calloc(1, sizeof(char *));
	int ch = 0;
	int index = 0;

	//Determine whether or not the path is a file
	if(isRegularFile(path))
	{
		//Attempt to open file
		FILE* fp = fopen(path, "r");

		//If the file is NULL proceed no further
		if(fp != NULL)
		{
			//Define a string to hold contents of a file
			string = calloc(bufferSize(fp), sizeof(char *));
			while((ch = fgetc(fp)) != EOF)
			{
				if((char) ch != '\n' || (char) ch != '\t' || (char) ch != '\v' || (char) ch != '\f')
				{
					//printf("char %d %c: \n", index, (char) ch);
					string[index] = (char) ch;
					index++;
				}
				else
				{
					string[index] = ' ';
					index++;
				}
			}

		}

		//Close the file
		fclose(fp);

	}
	// Return the file contents as a string.
	return string;
}


char* fileToStringSYSTEM(const char* path)
{
	char* string = calloc(1, sizeof(char *));
	char* ch = calloc(1, sizeof(char *));
	int index = 0;
	int fd;

	//Determine whether or not the path is a file
	if(isRegularFile(path))
	{
		fd = open(path, O_RDONLY);

		//If file descriptor is that of an error, leave.
		if(fd != -1)
		{
			//Define a string to hold contents of a file
			string = calloc(bufferSizeSYS(fd), sizeof(char *));
			while(read(fd, ch, 1) != 0)
			{
				if(ch[0] != '\n' || ch[0] != '\t' || ch[0] != '\v' || ch[0] != '\f')
				{
					string[index] = ch[0];
					index++;
				}
				else
				{
					string[index] = ' ';
					index++;
				}
			}
		}

		//Close the file
		close(fd);
	}

	//Get rid of buffer
	free(ch);

	//Return the file contents as a string
	return string;
}
