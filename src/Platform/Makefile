CC = g++
CFLAGS = -std=c++20 -Wall -Wshadow -Wpedantic
LDFLAGS = -lglfw3 -lglew32 -lopengl32

# Path to the vendor libs
GLFW_LIB_DIR = ../../vendor/GLFW/libs
GL_LIB_DIR = ../../vendor/GL/libs
STB_LIB_DIR = ../../vendor/STB/libs

# Path to the vendor include dirs
GLFW_INCLUDE_DIR = ../../vendor/GLFW/include
GL_INCLUDE_DIR = ../../vendor/GL/include
STB_INCLUDE_DIR = ../../vendor/STB/include

# Name of the output executable
OUTPUT_DIR = ../../bin/build/Platform
#OUTPUT = $(OUTPUT_DIR)/app

DEBUG_DIR = ../../bin/debug/Platform
#DEBUG = $(DEBUG_DIR)/app

# Source files and object files
SRC_DIR = ../Platform
SRC = $(wildcard $(SRC_DIR)/**/*.cpp)

OBJ_DIR = $(OUTPUT_DIR)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

DEBUG_OBJ_DIR = $(DEBUG_DIR)
DEBUG_OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(DEBUG_DIR)/%.o)

# Make will default to the first defined target command if given none
# "$ make" will run "$ make release"
release: CFLAGS += -O3
release: $(OBJ)

# Ensure the respective object directories exist
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)  # Create the directory for the object file
	$(CC) $(CFLAGS) -c -o $@ $< -I $(GLFW_INCLUDE_DIR) -I $(GL_INCLUDE_DIR) -I $(STB_INCLUDE_DIR)

# Useful for seeing what parameters are being unused
unoptimized: CFLAGS += -O0 -Wextra
unoptimized: $(OBJ)

# General purpose to show as many things as we can to see any possible issue
debug: CFLAGS += -DDEBUG -O0 -g -Wextra -Wuninitialized -Wunreachable-code -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Woverloaded-virtual -Wsign-conversion -Wnull-dereference -Wformat=2 -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast
debug: $(DEBUG_OBJ)

# Ensure the respective object directories exist
$(DEBUG_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)  # Create the directory for the object file
	$(CC) $(CFLAGS) -c -o $@ $< -I $(GLFW_INCLUDE_DIR) -I $(GL_INCLUDE_DIR) -I $(STB_INCLUDE_DIR)

