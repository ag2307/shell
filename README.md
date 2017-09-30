# shell
Shell implemented in C language
==============

Team Members:\
    1) **Abhinav Gupta**:\
    2) **Manas Daruka**:\
    3) **Hiten Sethiya**:

Files:\
	1) `shell.c`  - main file with full shell code with signal handling, etc.\
	2) `util.h`   - supporting header file containing declaration of certain functions and variables\
	3) `Makefile` - Compilation code\
	4) `README`   - Documentation\

Features
==============

* Basic commands: `pwd`, `clear`,`ls` and `cd`

* `ls` command shows all filed in the current directory (hidden also)

* Program invocation with forking and child processes

* Exit shell using `exit` commmand or `Ctrl + c` SIGINT signal

* `history n` command to print last `n` commands or all of the previous commands if no second argument 

* I/O redirection (use of `dup2` system call) limited to the following:  
        `<cmd> <args> > <output>`  
        `<cmd> <args> < <input> > <output>`

* `<program_name` to execute <program_name> and this supports `<` and `>` redirection
