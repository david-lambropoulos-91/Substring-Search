#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fileManager.h"

int main(int argc, char** argv)
{
	int numOccurrences = 0;	//Number of times a given word matched as a substring
	int argLength;	//Length of the argument
	int curr = 1;	//Current position in argv
	int isSet = 0;	//Holds whether or not the flag is set
	int position = 0;	//Position in the string
	int length = 0;	//length of the file
	int boundaryPoint;	//Where to stop looking
	int temp;	//arbitrary variable used for counting
	char* buff;	//Buffer for storing data
	char* fileString;	//String to hold the file contents
	//clock_t start, end;

	//Get Initial time
	//start = clock();

	//THE WALL OF CHECKS
	//No argument provided check.
	if(argc == 1)
	{
		fprintf(stderr, "%s: No arguments provided\n", argv[0]);
		return 0;
	}


	//Check if the flag was presented with too few arguments
	if(argc == 2 && strcmp("-s", argv[curr]) == 0)
	{
		fprintf(stderr, "%s: No file or arguments provided\n", argv[0]);
		return 0;
	}
	else if(strcmp("-s", argv[curr]) == 0)
	{
		isSet = 1;
	}

	if(argc == 2 && isSet == 0)
	{
		fprintf(stderr, "%s: No arguments provided\n", argv[0]);
		return 0;
	}

	if(isSet == 1)
	{
		//File name provided, check for existence
		if(Exists(argv[curr + 1]) == 0)
		{
			fprintf(stderr, "%s: No such file or directory\n", argv[0]);
			return 0;
		}
	}
	else
	{
		//File name provided, check for existence
		if(Exists(argv[curr]) == 0)
		{
			fprintf(stderr, "%s: No such file or directory\n", argv[0]);
			return 0;
		}
	}

	//Check if any argument were provided
	if(argc == 3 && isSet == 1)
	{
		fprintf(stderr, "%s: You must enter something to be found\n", argv[0]);
		return 0;
	}


	//Adjust position based on flag argument
	if(isSet == 0)
	{
		//Read file using standard I/O
		fileString = fileToStringSTDIO(argv[curr]);

		//See if file was empty, if so leave
		if(strlen(fileString) == 0)
		{
			fprintf(stderr, "File is empty, no appropriate actions can be taken!\n");
			return 0;
		}

		//See if file was too big



		curr++;
	}
	else
	{
		//Read file using system calls
		fileString = fileToStringSYSTEM(argv[curr + 1]);

		//See if file was empty, if so leave
		if(strlen(fileString) == 0)
		{
			fprintf(stderr, "File is empty, no appropriate actions can be taken!\n");
			return 0;
		}

		//See if file is too big



		curr = curr + 2;
	}

	//Get the length of
	length = strlen(fileString) - 1;


	//Grab each argument one at a time
	while(curr < argc)
	{
		argLength = strlen(argv[curr]);
		boundaryPoint = length - argLength;

		//fprintf(stderr, "length = %d\nargLength = %d\nboundaryPoint = %d\n", length, argLength, boundaryPoint);

		//If argument is longer than content of file, it can't be in file
		if(argLength > length)
		{
			//Print result
			fprintf(stderr, "0\n");

			//Reset all values and increment position
			curr++;
			numOccurrences = 0;
			position = 0;
			continue;
		}

		//Create the buffer
		buff = calloc(0,argLength*sizeof(char));

		//Walk through the file looking for all possible occurrences
		while(position <= boundaryPoint)
		{
			//Grab next substring
			for(temp = 0; temp < argLength; temp++)
			{
				buff[temp] = fileString[position+temp];
			}

			//fprintf(stderr, "buff = %s\nargv[%d] = %s", buff, curr, argv[curr]);
			//Compare substring and increment numOccurrence respectively
			if(strcmp(buff, argv[curr]) == 0)
			{
				numOccurrences++;
			}

			position++;
		}

		//Print result
		fprintf(stdout, "%d\n", numOccurrences);

		//Reset all values and increment position
		free(buff);
		curr++;
		numOccurrences = 0;
		position = 0;
	}

	//Get ending time
	//end = clock();

	//Calculate and display execution time
	//printf("Execution time: %fs\n", (double) (end-start)/CLOCKS_PER_SEC);


	return 0;
}
