# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/daniel/Documents/workplace/CC3k

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daniel/Documents/workplace/CC3k

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/cmake-gui -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/daniel/Documents/workplace/CC3k/CMakeFiles /home/daniel/Documents/workplace/CC3k/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/daniel/Documents/workplace/CC3k/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named cc3k

# Build rule for target.
cc3k: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 cc3k
.PHONY : cc3k

# fast build rule for target.
cc3k/fast:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/build
.PHONY : cc3k/fast

src/entity.o: src/entity.cc.o

.PHONY : src/entity.o

# target to build an object file
src/entity.cc.o:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/entity.cc.o
.PHONY : src/entity.cc.o

src/entity.i: src/entity.cc.i

.PHONY : src/entity.i

# target to preprocess a source file
src/entity.cc.i:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/entity.cc.i
.PHONY : src/entity.cc.i

src/entity.s: src/entity.cc.s

.PHONY : src/entity.s

# target to generate assembly for a file
src/entity.cc.s:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/entity.cc.s
.PHONY : src/entity.cc.s

src/entityManager.o: src/entityManager.cc.o

.PHONY : src/entityManager.o

# target to build an object file
src/entityManager.cc.o:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/entityManager.cc.o
.PHONY : src/entityManager.cc.o

src/entityManager.i: src/entityManager.cc.i

.PHONY : src/entityManager.i

# target to preprocess a source file
src/entityManager.cc.i:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/entityManager.cc.i
.PHONY : src/entityManager.cc.i

src/entityManager.s: src/entityManager.cc.s

.PHONY : src/entityManager.s

# target to generate assembly for a file
src/entityManager.cc.s:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/entityManager.cc.s
.PHONY : src/entityManager.cc.s

src/game.o: src/game.cc.o

.PHONY : src/game.o

# target to build an object file
src/game.cc.o:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/game.cc.o
.PHONY : src/game.cc.o

src/game.i: src/game.cc.i

.PHONY : src/game.i

# target to preprocess a source file
src/game.cc.i:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/game.cc.i
.PHONY : src/game.cc.i

src/game.s: src/game.cc.s

.PHONY : src/game.s

# target to generate assembly for a file
src/game.cc.s:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/game.cc.s
.PHONY : src/game.cc.s

src/graphics.o: src/graphics.cc.o

.PHONY : src/graphics.o

# target to build an object file
src/graphics.cc.o:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/graphics.cc.o
.PHONY : src/graphics.cc.o

src/graphics.i: src/graphics.cc.i

.PHONY : src/graphics.i

# target to preprocess a source file
src/graphics.cc.i:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/graphics.cc.i
.PHONY : src/graphics.cc.i

src/graphics.s: src/graphics.cc.s

.PHONY : src/graphics.s

# target to generate assembly for a file
src/graphics.cc.s:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/graphics.cc.s
.PHONY : src/graphics.cc.s

src/inputManager.o: src/inputManager.cc.o

.PHONY : src/inputManager.o

# target to build an object file
src/inputManager.cc.o:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/inputManager.cc.o
.PHONY : src/inputManager.cc.o

src/inputManager.i: src/inputManager.cc.i

.PHONY : src/inputManager.i

# target to preprocess a source file
src/inputManager.cc.i:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/inputManager.cc.i
.PHONY : src/inputManager.cc.i

src/inputManager.s: src/inputManager.cc.s

.PHONY : src/inputManager.s

# target to generate assembly for a file
src/inputManager.cc.s:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/inputManager.cc.s
.PHONY : src/inputManager.cc.s

src/main.o: src/main.cc.o

.PHONY : src/main.o

# target to build an object file
src/main.cc.o:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/main.cc.o
.PHONY : src/main.cc.o

src/main.i: src/main.cc.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cc.i:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/main.cc.i
.PHONY : src/main.cc.i

src/main.s: src/main.cc.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cc.s:
	$(MAKE) -f CMakeFiles/cc3k.dir/build.make CMakeFiles/cc3k.dir/src/main.cc.s
.PHONY : src/main.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... cc3k"
	@echo "... edit_cache"
	@echo "... src/entity.o"
	@echo "... src/entity.i"
	@echo "... src/entity.s"
	@echo "... src/entityManager.o"
	@echo "... src/entityManager.i"
	@echo "... src/entityManager.s"
	@echo "... src/game.o"
	@echo "... src/game.i"
	@echo "... src/game.s"
	@echo "... src/graphics.o"
	@echo "... src/graphics.i"
	@echo "... src/graphics.s"
	@echo "... src/inputManager.o"
	@echo "... src/inputManager.i"
	@echo "... src/inputManager.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

