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
include kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/depend.make

# Include the progress variables for this target.
include kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/progress.make

# Include the compile flags for this target's objects.
include kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/flags.make

kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o: kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/flags.make
kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o: /Users/sthennin/Projects/2dx/kernel/mrc/source/2dx_getdirectories.for
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/sthennin/2dx/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building Fortran object kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o"
	cd /Users/sthennin/2dx/kernel/mrc/source && /usr/local/bin/gfortran  $(Fortran_DEFINES) $(Fortran_FLAGS) -c /Users/sthennin/Projects/2dx/kernel/mrc/source/2dx_getdirectories.for -o CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o

kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o.requires:
.PHONY : kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o.requires

kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o.provides: kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o.requires
	$(MAKE) -f kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/build.make kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o.provides.build
.PHONY : kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o.provides

kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o.provides.build: kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o

# Object files for target 2dx_getdirectories
2dx_getdirectories_OBJECTS = \
"CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o"

# External object files for target 2dx_getdirectories
2dx_getdirectories_EXTERNAL_OBJECTS =

kernel/mrc/source/2dx_getdirectories.exe: kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o
kernel/mrc/source/2dx_getdirectories.exe: kernel/mrc/source/../lib/lib2dx.a
kernel/mrc/source/2dx_getdirectories.exe: kernel/mrc/source/../lib/libim2k.a
kernel/mrc/source/2dx_getdirectories.exe: kernel/mrc/source/../lib/libmisc.a
kernel/mrc/source/2dx_getdirectories.exe: kernel/mrc/source/../lib/libgen.a
kernel/mrc/source/2dx_getdirectories.exe: kernel/mrc/source/../lib/libplot2k.a
kernel/mrc/source/2dx_getdirectories.exe: kernel/mrc/source/../lib/libfft.a
kernel/mrc/source/2dx_getdirectories.exe: kernel/mrc/source/../lib/libconv.a
kernel/mrc/source/2dx_getdirectories.exe: /usr/local/lib/libstdc++.a
kernel/mrc/source/2dx_getdirectories.exe: /usr/local/lib/libfftw3f.dylib
kernel/mrc/source/2dx_getdirectories.exe: kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/build.make
kernel/mrc/source/2dx_getdirectories.exe: kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking Fortran executable 2dx_getdirectories.exe"
	cd /Users/sthennin/2dx/kernel/mrc/source && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2dx_getdirectories.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/build: kernel/mrc/source/2dx_getdirectories.exe
.PHONY : kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/build

kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/requires: kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/2dx_getdirectories.for.o.requires
.PHONY : kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/requires

kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/clean:
	cd /Users/sthennin/2dx/kernel/mrc/source && $(CMAKE_COMMAND) -P CMakeFiles/2dx_getdirectories.dir/cmake_clean.cmake
.PHONY : kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/clean

kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/depend:
	cd /Users/sthennin/2dx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sthennin/Projects/2dx /Users/sthennin/Projects/2dx/kernel/mrc/source /Users/sthennin/2dx /Users/sthennin/2dx/kernel/mrc/source /Users/sthennin/2dx/kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : kernel/mrc/source/CMakeFiles/2dx_getdirectories.dir/depend

