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
include kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/depend.make

# Include the progress variables for this target.
include kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/progress.make

# Include the compile flags for this target's objects.
include kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/flags.make

kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o: kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/flags.make
kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o: /Users/sthennin/Projects/2dx/kernel/mrc/source/2dx_getlat/2dx_getlat.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/sthennin/2dx/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o"
	cd /Users/sthennin/2dx/kernel/mrc/source/2dx_getlat && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o -c /Users/sthennin/Projects/2dx/kernel/mrc/source/2dx_getlat/2dx_getlat.cpp

kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.i"
	cd /Users/sthennin/2dx/kernel/mrc/source/2dx_getlat && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/sthennin/Projects/2dx/kernel/mrc/source/2dx_getlat/2dx_getlat.cpp > CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.i

kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.s"
	cd /Users/sthennin/2dx/kernel/mrc/source/2dx_getlat && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/sthennin/Projects/2dx/kernel/mrc/source/2dx_getlat/2dx_getlat.cpp -o CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.s

kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o.requires:
.PHONY : kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o.requires

kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o.provides: kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o.requires
	$(MAKE) -f kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/build.make kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o.provides.build
.PHONY : kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o.provides

kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o.provides.build: kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o

# Object files for target 2dx_getlat
2dx_getlat_OBJECTS = \
"CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o"

# External object files for target 2dx_getlat
2dx_getlat_EXTERNAL_OBJECTS =

kernel/mrc/source/2dx_getlat/2dx_getlat.exe: kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o
kernel/mrc/source/2dx_getlat/2dx_getlat.exe: kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/build.make
kernel/mrc/source/2dx_getlat/2dx_getlat.exe: kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable 2dx_getlat.exe"
	cd /Users/sthennin/2dx/kernel/mrc/source/2dx_getlat && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2dx_getlat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/build: kernel/mrc/source/2dx_getlat/2dx_getlat.exe
.PHONY : kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/build

kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/requires: kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/2dx_getlat.cpp.o.requires
.PHONY : kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/requires

kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/clean:
	cd /Users/sthennin/2dx/kernel/mrc/source/2dx_getlat && $(CMAKE_COMMAND) -P CMakeFiles/2dx_getlat.dir/cmake_clean.cmake
.PHONY : kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/clean

kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/depend:
	cd /Users/sthennin/2dx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sthennin/Projects/2dx /Users/sthennin/Projects/2dx/kernel/mrc/source/2dx_getlat /Users/sthennin/2dx /Users/sthennin/2dx/kernel/mrc/source/2dx_getlat /Users/sthennin/2dx/kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : kernel/mrc/source/2dx_getlat/CMakeFiles/2dx_getlat.dir/depend

