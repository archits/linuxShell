Assignment 1 - Part 2
02/02/2015
Author: Archit Sood 

Summary:
The submitted program tries to emulate the UNIX Shell.

Files Submuitted : 
	1. Source Code: my_shell.c
	2. Executable: my_shell
	3. Makefile
	4. README_part2.txt (This file)

Instructions to run:
	1. Unizip the files in desired directory.
	2. Open the terminal and make sure that you are in the same directory as step 1. For example "cd sfuhome/300".
	3. Once in the correct directory, type "make" in terminal. The code should compile now and  terminal should display "	gcc -o my_shell my_shell.c".
	4. After an error free complition, type "make run" in the terminal.
	5. A prompt is displayed. For example "archits_shell$> "
	6. The Shell is ready to be tested.

Supported Features:
	1. Basic command like "ls", "exit", etc. along with multiple arguments.
	2. "cd" can change the directory.
	3. The program puts the process in background when "&" is typed with the command at the end. The status of background process can be checked by typing "jobs" command. The "jobs" is not fully implemented, however it uses a "ps" system call to display the process status and backgrounding job.
	4. Piping is supported.
	5. Error handling.
	6. cntrl-z and cntrl-c is not supported.

Tests:
	1. The program was tested and compiled on several linux machines in CSIL Lab.
	2. Some commands tested:
		i) 	  "ls"
		ii)   "ls -1"
		iii)  "ls | grep a"
		iv)   "firefox www.google.com"
		v)    "sleep 10" 
		vi)   "sleep 10 &"
		vii)  "jobs" (indirectly implements "ps")
		viii) "ls | grep a | grep 1"
		ix)   "exit"
		x)    "cd [dir_name]"
		xi)   "cd .." and then "ls" again.
		xii)  "ls | sort"
		xiii) "&"
		xiv)  " " (Just press Enter on keyboard without typing any command)
		xv)   "blah" (non supported commands)  	