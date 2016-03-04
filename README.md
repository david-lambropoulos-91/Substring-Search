This application requires at least two arguments. The second argument specifies the file in which you will be finding sub-strings. The third and remaining arguments are sub-strings that are to be searched for in the file specified by the second argument.

In our problem, "sub-strings" are not necessarily separated by whitespace; that's why we're calling them "substrings" instead of "words".

An additional command line argument (-s) can be provided that will switch over to a system call implementation of the program whereas without the flag the program will run on standard I/O.

Runtime differences are provided in runtime.txt.



Examples:

	Run 1:

		% echo "abcdefgh" > bar
		% ./p1
		bar bc
		1
		%

	Run 2:

		% echo "aaab" > bar
		% ./p1
		bar aa B
		2
		1
		%

	Run 3:

		% echo "abcdefgh" > bar
		% ./p1 -s bar bc
		1


In order to run the test script, create a tarball username-p1.tar.gz.

Conditions:
	
	1) Executable must be named p1
	
	2) The tarball must contain either a makefile or a configure command to generate a makefile
	
	3) The source code must be in a file named p1.c

Finally just run the following command to execute the test script,

	% ./test-p1.sh username-p1.tar.gz
