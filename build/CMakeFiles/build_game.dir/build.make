# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = "/mnt/HDD/CPP/Games/Build Game"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/HDD/CPP/Games/Build Game/build"

# Include any dependencies generated for this target.
include CMakeFiles/build_game.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/build_game.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/build_game.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/build_game.dir/flags.make

CMakeFiles/build_game.dir/src/main.cpp.o: CMakeFiles/build_game.dir/flags.make
CMakeFiles/build_game.dir/src/main.cpp.o: /mnt/HDD/CPP/Games/Build\ Game/src/main.cpp
CMakeFiles/build_game.dir/src/main.cpp.o: CMakeFiles/build_game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/HDD/CPP/Games/Build Game/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/build_game.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/build_game.dir/src/main.cpp.o -MF CMakeFiles/build_game.dir/src/main.cpp.o.d -o CMakeFiles/build_game.dir/src/main.cpp.o -c "/mnt/HDD/CPP/Games/Build Game/src/main.cpp"

CMakeFiles/build_game.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/build_game.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/HDD/CPP/Games/Build Game/src/main.cpp" > CMakeFiles/build_game.dir/src/main.cpp.i

CMakeFiles/build_game.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/build_game.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/HDD/CPP/Games/Build Game/src/main.cpp" -o CMakeFiles/build_game.dir/src/main.cpp.s

CMakeFiles/build_game.dir/src/utils.cpp.o: CMakeFiles/build_game.dir/flags.make
CMakeFiles/build_game.dir/src/utils.cpp.o: /mnt/HDD/CPP/Games/Build\ Game/src/utils.cpp
CMakeFiles/build_game.dir/src/utils.cpp.o: CMakeFiles/build_game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/HDD/CPP/Games/Build Game/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/build_game.dir/src/utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/build_game.dir/src/utils.cpp.o -MF CMakeFiles/build_game.dir/src/utils.cpp.o.d -o CMakeFiles/build_game.dir/src/utils.cpp.o -c "/mnt/HDD/CPP/Games/Build Game/src/utils.cpp"

CMakeFiles/build_game.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/build_game.dir/src/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/HDD/CPP/Games/Build Game/src/utils.cpp" > CMakeFiles/build_game.dir/src/utils.cpp.i

CMakeFiles/build_game.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/build_game.dir/src/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/HDD/CPP/Games/Build Game/src/utils.cpp" -o CMakeFiles/build_game.dir/src/utils.cpp.s

# Object files for target build_game
build_game_OBJECTS = \
"CMakeFiles/build_game.dir/src/main.cpp.o" \
"CMakeFiles/build_game.dir/src/utils.cpp.o"

# External object files for target build_game
build_game_EXTERNAL_OBJECTS =

build_game: CMakeFiles/build_game.dir/src/main.cpp.o
build_game: CMakeFiles/build_game.dir/src/utils.cpp.o
build_game: CMakeFiles/build_game.dir/build.make
build_game: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.8
build_game: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.8
build_game: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.8
build_game: CMakeFiles/build_game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/HDD/CPP/Games/Build Game/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable build_game"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/build_game.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/build_game.dir/build: build_game
.PHONY : CMakeFiles/build_game.dir/build

CMakeFiles/build_game.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/build_game.dir/cmake_clean.cmake
.PHONY : CMakeFiles/build_game.dir/clean

CMakeFiles/build_game.dir/depend:
	cd "/mnt/HDD/CPP/Games/Build Game/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/HDD/CPP/Games/Build Game" "/mnt/HDD/CPP/Games/Build Game" "/mnt/HDD/CPP/Games/Build Game/build" "/mnt/HDD/CPP/Games/Build Game/build" "/mnt/HDD/CPP/Games/Build Game/build/CMakeFiles/build_game.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/build_game.dir/depend
