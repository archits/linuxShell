####02/02/2015
####Author: Archit Sood 

##Summary:
The program tries to emulate the UNIX Shell.

##Files: 
	1. Source Code: my_shell.c
	3. Makefile
	4. README.txt 

##Instructions to run:
	1. Unizip the files in desired directory.
	2. Open the terminal and make sure that you are in the same directory as step 1. For example "cd home/myshell".
	3. Once in the correct directory, type "make" in terminal. The code should compile now and  terminal should display "	gcc -o my_shell my_shell.c".
	4. After an error free complition, type "make run" in the terminal.
	5. A prompt is displayed. For example "archits_shell$> "
	6. The Shell is ready to be tested.

##Supported Features:
	1. Basic command like "ls", "exit", etc. along with multiple arguments.
	2. "cd" can change the directory.
	3. The program puts the process in background when "&" is typed with the command at the end. The status of background process can be checked by typing "jobs" command. The "jobs" is not fully implemented, however it uses a "ps" system call to display the process status and backgrounding job.
	4. Piping is supported.
	5. Error handling.
	6. cntrl-z and cntrl-c is not supported.

##Tests:
	1. The program was tested and compiled on several linux machines.
	2. Some commands tested:
		*	"ls"
		*	"ls -1"
		*	"ls | grep a"
		*	"firefox www.google.com"
		*	"sleep 10" 
		*	"sleep 10 &"
		*	"jobs" (indirectly implements "ps")
		*	"ls | grep a | grep 1"
		*	"exit"
		*	"cd [dir_name]"
		*	"cd .." and then "ls" again.
		*	"ls | sort"
		*	"&"
		*	" " (Just press Enter on keyboard without typing any command)
		*	"blah" (non supported commands)  	
