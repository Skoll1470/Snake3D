# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/max/Documents/master1/MOTEUR/Snake3D

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/max/Documents/master1/MOTEUR/Snake3D/build

# Include any dependencies generated for this target.
include CMakeFiles/Snake.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Snake.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Snake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Snake.dir/flags.make

CMakeFiles/Snake.dir/Snake/Snake.cpp.o: CMakeFiles/Snake.dir/flags.make
CMakeFiles/Snake.dir/Snake/Snake.cpp.o: ../Snake/Snake.cpp
CMakeFiles/Snake.dir/Snake/Snake.cpp.o: CMakeFiles/Snake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/max/Documents/master1/MOTEUR/Snake3D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Snake.dir/Snake/Snake.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Snake.dir/Snake/Snake.cpp.o -MF CMakeFiles/Snake.dir/Snake/Snake.cpp.o.d -o CMakeFiles/Snake.dir/Snake/Snake.cpp.o -c /Users/max/Documents/master1/MOTEUR/Snake3D/Snake/Snake.cpp

CMakeFiles/Snake.dir/Snake/Snake.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Snake.dir/Snake/Snake.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/max/Documents/master1/MOTEUR/Snake3D/Snake/Snake.cpp > CMakeFiles/Snake.dir/Snake/Snake.cpp.i

CMakeFiles/Snake.dir/Snake/Snake.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Snake.dir/Snake/Snake.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/max/Documents/master1/MOTEUR/Snake3D/Snake/Snake.cpp -o CMakeFiles/Snake.dir/Snake/Snake.cpp.s

CMakeFiles/Snake.dir/common/shader.cpp.o: CMakeFiles/Snake.dir/flags.make
CMakeFiles/Snake.dir/common/shader.cpp.o: ../common/shader.cpp
CMakeFiles/Snake.dir/common/shader.cpp.o: CMakeFiles/Snake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/max/Documents/master1/MOTEUR/Snake3D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Snake.dir/common/shader.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Snake.dir/common/shader.cpp.o -MF CMakeFiles/Snake.dir/common/shader.cpp.o.d -o CMakeFiles/Snake.dir/common/shader.cpp.o -c /Users/max/Documents/master1/MOTEUR/Snake3D/common/shader.cpp

CMakeFiles/Snake.dir/common/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Snake.dir/common/shader.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/max/Documents/master1/MOTEUR/Snake3D/common/shader.cpp > CMakeFiles/Snake.dir/common/shader.cpp.i

CMakeFiles/Snake.dir/common/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Snake.dir/common/shader.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/max/Documents/master1/MOTEUR/Snake3D/common/shader.cpp -o CMakeFiles/Snake.dir/common/shader.cpp.s

CMakeFiles/Snake.dir/common/controls.cpp.o: CMakeFiles/Snake.dir/flags.make
CMakeFiles/Snake.dir/common/controls.cpp.o: ../common/controls.cpp
CMakeFiles/Snake.dir/common/controls.cpp.o: CMakeFiles/Snake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/max/Documents/master1/MOTEUR/Snake3D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Snake.dir/common/controls.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Snake.dir/common/controls.cpp.o -MF CMakeFiles/Snake.dir/common/controls.cpp.o.d -o CMakeFiles/Snake.dir/common/controls.cpp.o -c /Users/max/Documents/master1/MOTEUR/Snake3D/common/controls.cpp

CMakeFiles/Snake.dir/common/controls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Snake.dir/common/controls.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/max/Documents/master1/MOTEUR/Snake3D/common/controls.cpp > CMakeFiles/Snake.dir/common/controls.cpp.i

CMakeFiles/Snake.dir/common/controls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Snake.dir/common/controls.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/max/Documents/master1/MOTEUR/Snake3D/common/controls.cpp -o CMakeFiles/Snake.dir/common/controls.cpp.s

CMakeFiles/Snake.dir/common/texture.cpp.o: CMakeFiles/Snake.dir/flags.make
CMakeFiles/Snake.dir/common/texture.cpp.o: ../common/texture.cpp
CMakeFiles/Snake.dir/common/texture.cpp.o: CMakeFiles/Snake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/max/Documents/master1/MOTEUR/Snake3D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Snake.dir/common/texture.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Snake.dir/common/texture.cpp.o -MF CMakeFiles/Snake.dir/common/texture.cpp.o.d -o CMakeFiles/Snake.dir/common/texture.cpp.o -c /Users/max/Documents/master1/MOTEUR/Snake3D/common/texture.cpp

CMakeFiles/Snake.dir/common/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Snake.dir/common/texture.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/max/Documents/master1/MOTEUR/Snake3D/common/texture.cpp > CMakeFiles/Snake.dir/common/texture.cpp.i

CMakeFiles/Snake.dir/common/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Snake.dir/common/texture.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/max/Documents/master1/MOTEUR/Snake3D/common/texture.cpp -o CMakeFiles/Snake.dir/common/texture.cpp.s

CMakeFiles/Snake.dir/common/objloader.cpp.o: CMakeFiles/Snake.dir/flags.make
CMakeFiles/Snake.dir/common/objloader.cpp.o: ../common/objloader.cpp
CMakeFiles/Snake.dir/common/objloader.cpp.o: CMakeFiles/Snake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/max/Documents/master1/MOTEUR/Snake3D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Snake.dir/common/objloader.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Snake.dir/common/objloader.cpp.o -MF CMakeFiles/Snake.dir/common/objloader.cpp.o.d -o CMakeFiles/Snake.dir/common/objloader.cpp.o -c /Users/max/Documents/master1/MOTEUR/Snake3D/common/objloader.cpp

CMakeFiles/Snake.dir/common/objloader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Snake.dir/common/objloader.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/max/Documents/master1/MOTEUR/Snake3D/common/objloader.cpp > CMakeFiles/Snake.dir/common/objloader.cpp.i

CMakeFiles/Snake.dir/common/objloader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Snake.dir/common/objloader.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/max/Documents/master1/MOTEUR/Snake3D/common/objloader.cpp -o CMakeFiles/Snake.dir/common/objloader.cpp.s

CMakeFiles/Snake.dir/common/vboindexer.cpp.o: CMakeFiles/Snake.dir/flags.make
CMakeFiles/Snake.dir/common/vboindexer.cpp.o: ../common/vboindexer.cpp
CMakeFiles/Snake.dir/common/vboindexer.cpp.o: CMakeFiles/Snake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/max/Documents/master1/MOTEUR/Snake3D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Snake.dir/common/vboindexer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Snake.dir/common/vboindexer.cpp.o -MF CMakeFiles/Snake.dir/common/vboindexer.cpp.o.d -o CMakeFiles/Snake.dir/common/vboindexer.cpp.o -c /Users/max/Documents/master1/MOTEUR/Snake3D/common/vboindexer.cpp

CMakeFiles/Snake.dir/common/vboindexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Snake.dir/common/vboindexer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/max/Documents/master1/MOTEUR/Snake3D/common/vboindexer.cpp > CMakeFiles/Snake.dir/common/vboindexer.cpp.i

CMakeFiles/Snake.dir/common/vboindexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Snake.dir/common/vboindexer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/max/Documents/master1/MOTEUR/Snake3D/common/vboindexer.cpp -o CMakeFiles/Snake.dir/common/vboindexer.cpp.s

# Object files for target Snake
Snake_OBJECTS = \
"CMakeFiles/Snake.dir/Snake/Snake.cpp.o" \
"CMakeFiles/Snake.dir/common/shader.cpp.o" \
"CMakeFiles/Snake.dir/common/controls.cpp.o" \
"CMakeFiles/Snake.dir/common/texture.cpp.o" \
"CMakeFiles/Snake.dir/common/objloader.cpp.o" \
"CMakeFiles/Snake.dir/common/vboindexer.cpp.o"

# External object files for target Snake
Snake_EXTERNAL_OBJECTS =

Snake: CMakeFiles/Snake.dir/Snake/Snake.cpp.o
Snake: CMakeFiles/Snake.dir/common/shader.cpp.o
Snake: CMakeFiles/Snake.dir/common/controls.cpp.o
Snake: CMakeFiles/Snake.dir/common/texture.cpp.o
Snake: CMakeFiles/Snake.dir/common/objloader.cpp.o
Snake: CMakeFiles/Snake.dir/common/vboindexer.cpp.o
Snake: CMakeFiles/Snake.dir/build.make
Snake: external/glfw-3.1.2/src/libglfw3.a
Snake: external/libGLEW_1130.a
Snake: CMakeFiles/Snake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/max/Documents/master1/MOTEUR/Snake3D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable Snake"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Snake.dir/link.txt --verbose=$(VERBOSE)
	/opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E copy /Users/max/Documents/master1/MOTEUR/Snake3D/build/./Snake /Users/max/Documents/master1/MOTEUR/Snake3D/Snake/

# Rule to build all files generated by this target.
CMakeFiles/Snake.dir/build: Snake
.PHONY : CMakeFiles/Snake.dir/build

CMakeFiles/Snake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Snake.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Snake.dir/clean

CMakeFiles/Snake.dir/depend:
	cd /Users/max/Documents/master1/MOTEUR/Snake3D/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/max/Documents/master1/MOTEUR/Snake3D /Users/max/Documents/master1/MOTEUR/Snake3D /Users/max/Documents/master1/MOTEUR/Snake3D/build /Users/max/Documents/master1/MOTEUR/Snake3D/build /Users/max/Documents/master1/MOTEUR/Snake3D/build/CMakeFiles/Snake.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Snake.dir/depend
