Shell implemented in C language

==============

**Compiling and Running the shell**: :boom::boom:

Go to folder containing all the files and then run following commands to compile and run the shell.

```
make
./shell
```

==============

**Features**: :clipboard::clipboard:

* Basic commands allowed: `pwd`, `clear`, `ls` , `cd`, `<program_name>` and `<program_name> m`

* `ls` command shows all filed in the current directory (non-hidden only)

* `rm` command working with `-r` , `-f` and `-v` options. 

* `rmexcept file1 ...` command removes all files except files specified with the command.

* `issue n` command runs the `n`th latest command in history. 

* Program invocation with forking and child processes

* Exit shell using `exit` commmand or `Ctrl + c` SIGINT signal

* `history n` command to print last `n` commands or all of the previous commands if no second argument 

* I/O redirection (use of `dup2` system call) limited to the following:

	* `	<command> < <input> `
    * ` <command> > <output> `
    * ` <command> < <input> > <output> `

  Space between operators is important for correct functioning.

* `<program_name>` to execute <program_name> and this supports `<` and `>` redirection.

		Ex: ./in-out < input.txt > output.txt 

* `<program_name> m` command terminates process after `m` seconds of time consumption or earlier (if program terminates).

		Ex: ./infinite 1

==============

**Team Members**: :beers::beers:

* **Abhinav Gupta** - Implementation of `cd`,`ls`,`history`,`issue`,`<program_name>`,`<program_name> m` and `exit` commands.

* **Hiten Sethiya** - Implementation of `rm` and `rmexcept` commands with all their options.
    
* **Manas Daruka** - Thorough debugging of full program.

==============

**Files**: :file_folder::file_folder:

* `shell.c`  - main file with full shell code with signal handling, etc.
* `util.h`   - supporting header file containing declaration of certain functions and variables
* `in-out.c` and `infinite.c` - code for testing
* `in-out`, `infinite` and `shell` - executable files
* `input.txt` and `output.txt` - sample files for input and output redirection
* `Makefile` - Compilation code
* `README`   - Documentation
