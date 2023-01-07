# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /home/kacper/aplikacje/clion-2020.3.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/kacper/aplikacje/clion-2020.3.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kacper/Pulpit/zpr_eps

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kacper/Pulpit/zpr_eps/cmake-build-debug-coverage

# Include any dependencies generated for this target.
include tests/CMakeFiles/EPSFileToolsTest.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/EPSFileToolsTest.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/EPSFileToolsTest.dir/flags.make

tests/CMakeFiles/EPSFileToolsTest.dir/EPSFileToolsTest.cc.o: tests/CMakeFiles/EPSFileToolsTest.dir/flags.make
tests/CMakeFiles/EPSFileToolsTest.dir/EPSFileToolsTest.cc.o: ../tests/EPSFileToolsTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kacper/Pulpit/zpr_eps/cmake-build-debug-coverage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/EPSFileToolsTest.dir/EPSFileToolsTest.cc.o"
	cd /home/kacper/Pulpit/zpr_eps/cmake-build-debug-coverage/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EPSFileToolsTest.dir/EPSFileToolsTest.cc.o -c /home/kacper/Pulpit/zpr_eps/tests/EPSFileToolsTest.cc

tests/CMakeFiles/EPSFileToolsTest.dir/EPSFileToolsTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EPSFileToolsTest.dir/EPSFileToolsTest.cc.i"
	cd /home/kacper/Pulpit/zpr_eps/cmake-build-debug-coverage/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kacper/Pulpit/zpr_eps/tests/EPSFileToolsTest.cc > CMakeFiles/EPSFileToolsTest.dir/EPSFileToolsTest.cc.i

tests/CMakeFiles/EPSFileToolsTest.dir/EPSFileToolsTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EPSFileToolsTest.dir/EPSFileToolsTest.cc.s"
	cd /home/kacper/Pulpit/zpr_eps/cmake-build-debug-coverage/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kacper/Pulpit/zpr_eps/tests/EPSFileToolsTest.cc -o CMakeFiles/EPSFileToolsTest.dir/EPSFileToolsTest.cc.s

# Object files for target EPSFileToolsTest
EPSFileToolsTest_OBJECTS = \
"CMakeFiles/EPSFileToolsTest.dir/EPSFileToolsTest.cc.o"

# External object files for target EPSFileToolsTest
EPSFileToolsTest_EXTERNAL_OBJECTS =

tests/EPSFileToolsTest: tests/CMakeFiles/EPSFileToolsTest.dir/EPSFileToolsTest.cc.o
tests/EPSFileToolsTest: tests/CMakeFiles/EPSFileToolsTest.dir/build.make
tests/EPSFileToolsTest: src/libEPSFileTools.a
tests/EPSFileToolsTest: src/libScalar2DRepresentation.a
tests/EPSFileToolsTest: src/libEPSCommands.a
tests/EPSFileToolsTest: lib/libgtest_maind.a
tests/EPSFileToolsTest: lib/libgtestd.a
tests/EPSFileToolsTest: tests/CMakeFiles/EPSFileToolsTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kacper/Pulpit/zpr_eps/cmake-build-debug-coverage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable EPSFileToolsTest"
	cd /home/kacper/Pulpit/zpr_eps/cmake-build-debug-coverage/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EPSFileToolsTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/EPSFileToolsTest.dir/build: tests/EPSFileToolsTest

.PHONY : tests/CMakeFiles/EPSFileToolsTest.dir/build

tests/CMakeFiles/EPSFileToolsTest.dir/clean:
	cd /home/kacper/Pulpit/zpr_eps/cmake-build-debug-coverage/tests && $(CMAKE_COMMAND) -P CMakeFiles/EPSFileToolsTest.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/EPSFileToolsTest.dir/clean

tests/CMakeFiles/EPSFileToolsTest.dir/depend:
	cd /home/kacper/Pulpit/zpr_eps/cmake-build-debug-coverage && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kacper/Pulpit/zpr_eps /home/kacper/Pulpit/zpr_eps/tests /home/kacper/Pulpit/zpr_eps/cmake-build-debug-coverage /home/kacper/Pulpit/zpr_eps/cmake-build-debug-coverage/tests /home/kacper/Pulpit/zpr_eps/cmake-build-debug-coverage/tests/CMakeFiles/EPSFileToolsTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/EPSFileToolsTest.dir/depend

