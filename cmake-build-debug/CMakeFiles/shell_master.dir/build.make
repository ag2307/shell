# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hs/Documents/Projects/shell-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hs/Documents/Projects/shell-master/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/shell_master.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/shell_master.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shell_master.dir/flags.make

CMakeFiles/shell_master.dir/shell.c.o: CMakeFiles/shell_master.dir/flags.make
CMakeFiles/shell_master.dir/shell.c.o: ../shell.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hs/Documents/Projects/shell-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/shell_master.dir/shell.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell_master.dir/shell.c.o   -c /Users/hs/Documents/Projects/shell-master/shell.c

CMakeFiles/shell_master.dir/shell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell_master.dir/shell.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/hs/Documents/Projects/shell-master/shell.c > CMakeFiles/shell_master.dir/shell.c.i

CMakeFiles/shell_master.dir/shell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell_master.dir/shell.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/hs/Documents/Projects/shell-master/shell.c -o CMakeFiles/shell_master.dir/shell.c.s

CMakeFiles/shell_master.dir/shell.c.o.requires:

.PHONY : CMakeFiles/shell_master.dir/shell.c.o.requires

CMakeFiles/shell_master.dir/shell.c.o.provides: CMakeFiles/shell_master.dir/shell.c.o.requires
	$(MAKE) -f CMakeFiles/shell_master.dir/build.make CMakeFiles/shell_master.dir/shell.c.o.provides.build
.PHONY : CMakeFiles/shell_master.dir/shell.c.o.provides

CMakeFiles/shell_master.dir/shell.c.o.provides.build: CMakeFiles/shell_master.dir/shell.c.o


# Object files for target shell_master
shell_master_OBJECTS = \
"CMakeFiles/shell_master.dir/shell.c.o"

# External object files for target shell_master
shell_master_EXTERNAL_OBJECTS =

shell_master: CMakeFiles/shell_master.dir/shell.c.o
shell_master: CMakeFiles/shell_master.dir/build.make
shell_master: CMakeFiles/shell_master.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hs/Documents/Projects/shell-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable shell_master"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shell_master.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shell_master.dir/build: shell_master

.PHONY : CMakeFiles/shell_master.dir/build

CMakeFiles/shell_master.dir/requires: CMakeFiles/shell_master.dir/shell.c.o.requires

.PHONY : CMakeFiles/shell_master.dir/requires

CMakeFiles/shell_master.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shell_master.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shell_master.dir/clean

CMakeFiles/shell_master.dir/depend:
	cd /Users/hs/Documents/Projects/shell-master/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hs/Documents/Projects/shell-master /Users/hs/Documents/Projects/shell-master /Users/hs/Documents/Projects/shell-master/cmake-build-debug /Users/hs/Documents/Projects/shell-master/cmake-build-debug /Users/hs/Documents/Projects/shell-master/cmake-build-debug/CMakeFiles/shell_master.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shell_master.dir/depend

