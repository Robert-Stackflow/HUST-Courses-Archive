# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Documents\GitHub\DataStructure_Course_Design\4_Code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Documents\GitHub\DataStructure_Course_Design\4_Code\build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/src/dpll.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/dpll.c.obj: CMakeFiles/main.dir/includes_C.rsp
CMakeFiles/main.dir/src/dpll.c.obj: ../src/dpll.c
CMakeFiles/main.dir/src/dpll.c.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Documents\GitHub\DataStructure_Course_Design\4_Code\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/main.dir/src/dpll.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X8EAA8~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/src/dpll.c.obj -MF CMakeFiles\main.dir\src\dpll.c.obj.d -o CMakeFiles\main.dir\src\dpll.c.obj -c D:\Documents\GitHub\DataStructure_Course_Design\4_Code\src\dpll.c

CMakeFiles/main.dir/src/dpll.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/dpll.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X8EAA8~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Documents\GitHub\DataStructure_Course_Design\4_Code\src\dpll.c > CMakeFiles\main.dir\src\dpll.c.i

CMakeFiles/main.dir/src/dpll.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/dpll.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X8EAA8~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Documents\GitHub\DataStructure_Course_Design\4_Code\src\dpll.c -o CMakeFiles\main.dir\src\dpll.c.s

CMakeFiles/main.dir/src/fin.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/fin.c.obj: CMakeFiles/main.dir/includes_C.rsp
CMakeFiles/main.dir/src/fin.c.obj: ../src/fin.c
CMakeFiles/main.dir/src/fin.c.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Documents\GitHub\DataStructure_Course_Design\4_Code\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/main.dir/src/fin.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X8EAA8~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/src/fin.c.obj -MF CMakeFiles\main.dir\src\fin.c.obj.d -o CMakeFiles\main.dir\src\fin.c.obj -c D:\Documents\GitHub\DataStructure_Course_Design\4_Code\src\fin.c

CMakeFiles/main.dir/src/fin.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/fin.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X8EAA8~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Documents\GitHub\DataStructure_Course_Design\4_Code\src\fin.c > CMakeFiles\main.dir\src\fin.c.i

CMakeFiles/main.dir/src/fin.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/fin.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X8EAA8~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Documents\GitHub\DataStructure_Course_Design\4_Code\src\fin.c -o CMakeFiles\main.dir\src\fin.c.s

CMakeFiles/main.dir/src/main.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/main.c.obj: CMakeFiles/main.dir/includes_C.rsp
CMakeFiles/main.dir/src/main.c.obj: ../src/main.c
CMakeFiles/main.dir/src/main.c.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Documents\GitHub\DataStructure_Course_Design\4_Code\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/main.dir/src/main.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X8EAA8~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/src/main.c.obj -MF CMakeFiles\main.dir\src\main.c.obj.d -o CMakeFiles\main.dir\src\main.c.obj -c D:\Documents\GitHub\DataStructure_Course_Design\4_Code\src\main.c

CMakeFiles/main.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/main.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X8EAA8~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Documents\GitHub\DataStructure_Course_Design\4_Code\src\main.c > CMakeFiles\main.dir\src\main.c.i

CMakeFiles/main.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/main.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X8EAA8~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Documents\GitHub\DataStructure_Course_Design\4_Code\src\main.c -o CMakeFiles\main.dir\src\main.c.s

CMakeFiles/main.dir/src/sudoku.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/sudoku.c.obj: CMakeFiles/main.dir/includes_C.rsp
CMakeFiles/main.dir/src/sudoku.c.obj: ../src/sudoku.c
CMakeFiles/main.dir/src/sudoku.c.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Documents\GitHub\DataStructure_Course_Design\4_Code\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/main.dir/src/sudoku.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X8EAA8~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/src/sudoku.c.obj -MF CMakeFiles\main.dir\src\sudoku.c.obj.d -o CMakeFiles\main.dir\src\sudoku.c.obj -c D:\Documents\GitHub\DataStructure_Course_Design\4_Code\src\sudoku.c

CMakeFiles/main.dir/src/sudoku.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/sudoku.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X8EAA8~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Documents\GitHub\DataStructure_Course_Design\4_Code\src\sudoku.c > CMakeFiles\main.dir\src\sudoku.c.i

CMakeFiles/main.dir/src/sudoku.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/sudoku.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X8EAA8~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Documents\GitHub\DataStructure_Course_Design\4_Code\src\sudoku.c -o CMakeFiles\main.dir\src\sudoku.c.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/src/dpll.c.obj" \
"CMakeFiles/main.dir/src/fin.c.obj" \
"CMakeFiles/main.dir/src/main.c.obj" \
"CMakeFiles/main.dir/src/sudoku.c.obj"

# External object files for target main
main_EXTERNAL_OBJECTS =

../main.exe: CMakeFiles/main.dir/src/dpll.c.obj
../main.exe: CMakeFiles/main.dir/src/fin.c.obj
../main.exe: CMakeFiles/main.dir/src/main.c.obj
../main.exe: CMakeFiles/main.dir/src/sudoku.c.obj
../main.exe: CMakeFiles/main.dir/build.make
../main.exe: CMakeFiles/main.dir/linklibs.rsp
../main.exe: CMakeFiles/main.dir/objects1.rsp
../main.exe: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Documents\GitHub\DataStructure_Course_Design\4_Code\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable ..\main.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\main.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: ../main.exe
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\main.dir\cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Documents\GitHub\DataStructure_Course_Design\4_Code D:\Documents\GitHub\DataStructure_Course_Design\4_Code D:\Documents\GitHub\DataStructure_Course_Design\4_Code\build D:\Documents\GitHub\DataStructure_Course_Design\4_Code\build D:\Documents\GitHub\DataStructure_Course_Design\4_Code\build\CMakeFiles\main.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

