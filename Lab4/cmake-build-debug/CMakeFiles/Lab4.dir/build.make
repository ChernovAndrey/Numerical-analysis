# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/andrey/Загрузки/clion-2017.2.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/andrey/Загрузки/clion-2017.2.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/andrey/CLionProjects/NumericalMethods/Lab4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrey/CLionProjects/NumericalMethods/Lab4/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Lab4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab4.dir/flags.make

CMakeFiles/Lab4.dir/main.cpp.o: CMakeFiles/Lab4.dir/flags.make
CMakeFiles/Lab4.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrey/CLionProjects/NumericalMethods/Lab4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lab4.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab4.dir/main.cpp.o -c /home/andrey/CLionProjects/NumericalMethods/Lab4/main.cpp

CMakeFiles/Lab4.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab4.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrey/CLionProjects/NumericalMethods/Lab4/main.cpp > CMakeFiles/Lab4.dir/main.cpp.i

CMakeFiles/Lab4.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab4.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrey/CLionProjects/NumericalMethods/Lab4/main.cpp -o CMakeFiles/Lab4.dir/main.cpp.s

CMakeFiles/Lab4.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Lab4.dir/main.cpp.o.requires

CMakeFiles/Lab4.dir/main.cpp.o.provides: CMakeFiles/Lab4.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Lab4.dir/build.make CMakeFiles/Lab4.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Lab4.dir/main.cpp.o.provides

CMakeFiles/Lab4.dir/main.cpp.o.provides.build: CMakeFiles/Lab4.dir/main.cpp.o


CMakeFiles/Lab4.dir/matrixOperations.cpp.o: CMakeFiles/Lab4.dir/flags.make
CMakeFiles/Lab4.dir/matrixOperations.cpp.o: ../matrixOperations.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrey/CLionProjects/NumericalMethods/Lab4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Lab4.dir/matrixOperations.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab4.dir/matrixOperations.cpp.o -c /home/andrey/CLionProjects/NumericalMethods/Lab4/matrixOperations.cpp

CMakeFiles/Lab4.dir/matrixOperations.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab4.dir/matrixOperations.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrey/CLionProjects/NumericalMethods/Lab4/matrixOperations.cpp > CMakeFiles/Lab4.dir/matrixOperations.cpp.i

CMakeFiles/Lab4.dir/matrixOperations.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab4.dir/matrixOperations.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrey/CLionProjects/NumericalMethods/Lab4/matrixOperations.cpp -o CMakeFiles/Lab4.dir/matrixOperations.cpp.s

CMakeFiles/Lab4.dir/matrixOperations.cpp.o.requires:

.PHONY : CMakeFiles/Lab4.dir/matrixOperations.cpp.o.requires

CMakeFiles/Lab4.dir/matrixOperations.cpp.o.provides: CMakeFiles/Lab4.dir/matrixOperations.cpp.o.requires
	$(MAKE) -f CMakeFiles/Lab4.dir/build.make CMakeFiles/Lab4.dir/matrixOperations.cpp.o.provides.build
.PHONY : CMakeFiles/Lab4.dir/matrixOperations.cpp.o.provides

CMakeFiles/Lab4.dir/matrixOperations.cpp.o.provides.build: CMakeFiles/Lab4.dir/matrixOperations.cpp.o


CMakeFiles/Lab4.dir/sourceMatrices.cpp.o: CMakeFiles/Lab4.dir/flags.make
CMakeFiles/Lab4.dir/sourceMatrices.cpp.o: ../sourceMatrices.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrey/CLionProjects/NumericalMethods/Lab4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Lab4.dir/sourceMatrices.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab4.dir/sourceMatrices.cpp.o -c /home/andrey/CLionProjects/NumericalMethods/Lab4/sourceMatrices.cpp

CMakeFiles/Lab4.dir/sourceMatrices.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab4.dir/sourceMatrices.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrey/CLionProjects/NumericalMethods/Lab4/sourceMatrices.cpp > CMakeFiles/Lab4.dir/sourceMatrices.cpp.i

CMakeFiles/Lab4.dir/sourceMatrices.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab4.dir/sourceMatrices.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrey/CLionProjects/NumericalMethods/Lab4/sourceMatrices.cpp -o CMakeFiles/Lab4.dir/sourceMatrices.cpp.s

CMakeFiles/Lab4.dir/sourceMatrices.cpp.o.requires:

.PHONY : CMakeFiles/Lab4.dir/sourceMatrices.cpp.o.requires

CMakeFiles/Lab4.dir/sourceMatrices.cpp.o.provides: CMakeFiles/Lab4.dir/sourceMatrices.cpp.o.requires
	$(MAKE) -f CMakeFiles/Lab4.dir/build.make CMakeFiles/Lab4.dir/sourceMatrices.cpp.o.provides.build
.PHONY : CMakeFiles/Lab4.dir/sourceMatrices.cpp.o.provides

CMakeFiles/Lab4.dir/sourceMatrices.cpp.o.provides.build: CMakeFiles/Lab4.dir/sourceMatrices.cpp.o


CMakeFiles/Lab4.dir/vectorOperations.cpp.o: CMakeFiles/Lab4.dir/flags.make
CMakeFiles/Lab4.dir/vectorOperations.cpp.o: ../vectorOperations.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrey/CLionProjects/NumericalMethods/Lab4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Lab4.dir/vectorOperations.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab4.dir/vectorOperations.cpp.o -c /home/andrey/CLionProjects/NumericalMethods/Lab4/vectorOperations.cpp

CMakeFiles/Lab4.dir/vectorOperations.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab4.dir/vectorOperations.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrey/CLionProjects/NumericalMethods/Lab4/vectorOperations.cpp > CMakeFiles/Lab4.dir/vectorOperations.cpp.i

CMakeFiles/Lab4.dir/vectorOperations.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab4.dir/vectorOperations.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrey/CLionProjects/NumericalMethods/Lab4/vectorOperations.cpp -o CMakeFiles/Lab4.dir/vectorOperations.cpp.s

CMakeFiles/Lab4.dir/vectorOperations.cpp.o.requires:

.PHONY : CMakeFiles/Lab4.dir/vectorOperations.cpp.o.requires

CMakeFiles/Lab4.dir/vectorOperations.cpp.o.provides: CMakeFiles/Lab4.dir/vectorOperations.cpp.o.requires
	$(MAKE) -f CMakeFiles/Lab4.dir/build.make CMakeFiles/Lab4.dir/vectorOperations.cpp.o.provides.build
.PHONY : CMakeFiles/Lab4.dir/vectorOperations.cpp.o.provides

CMakeFiles/Lab4.dir/vectorOperations.cpp.o.provides.build: CMakeFiles/Lab4.dir/vectorOperations.cpp.o


# Object files for target Lab4
Lab4_OBJECTS = \
"CMakeFiles/Lab4.dir/main.cpp.o" \
"CMakeFiles/Lab4.dir/matrixOperations.cpp.o" \
"CMakeFiles/Lab4.dir/sourceMatrices.cpp.o" \
"CMakeFiles/Lab4.dir/vectorOperations.cpp.o"

# External object files for target Lab4
Lab4_EXTERNAL_OBJECTS =

Lab4: CMakeFiles/Lab4.dir/main.cpp.o
Lab4: CMakeFiles/Lab4.dir/matrixOperations.cpp.o
Lab4: CMakeFiles/Lab4.dir/sourceMatrices.cpp.o
Lab4: CMakeFiles/Lab4.dir/vectorOperations.cpp.o
Lab4: CMakeFiles/Lab4.dir/build.make
Lab4: CMakeFiles/Lab4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrey/CLionProjects/NumericalMethods/Lab4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Lab4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab4.dir/build: Lab4

.PHONY : CMakeFiles/Lab4.dir/build

CMakeFiles/Lab4.dir/requires: CMakeFiles/Lab4.dir/main.cpp.o.requires
CMakeFiles/Lab4.dir/requires: CMakeFiles/Lab4.dir/matrixOperations.cpp.o.requires
CMakeFiles/Lab4.dir/requires: CMakeFiles/Lab4.dir/sourceMatrices.cpp.o.requires
CMakeFiles/Lab4.dir/requires: CMakeFiles/Lab4.dir/vectorOperations.cpp.o.requires

.PHONY : CMakeFiles/Lab4.dir/requires

CMakeFiles/Lab4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab4.dir/clean

CMakeFiles/Lab4.dir/depend:
	cd /home/andrey/CLionProjects/NumericalMethods/Lab4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrey/CLionProjects/NumericalMethods/Lab4 /home/andrey/CLionProjects/NumericalMethods/Lab4 /home/andrey/CLionProjects/NumericalMethods/Lab4/cmake-build-debug /home/andrey/CLionProjects/NumericalMethods/Lab4/cmake-build-debug /home/andrey/CLionProjects/NumericalMethods/Lab4/cmake-build-debug/CMakeFiles/Lab4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Lab4.dir/depend

