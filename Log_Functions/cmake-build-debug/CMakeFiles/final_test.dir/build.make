# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.3.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.3.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\212410438\CLionProjects\Log_Functions

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\212410438\CLionProjects\Log_Functions\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/final_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/final_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/final_test.dir/flags.make

CMakeFiles/final_test.dir/main.cpp.obj: CMakeFiles/final_test.dir/flags.make
CMakeFiles/final_test.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\212410438\CLionProjects\Log_Functions\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/final_test.dir/main.cpp.obj"
	C:\Users\212410438\Documents\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\final_test.dir\main.cpp.obj -c C:\Users\212410438\CLionProjects\Log_Functions\main.cpp

CMakeFiles/final_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final_test.dir/main.cpp.i"
	C:\Users\212410438\Documents\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\212410438\CLionProjects\Log_Functions\main.cpp > CMakeFiles\final_test.dir\main.cpp.i

CMakeFiles/final_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final_test.dir/main.cpp.s"
	C:\Users\212410438\Documents\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\212410438\CLionProjects\Log_Functions\main.cpp -o CMakeFiles\final_test.dir\main.cpp.s

CMakeFiles/final_test.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/final_test.dir/main.cpp.obj.requires

CMakeFiles/final_test.dir/main.cpp.obj.provides: CMakeFiles/final_test.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\final_test.dir\build.make CMakeFiles/final_test.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/final_test.dir/main.cpp.obj.provides

CMakeFiles/final_test.dir/main.cpp.obj.provides.build: CMakeFiles/final_test.dir/main.cpp.obj


# Object files for target final_test
final_test_OBJECTS = \
"CMakeFiles/final_test.dir/main.cpp.obj"

# External object files for target final_test
final_test_EXTERNAL_OBJECTS =

final_test.exe: CMakeFiles/final_test.dir/main.cpp.obj
final_test.exe: CMakeFiles/final_test.dir/build.make
final_test.exe: CMakeFiles/final_test.dir/linklibs.rsp
final_test.exe: CMakeFiles/final_test.dir/objects1.rsp
final_test.exe: CMakeFiles/final_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\212410438\CLionProjects\Log_Functions\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable final_test.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\final_test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/final_test.dir/build: final_test.exe

.PHONY : CMakeFiles/final_test.dir/build

CMakeFiles/final_test.dir/requires: CMakeFiles/final_test.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/final_test.dir/requires

CMakeFiles/final_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\final_test.dir\cmake_clean.cmake
.PHONY : CMakeFiles/final_test.dir/clean

CMakeFiles/final_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\212410438\CLionProjects\Log_Functions C:\Users\212410438\CLionProjects\Log_Functions C:\Users\212410438\CLionProjects\Log_Functions\cmake-build-debug C:\Users\212410438\CLionProjects\Log_Functions\cmake-build-debug C:\Users\212410438\CLionProjects\Log_Functions\cmake-build-debug\CMakeFiles\final_test.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/final_test.dir/depend

