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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/smirza/senior-project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/smirza/senior-project

# Include any dependencies generated for this target.
include glfw/tests/CMakeFiles/tearing.dir/depend.make

# Include the progress variables for this target.
include glfw/tests/CMakeFiles/tearing.dir/progress.make

# Include the compile flags for this target's objects.
include glfw/tests/CMakeFiles/tearing.dir/flags.make

glfw/tests/CMakeFiles/tearing.dir/tearing.c.o: glfw/tests/CMakeFiles/tearing.dir/flags.make
glfw/tests/CMakeFiles/tearing.dir/tearing.c.o: glfw/tests/tearing.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/smirza/senior-project/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object glfw/tests/CMakeFiles/tearing.dir/tearing.c.o"
	cd /home/smirza/senior-project/glfw/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/tearing.dir/tearing.c.o   -c /home/smirza/senior-project/glfw/tests/tearing.c

glfw/tests/CMakeFiles/tearing.dir/tearing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tearing.dir/tearing.c.i"
	cd /home/smirza/senior-project/glfw/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/smirza/senior-project/glfw/tests/tearing.c > CMakeFiles/tearing.dir/tearing.c.i

glfw/tests/CMakeFiles/tearing.dir/tearing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tearing.dir/tearing.c.s"
	cd /home/smirza/senior-project/glfw/tests && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/smirza/senior-project/glfw/tests/tearing.c -o CMakeFiles/tearing.dir/tearing.c.s

glfw/tests/CMakeFiles/tearing.dir/tearing.c.o.requires:
.PHONY : glfw/tests/CMakeFiles/tearing.dir/tearing.c.o.requires

glfw/tests/CMakeFiles/tearing.dir/tearing.c.o.provides: glfw/tests/CMakeFiles/tearing.dir/tearing.c.o.requires
	$(MAKE) -f glfw/tests/CMakeFiles/tearing.dir/build.make glfw/tests/CMakeFiles/tearing.dir/tearing.c.o.provides.build
.PHONY : glfw/tests/CMakeFiles/tearing.dir/tearing.c.o.provides

glfw/tests/CMakeFiles/tearing.dir/tearing.c.o.provides.build: glfw/tests/CMakeFiles/tearing.dir/tearing.c.o

# Object files for target tearing
tearing_OBJECTS = \
"CMakeFiles/tearing.dir/tearing.c.o"

# External object files for target tearing
tearing_EXTERNAL_OBJECTS =

glfw/tests/tearing: glfw/tests/CMakeFiles/tearing.dir/tearing.c.o
glfw/tests/tearing: glfw/tests/CMakeFiles/tearing.dir/build.make
glfw/tests/tearing: glfw/src/libglfw3.a
glfw/tests/tearing: /usr/lib64/libX11.so
glfw/tests/tearing: /usr/lib64/librt.so
glfw/tests/tearing: /usr/lib64/libXrandr.so
glfw/tests/tearing: /usr/lib64/libXinerama.so
glfw/tests/tearing: /usr/lib64/libXi.so
glfw/tests/tearing: /usr/lib64/libXxf86vm.so
glfw/tests/tearing: /usr/lib64/librt.so
glfw/tests/tearing: /usr/lib64/libm.so
glfw/tests/tearing: /usr/lib64/libXcursor.so
glfw/tests/tearing: /usr/lib64/libGL.so
glfw/tests/tearing: /usr/lib64/libXrandr.so
glfw/tests/tearing: /usr/lib64/libXinerama.so
glfw/tests/tearing: /usr/lib64/libXi.so
glfw/tests/tearing: /usr/lib64/libXxf86vm.so
glfw/tests/tearing: /usr/lib64/libm.so
glfw/tests/tearing: /usr/lib64/libXcursor.so
glfw/tests/tearing: /usr/lib64/libGL.so
glfw/tests/tearing: glfw/tests/CMakeFiles/tearing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable tearing"
	cd /home/smirza/senior-project/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tearing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glfw/tests/CMakeFiles/tearing.dir/build: glfw/tests/tearing
.PHONY : glfw/tests/CMakeFiles/tearing.dir/build

glfw/tests/CMakeFiles/tearing.dir/requires: glfw/tests/CMakeFiles/tearing.dir/tearing.c.o.requires
.PHONY : glfw/tests/CMakeFiles/tearing.dir/requires

glfw/tests/CMakeFiles/tearing.dir/clean:
	cd /home/smirza/senior-project/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/tearing.dir/cmake_clean.cmake
.PHONY : glfw/tests/CMakeFiles/tearing.dir/clean

glfw/tests/CMakeFiles/tearing.dir/depend:
	cd /home/smirza/senior-project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/smirza/senior-project /home/smirza/senior-project/glfw/tests /home/smirza/senior-project /home/smirza/senior-project/glfw/tests /home/smirza/senior-project/glfw/tests/CMakeFiles/tearing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glfw/tests/CMakeFiles/tearing.dir/depend

