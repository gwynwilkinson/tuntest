# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /home/gwyn/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.5429.37/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/gwyn/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.5429.37/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gwyn/dev/vpntest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gwyn/dev/vpntest/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/vpntest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/vpntest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vpntest.dir/flags.make

CMakeFiles/vpntest.dir/main.c.o: CMakeFiles/vpntest.dir/flags.make
CMakeFiles/vpntest.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gwyn/dev/vpntest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/vpntest.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/vpntest.dir/main.c.o   -c /home/gwyn/dev/vpntest/main.c

CMakeFiles/vpntest.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vpntest.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gwyn/dev/vpntest/main.c > CMakeFiles/vpntest.dir/main.c.i

CMakeFiles/vpntest.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vpntest.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gwyn/dev/vpntest/main.c -o CMakeFiles/vpntest.dir/main.c.s

# Object files for target vpntest
vpntest_OBJECTS = \
"CMakeFiles/vpntest.dir/main.c.o"

# External object files for target vpntest
vpntest_EXTERNAL_OBJECTS =

vpntest: CMakeFiles/vpntest.dir/main.c.o
vpntest: CMakeFiles/vpntest.dir/build.make
vpntest: CMakeFiles/vpntest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gwyn/dev/vpntest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable vpntest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vpntest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vpntest.dir/build: vpntest

.PHONY : CMakeFiles/vpntest.dir/build

CMakeFiles/vpntest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vpntest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vpntest.dir/clean

CMakeFiles/vpntest.dir/depend:
	cd /home/gwyn/dev/vpntest/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gwyn/dev/vpntest /home/gwyn/dev/vpntest /home/gwyn/dev/vpntest/cmake-build-debug /home/gwyn/dev/vpntest/cmake-build-debug /home/gwyn/dev/vpntest/cmake-build-debug/CMakeFiles/vpntest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vpntest.dir/depend

