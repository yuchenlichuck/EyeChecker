# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = "D:\Program Files\JetBrains\CLion 2018.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\JetBrains\CLion 2018.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\code\EyeChecker\EyeChecker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\code\EyeChecker\EyeChecker\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/EyeChecker.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/EyeChecker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/EyeChecker.dir/flags.make

CMakeFiles/EyeChecker.dir/EyeChecker.cpp.obj: CMakeFiles/EyeChecker.dir/flags.make
CMakeFiles/EyeChecker.dir/EyeChecker.cpp.obj: ../EyeChecker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\EyeChecker\EyeChecker\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/EyeChecker.dir/EyeChecker.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\EyeChecker.dir\EyeChecker.cpp.obj -c D:\code\EyeChecker\EyeChecker\EyeChecker.cpp

CMakeFiles/EyeChecker.dir/EyeChecker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EyeChecker.dir/EyeChecker.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\code\EyeChecker\EyeChecker\EyeChecker.cpp > CMakeFiles\EyeChecker.dir\EyeChecker.cpp.i

CMakeFiles/EyeChecker.dir/EyeChecker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EyeChecker.dir/EyeChecker.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\code\EyeChecker\EyeChecker\EyeChecker.cpp -o CMakeFiles\EyeChecker.dir\EyeChecker.cpp.s

CMakeFiles/EyeChecker.dir/mmm.cpp.obj: CMakeFiles/EyeChecker.dir/flags.make
CMakeFiles/EyeChecker.dir/mmm.cpp.obj: ../mmm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\EyeChecker\EyeChecker\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/EyeChecker.dir/mmm.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\EyeChecker.dir\mmm.cpp.obj -c D:\code\EyeChecker\EyeChecker\mmm.cpp

CMakeFiles/EyeChecker.dir/mmm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EyeChecker.dir/mmm.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\code\EyeChecker\EyeChecker\mmm.cpp > CMakeFiles\EyeChecker.dir\mmm.cpp.i

CMakeFiles/EyeChecker.dir/mmm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EyeChecker.dir/mmm.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\code\EyeChecker\EyeChecker\mmm.cpp -o CMakeFiles\EyeChecker.dir\mmm.cpp.s

CMakeFiles/EyeChecker.dir/pch.cpp.obj: CMakeFiles/EyeChecker.dir/flags.make
CMakeFiles/EyeChecker.dir/pch.cpp.obj: ../pch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\EyeChecker\EyeChecker\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/EyeChecker.dir/pch.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\EyeChecker.dir\pch.cpp.obj -c D:\code\EyeChecker\EyeChecker\pch.cpp

CMakeFiles/EyeChecker.dir/pch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EyeChecker.dir/pch.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\code\EyeChecker\EyeChecker\pch.cpp > CMakeFiles\EyeChecker.dir\pch.cpp.i

CMakeFiles/EyeChecker.dir/pch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EyeChecker.dir/pch.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\code\EyeChecker\EyeChecker\pch.cpp -o CMakeFiles\EyeChecker.dir\pch.cpp.s

# Object files for target EyeChecker
EyeChecker_OBJECTS = \
"CMakeFiles/EyeChecker.dir/EyeChecker.cpp.obj" \
"CMakeFiles/EyeChecker.dir/mmm.cpp.obj" \
"CMakeFiles/EyeChecker.dir/pch.cpp.obj"

# External object files for target EyeChecker
EyeChecker_EXTERNAL_OBJECTS =

EyeChecker.exe: CMakeFiles/EyeChecker.dir/EyeChecker.cpp.obj
EyeChecker.exe: CMakeFiles/EyeChecker.dir/mmm.cpp.obj
EyeChecker.exe: CMakeFiles/EyeChecker.dir/pch.cpp.obj
EyeChecker.exe: CMakeFiles/EyeChecker.dir/build.make
EyeChecker.exe: CMakeFiles/EyeChecker.dir/objects1.rsp
EyeChecker.exe: CMakeFiles/EyeChecker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\code\EyeChecker\EyeChecker\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable EyeChecker.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\EyeChecker.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/EyeChecker.dir/build: EyeChecker.exe

.PHONY : CMakeFiles/EyeChecker.dir/build

CMakeFiles/EyeChecker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\EyeChecker.dir\cmake_clean.cmake
.PHONY : CMakeFiles/EyeChecker.dir/clean

CMakeFiles/EyeChecker.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\code\EyeChecker\EyeChecker D:\code\EyeChecker\EyeChecker D:\code\EyeChecker\EyeChecker\cmake-build-debug D:\code\EyeChecker\EyeChecker\cmake-build-debug D:\code\EyeChecker\EyeChecker\cmake-build-debug\CMakeFiles\EyeChecker.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/EyeChecker.dir/depend

