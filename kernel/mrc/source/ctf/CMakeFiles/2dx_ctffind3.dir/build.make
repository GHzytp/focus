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

# Include any dependencies generated for this target.
include kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/depend.make

# Include the progress variables for this target.
include kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/progress.make

# Include the compile flags for this target's objects.
include kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/flags.make

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/flags.make
kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o: /Users/sthennin/Projects/2dx/kernel/mrc/source/ctf/2dx_ctffind3.f
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/sthennin/2dx/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building Fortran object kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o"
	cd /Users/sthennin/2dx/kernel/mrc/source/ctf && /usr/local/bin/gfortran  $(Fortran_DEFINES) $(Fortran_FLAGS) -c /Users/sthennin/Projects/2dx/kernel/mrc/source/ctf/2dx_ctffind3.f -o CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o.requires:
.PHONY : kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o.requires

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o.provides: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o.requires
	$(MAKE) -f kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/build.make kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o.provides.build
.PHONY : kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o.provides

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o.provides.build: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/iof.f.o: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/flags.make
kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/iof.f.o: /Users/sthennin/Projects/2dx/kernel/mrc/source/ctf/iof.f
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/sthennin/2dx/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building Fortran object kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/iof.f.o"
	cd /Users/sthennin/2dx/kernel/mrc/source/ctf && /usr/local/bin/gfortran  $(Fortran_DEFINES) $(Fortran_FLAGS) -c /Users/sthennin/Projects/2dx/kernel/mrc/source/ctf/iof.f -o CMakeFiles/2dx_ctffind3.dir/iof.f.o

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/iof.f.o.requires:
.PHONY : kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/iof.f.o.requires

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/iof.f.o.provides: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/iof.f.o.requires
	$(MAKE) -f kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/build.make kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/iof.f.o.provides.build
.PHONY : kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/iof.f.o.provides

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/iof.f.o.provides.build: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/iof.f.o

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.o: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/flags.make
kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.o: /Users/sthennin/Projects/2dx/kernel/mrc/source/ctf/ioc.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/sthennin/2dx/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.o"
	cd /Users/sthennin/2dx/kernel/mrc/source/ctf && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/2dx_ctffind3.dir/ioc.c.o   -c /Users/sthennin/Projects/2dx/kernel/mrc/source/ctf/ioc.c

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/2dx_ctffind3.dir/ioc.c.i"
	cd /Users/sthennin/2dx/kernel/mrc/source/ctf && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /Users/sthennin/Projects/2dx/kernel/mrc/source/ctf/ioc.c > CMakeFiles/2dx_ctffind3.dir/ioc.c.i

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/2dx_ctffind3.dir/ioc.c.s"
	cd /Users/sthennin/2dx/kernel/mrc/source/ctf && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /Users/sthennin/Projects/2dx/kernel/mrc/source/ctf/ioc.c -o CMakeFiles/2dx_ctffind3.dir/ioc.c.s

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.o.requires:
.PHONY : kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.o.requires

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.o.provides: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.o.requires
	$(MAKE) -f kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/build.make kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.o.provides.build
.PHONY : kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.o.provides

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.o.provides.build: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.o

# Object files for target 2dx_ctffind3
2dx_ctffind3_OBJECTS = \
"CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o" \
"CMakeFiles/2dx_ctffind3.dir/iof.f.o" \
"CMakeFiles/2dx_ctffind3.dir/ioc.c.o"

# External object files for target 2dx_ctffind3
2dx_ctffind3_EXTERNAL_OBJECTS =

kernel/mrc/source/ctf/2dx_ctffind3.exe: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o
kernel/mrc/source/ctf/2dx_ctffind3.exe: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/iof.f.o
kernel/mrc/source/ctf/2dx_ctffind3.exe: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.o
kernel/mrc/source/ctf/2dx_ctffind3.exe: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/build.make
kernel/mrc/source/ctf/2dx_ctffind3.exe: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking Fortran executable 2dx_ctffind3.exe"
	cd /Users/sthennin/2dx/kernel/mrc/source/ctf && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2dx_ctffind3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/build: kernel/mrc/source/ctf/2dx_ctffind3.exe
.PHONY : kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/build

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/requires: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/2dx_ctffind3.f.o.requires
kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/requires: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/iof.f.o.requires
kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/requires: kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/ioc.c.o.requires
.PHONY : kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/requires

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/clean:
	cd /Users/sthennin/2dx/kernel/mrc/source/ctf && $(CMAKE_COMMAND) -P CMakeFiles/2dx_ctffind3.dir/cmake_clean.cmake
.PHONY : kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/clean

kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/depend:
	cd /Users/sthennin/2dx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sthennin/Projects/2dx /Users/sthennin/Projects/2dx/kernel/mrc/source/ctf /Users/sthennin/2dx /Users/sthennin/2dx/kernel/mrc/source/ctf /Users/sthennin/2dx/kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : kernel/mrc/source/ctf/CMakeFiles/2dx_ctffind3.dir/depend

