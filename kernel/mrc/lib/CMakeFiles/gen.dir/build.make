# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = "/Applications/CMake 2.8-7.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.8-7.app/Contents/bin/cmake" -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.8-7.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sthennin/Projects/2dx

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sthennin/2dx

# Utility rule file for gen.

# Include the progress variables for this target.
include kernel/mrc/lib/CMakeFiles/gen.dir/progress.make

kernel/mrc/lib/CMakeFiles/gen: kernel/mrc/lib/unix.for
kernel/mrc/lib/CMakeFiles/gen: kernel/mrc/lib/diskio.for
kernel/mrc/lib/CMakeFiles/gen: kernel/mrc/lib/ccplib.for
kernel/mrc/lib/CMakeFiles/gen: kernel/mrc/lib/subs.for
kernel/mrc/lib/CMakeFiles/gen: kernel/mrc/lib/parser.for
kernel/mrc/lib/CMakeFiles/gen: kernel/mrc/lib/symlib.for
kernel/mrc/lib/CMakeFiles/gen: /Users/sthennin/Projects/2dx/kernel/mrc/lib/library.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/sthennin/2dx/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "compiling libgen.a"
	cd /Users/sthennin/2dx/kernel/mrc/lib && "/Applications/CMake 2.8-7.app/Contents/bin/cmake" -DFSPLIT_OUTFILE=gen_fslpit_files.cmake -DSOURCES_FILE=/Users/sthennin/2dx/kernel/mrc/lib/sources.cmake -DLIB=libgen.a -P /Users/sthennin/Projects/2dx/kernel/mrc/lib/collectFiles.cmake
	cd /Users/sthennin/2dx/kernel/mrc/lib && "/Applications/CMake 2.8-7.app/Contents/bin/cmake" -DFSPLIT_INFILE=gen_fslpit_files.cmake -DFORTRAN_COMPILE_COMMAND=gfortran "-DFORTRAN_FLAGS=-O3 -ffixed-line-length-none -fno-second-underscore -fdollar-ok -ffast-math -w -dead_strip -static-libgcc -I/Users/sthennin/Projects/2dx/kernel/mrc/lib" -P /Users/sthennin/Projects/2dx/kernel/mrc/lib/doPostFortran.cmake
	cd /Users/sthennin/2dx/kernel/mrc/lib && /usr/bin/gcc -DPROTOTYPE -Dalliant -w -ffast-math -c /Users/sthennin/Projects/2dx/kernel/mrc/lib/library.c
	cd /Users/sthennin/2dx/kernel/mrc/lib && "/Applications/CMake 2.8-7.app/Contents/bin/cmake" -DLIB_NAME=gen -P /Users/sthennin/Projects/2dx/kernel/mrc/lib/createLib.cmake

kernel/mrc/lib/unix.for: kernel/mrc/lib/fsplit
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/sthennin/2dx/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating unix.for"
	cd /Users/sthennin/2dx/kernel/mrc/lib && ./fsplit /Users/sthennin/Projects/2dx/kernel/mrc/lib/unix.for

kernel/mrc/lib/diskio.for: kernel/mrc/lib/fsplit
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/sthennin/2dx/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating diskio.for"
	cd /Users/sthennin/2dx/kernel/mrc/lib && ./fsplit /Users/sthennin/Projects/2dx/kernel/mrc/lib/diskio.for

kernel/mrc/lib/ccplib.for: kernel/mrc/lib/fsplit
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/sthennin/2dx/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ccplib.for"
	cd /Users/sthennin/2dx/kernel/mrc/lib && ./fsplit /Users/sthennin/Projects/2dx/kernel/mrc/lib/ccplib.for

kernel/mrc/lib/subs.for: kernel/mrc/lib/fsplit
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/sthennin/2dx/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating subs.for"
	cd /Users/sthennin/2dx/kernel/mrc/lib && ./fsplit /Users/sthennin/Projects/2dx/kernel/mrc/lib/subs.for

kernel/mrc/lib/parser.for: kernel/mrc/lib/fsplit
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/sthennin/2dx/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating parser.for"
	cd /Users/sthennin/2dx/kernel/mrc/lib && ./fsplit /Users/sthennin/Projects/2dx/kernel/mrc/lib/parser.for

kernel/mrc/lib/symlib.for: kernel/mrc/lib/fsplit
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/sthennin/2dx/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating symlib.for"
	cd /Users/sthennin/2dx/kernel/mrc/lib && ./fsplit /Users/sthennin/Projects/2dx/kernel/mrc/lib/symlib.for

gen: kernel/mrc/lib/CMakeFiles/gen
gen: kernel/mrc/lib/unix.for
gen: kernel/mrc/lib/diskio.for
gen: kernel/mrc/lib/ccplib.for
gen: kernel/mrc/lib/subs.for
gen: kernel/mrc/lib/parser.for
gen: kernel/mrc/lib/symlib.for
gen: kernel/mrc/lib/CMakeFiles/gen.dir/build.make
.PHONY : gen

# Rule to build all files generated by this target.
kernel/mrc/lib/CMakeFiles/gen.dir/build: gen
.PHONY : kernel/mrc/lib/CMakeFiles/gen.dir/build

kernel/mrc/lib/CMakeFiles/gen.dir/clean:
	cd /Users/sthennin/2dx/kernel/mrc/lib && $(CMAKE_COMMAND) -P CMakeFiles/gen.dir/cmake_clean.cmake
.PHONY : kernel/mrc/lib/CMakeFiles/gen.dir/clean

kernel/mrc/lib/CMakeFiles/gen.dir/depend:
	cd /Users/sthennin/2dx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sthennin/Projects/2dx /Users/sthennin/Projects/2dx/kernel/mrc/lib /Users/sthennin/2dx /Users/sthennin/2dx/kernel/mrc/lib /Users/sthennin/2dx/kernel/mrc/lib/CMakeFiles/gen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : kernel/mrc/lib/CMakeFiles/gen.dir/depend

