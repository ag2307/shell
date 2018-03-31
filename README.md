# shell
Shell implemented in C language
==============
**Recent Update** : All parts works great but limited time execution(FileIO_Limited) i.e. `<program_name> m` has issues with it. In the implementation, the output from program is firstly transferred to a file named std_output.txt and then read from there to the console which takes a larger amount of time then the time specified in the terminal as an argument. Reason behind that is 'EXTRA WRITE TIME' in writing to the file std_output.txt.

*This issue can be solved very easily by not calling dup2() for output to file in FileIO_Limited. Any help in correcting the code will be appreciated.*   

Team Members:
1) **Abhinav Gupta**: Implementation of `cd`,`ls`,`history`,`issue`,`<program_name>` and `exit` commands.
    
2) **Manas Daruka** : Implementation of `<program_name> m` command and thorough debugging of full program.

3) **Hiten Sethiya**: Implementation of `rm` and `rmexcept` commands with all their options.

Files:
1) `shell.c`  - main file with full shell code with signal handling, etc.
2) `util.h`   - supporting header file containing declaration of certain functions and variables
3) `Makefile` - Compilation code
4) `README`   - Documentation

Features
==============

* Basic commands: `pwd`, `clear`,`ls` and `cd`

* `ls` command shows all filed in the current directory (hidden also)

* `rm` command working with `-r` , `-f` and `-v` options. 
* `rmexcept file1 ...` command removes all files except files specified with the command.
* `issue n` command runs the `n`th latest command in history. 

* Program invocation with forking and child processes

* Exit shell using `exit` commmand or `Ctrl + c` SIGINT signal

* `history n` command to print last `n` commands or all of the previous commands if no second argument 

* I/O redirection (use of `dup2` system call) limited to the following:  
        `<cmd> <args> > <output>`  
        `<cmd> <args> < <input> > <output>`
  this means that when `input` redirection is there there should be an output redirection as well

* `<program_name>` to execute <program_name> and this supports `<` and `>` redirection
* `<program_name> m` command terminates process after `m` seconds of time consumption or earlier if program terminates   earlier.
