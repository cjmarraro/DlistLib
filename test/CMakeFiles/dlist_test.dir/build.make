# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/myProjects/github/DListLib/DlistLib/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/myProjects/github/DListLib/DlistLib/test

# Include any dependencies generated for this target.
include CMakeFiles/dlist_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dlist_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dlist_test.dir/flags.make

CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o: CMakeFiles/dlist_test.dir/flags.make
CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o: /mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/myProjects/github/DListLib/DlistLib/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o   -c /mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c

CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c > CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.i

CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c -o CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.s

CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o.requires:

.PHONY : CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o.requires

CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o.provides: CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o.requires
	$(MAKE) -f CMakeFiles/dlist_test.dir/build.make CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o.provides.build
.PHONY : CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o.provides

CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o.provides.build: CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o


CMakeFiles/dlist_test.dir/dlist_test.c.o: CMakeFiles/dlist_test.dir/flags.make
CMakeFiles/dlist_test.dir/dlist_test.c.o: dlist_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/myProjects/github/DListLib/DlistLib/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/dlist_test.dir/dlist_test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dlist_test.dir/dlist_test.c.o   -c /mnt/c/myProjects/github/DListLib/DlistLib/test/dlist_test.c

CMakeFiles/dlist_test.dir/dlist_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dlist_test.dir/dlist_test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/myProjects/github/DListLib/DlistLib/test/dlist_test.c > CMakeFiles/dlist_test.dir/dlist_test.c.i

CMakeFiles/dlist_test.dir/dlist_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dlist_test.dir/dlist_test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/myProjects/github/DListLib/DlistLib/test/dlist_test.c -o CMakeFiles/dlist_test.dir/dlist_test.c.s

CMakeFiles/dlist_test.dir/dlist_test.c.o.requires:

.PHONY : CMakeFiles/dlist_test.dir/dlist_test.c.o.requires

CMakeFiles/dlist_test.dir/dlist_test.c.o.provides: CMakeFiles/dlist_test.dir/dlist_test.c.o.requires
	$(MAKE) -f CMakeFiles/dlist_test.dir/build.make CMakeFiles/dlist_test.dir/dlist_test.c.o.provides.build
.PHONY : CMakeFiles/dlist_test.dir/dlist_test.c.o.provides

CMakeFiles/dlist_test.dir/dlist_test.c.o.provides.build: CMakeFiles/dlist_test.dir/dlist_test.c.o


# Object files for target dlist_test
dlist_test_OBJECTS = \
"CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o" \
"CMakeFiles/dlist_test.dir/dlist_test.c.o"

# External object files for target dlist_test
dlist_test_EXTERNAL_OBJECTS =

dlist_test: CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o
dlist_test: CMakeFiles/dlist_test.dir/dlist_test.c.o
dlist_test: CMakeFiles/dlist_test.dir/build.make
dlist_test: CMakeFiles/dlist_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/myProjects/github/DListLib/DlistLib/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable dlist_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dlist_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dlist_test.dir/build: dlist_test

.PHONY : CMakeFiles/dlist_test.dir/build

CMakeFiles/dlist_test.dir/requires: CMakeFiles/dlist_test.dir/mnt/c/myProjects/github/DListLib/DlistLib/src/dlist.c.o.requires
CMakeFiles/dlist_test.dir/requires: CMakeFiles/dlist_test.dir/dlist_test.c.o.requires

.PHONY : CMakeFiles/dlist_test.dir/requires

CMakeFiles/dlist_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dlist_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dlist_test.dir/clean

CMakeFiles/dlist_test.dir/depend:
	cd /mnt/c/myProjects/github/DListLib/DlistLib/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/myProjects/github/DListLib/DlistLib/test /mnt/c/myProjects/github/DListLib/DlistLib/test /mnt/c/myProjects/github/DListLib/DlistLib/test /mnt/c/myProjects/github/DListLib/DlistLib/test /mnt/c/myProjects/github/DListLib/DlistLib/test/CMakeFiles/dlist_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dlist_test.dir/depend
