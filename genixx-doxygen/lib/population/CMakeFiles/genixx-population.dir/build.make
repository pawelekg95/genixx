# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gmurczykpa/Documents/genixx/genixx

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen

# Include any dependencies generated for this target.
include lib/population/CMakeFiles/genixx-population.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/population/CMakeFiles/genixx-population.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/population/CMakeFiles/genixx-population.dir/progress.make

# Include the compile flags for this target's objects.
include lib/population/CMakeFiles/genixx-population.dir/flags.make

lib/population/CMakeFiles/genixx-population.dir/Individual.cpp.o: lib/population/CMakeFiles/genixx-population.dir/flags.make
lib/population/CMakeFiles/genixx-population.dir/Individual.cpp.o: /home/gmurczykpa/Documents/genixx/genixx/lib/population/Individual.cpp
lib/population/CMakeFiles/genixx-population.dir/Individual.cpp.o: lib/population/CMakeFiles/genixx-population.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/population/CMakeFiles/genixx-population.dir/Individual.cpp.o"
	cd /home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen/lib/population && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/population/CMakeFiles/genixx-population.dir/Individual.cpp.o -MF CMakeFiles/genixx-population.dir/Individual.cpp.o.d -o CMakeFiles/genixx-population.dir/Individual.cpp.o -c /home/gmurczykpa/Documents/genixx/genixx/lib/population/Individual.cpp

lib/population/CMakeFiles/genixx-population.dir/Individual.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/genixx-population.dir/Individual.cpp.i"
	cd /home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen/lib/population && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gmurczykpa/Documents/genixx/genixx/lib/population/Individual.cpp > CMakeFiles/genixx-population.dir/Individual.cpp.i

lib/population/CMakeFiles/genixx-population.dir/Individual.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/genixx-population.dir/Individual.cpp.s"
	cd /home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen/lib/population && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gmurczykpa/Documents/genixx/genixx/lib/population/Individual.cpp -o CMakeFiles/genixx-population.dir/Individual.cpp.s

lib/population/CMakeFiles/genixx-population.dir/Population.cpp.o: lib/population/CMakeFiles/genixx-population.dir/flags.make
lib/population/CMakeFiles/genixx-population.dir/Population.cpp.o: /home/gmurczykpa/Documents/genixx/genixx/lib/population/Population.cpp
lib/population/CMakeFiles/genixx-population.dir/Population.cpp.o: lib/population/CMakeFiles/genixx-population.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/population/CMakeFiles/genixx-population.dir/Population.cpp.o"
	cd /home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen/lib/population && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/population/CMakeFiles/genixx-population.dir/Population.cpp.o -MF CMakeFiles/genixx-population.dir/Population.cpp.o.d -o CMakeFiles/genixx-population.dir/Population.cpp.o -c /home/gmurczykpa/Documents/genixx/genixx/lib/population/Population.cpp

lib/population/CMakeFiles/genixx-population.dir/Population.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/genixx-population.dir/Population.cpp.i"
	cd /home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen/lib/population && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gmurczykpa/Documents/genixx/genixx/lib/population/Population.cpp > CMakeFiles/genixx-population.dir/Population.cpp.i

lib/population/CMakeFiles/genixx-population.dir/Population.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/genixx-population.dir/Population.cpp.s"
	cd /home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen/lib/population && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gmurczykpa/Documents/genixx/genixx/lib/population/Population.cpp -o CMakeFiles/genixx-population.dir/Population.cpp.s

# Object files for target genixx-population
genixx__population_OBJECTS = \
"CMakeFiles/genixx-population.dir/Individual.cpp.o" \
"CMakeFiles/genixx-population.dir/Population.cpp.o"

# External object files for target genixx-population
genixx__population_EXTERNAL_OBJECTS =

lib/libgenixx-population.a: lib/population/CMakeFiles/genixx-population.dir/Individual.cpp.o
lib/libgenixx-population.a: lib/population/CMakeFiles/genixx-population.dir/Population.cpp.o
lib/libgenixx-population.a: lib/population/CMakeFiles/genixx-population.dir/build.make
lib/libgenixx-population.a: lib/population/CMakeFiles/genixx-population.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library ../libgenixx-population.a"
	cd /home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen/lib/population && $(CMAKE_COMMAND) -P CMakeFiles/genixx-population.dir/cmake_clean_target.cmake
	cd /home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen/lib/population && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/genixx-population.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/population/CMakeFiles/genixx-population.dir/build: lib/libgenixx-population.a
.PHONY : lib/population/CMakeFiles/genixx-population.dir/build

lib/population/CMakeFiles/genixx-population.dir/clean:
	cd /home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen/lib/population && $(CMAKE_COMMAND) -P CMakeFiles/genixx-population.dir/cmake_clean.cmake
.PHONY : lib/population/CMakeFiles/genixx-population.dir/clean

lib/population/CMakeFiles/genixx-population.dir/depend:
	cd /home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gmurczykpa/Documents/genixx/genixx /home/gmurczykpa/Documents/genixx/genixx/lib/population /home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen /home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen/lib/population /home/gmurczykpa/Documents/genixx/genixx/genixx-doxygen/lib/population/CMakeFiles/genixx-population.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : lib/population/CMakeFiles/genixx-population.dir/depend

