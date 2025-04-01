.PHONY: clean clean/debug clean/all run run/unoptimized run/debug rebuild rebuild/unoptimized rebuild/debug

CC = g++
CFLAGS = -std=c++20 -Wall -Wshadow -Wpedantic
LDFLAGS = -lglfw3 -lglew32 -lopengl32

# Path to the vendor libs
GLFW_LIB_DIR = vendor/GLFW/libs
GL_LIB_DIR = vendor/GL/libs
STB_LIB_DIR = vendor/STB/libs

# Path to the vendor include dirs
GLFW_INCLUDE_DIR = vendor/GLFW/include
GL_INCLUDE_DIR = vendor/GL/include
STB_INCLUDE_DIR = vendor/STB/include

# Name of the output executable
OUTPUT_DIR = bin/build
OUTPUT = $(OUTPUT_DIR)/app

DEBUG_DIR = bin/debug
DEBUG = $(DEBUG_DIR)/app

# Source files and object files
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/**/*.cpp)

OBJ_DIR = $(OUTPUT_DIR)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

DEBUG_OBJ_DIR = $(DEBUG_DIR)
DEBUG_OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(DEBUG_DIR)/%.o)

# Make will default to the first defined target command if given none
# "$ make" will run "$ make release"
release: CFLAGS += -O3
release: $(OUTPUT)

# Ensure the respective object directories exist
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)  # Create the directory for the object file
	$(CC) $(CFLAGS) -c -o $@ $< -I $(GLFW_INCLUDE_DIR) -I $(GL_INCLUDE_DIR) -I $(STB_INCLUDE_DIR)

$(OUTPUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L $(GLFW_LIB_DIR) -L $(GL_LIB_DIR) -L $(STB_LIB_DIR) $(LDFLAGS) 

# Useful for seeing what parameters are being unused
unoptimized: CFLAGS += -O0 -Wextra
unoptimized: $(OUTPUT)

# General purpose to show as many things as we can to see any possible issue
debug: CFLAGS += -DDEBUG -O0 -g -Wextra -Wuninitialized -Wunreachable-code -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Woverloaded-virtual -Wsign-conversion -Wnull-dereference -Wformat=2 -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast
debug: $(DEBUG)

# Ensure the respective object directories exist
$(DEBUG_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)  # Create the directory for the object file
	$(CC) $(CFLAGS) -c -o $@ $< -I $(GLFW_INCLUDE_DIR) -I $(GL_INCLUDE_DIR) -I $(STB_INCLUDE_DIR)

$(DEBUG): $(DEBUG_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L $(GLFW_LIB_DIR) -L $(GL_LIB_DIR) -L $(STB_LIB_DIR) $(LDFLAGS)

clean:
	if [ -d "$(OUTPUT_DIR)" ]; then \
		rm -rf $(OUTPUT_DIR)/**; \
		rm -f $(OUTPUT_DIR)/**; \
	fi

clean/debug:
	if [ -d "$(DEBUG_DIR)" ]; then \
		rm -rf $(DEBUG_DIR)/**; \
		rm -f $(DEBUG_DIR)/**; \
	fi

clean/all:
	$(MAKE) clean
	$(MAKE) clean/debug

run: 
	$(MAKE) release
	@$(OUTPUT);

run/unoptimized: 
	$(MAKE) unoptimized
	@$(OUTPUT);

run/debug:
	$(MAKE) debug
	@$(DEBUG);

rebuild:
	$(MAKE) clean
	$(MAKE) release

rebuild/unoptimized:
	$(MAKE) clean
	$(MAKE) unoptimized

rebuild/debug:
	$(MAKE) clean/debug
	$(MAKE) debug

help:
	@echo "Here is the list of commands available:";
	@echo "    make";
	@echo "    make release";
	@echo "    make unoptimized";
	@echo "    make debug";
	@echo "    make clean";
	@echo "    make clean/debug";
	@echo "    make clean/all";
	@echo "    make run";
	@echo "    make run/unoptimized";
	@echo "    make run/debug";
	@echo "    make rebuild";
	@echo "    make rebuild/unoptimized";
	@echo "    make rebuild/debug";

# for running the makefile commands through vscode's interface
copy:
	@Xcopy "C:\\Users\\work\\Code\\CPP_C\\PhysicsModelSystem\\models\\" "C:\\Users\\work\\Code\\CPP_C\\PhysicsModelSystem\\bin\\build\\models\\"
	@Xcopy "C:\\Users\\work\\Code\\CPP_C\\PhysicsModelSystem\\shaders\\" "C:\\Users\\work\\Code\\CPP_C\\PhysicsModelSystem\\bin\\build\\shaders\\"

copy/debug:
	@Xcopy "C:\\Users\\work\\Code\\CPP_C\\PhysicsModelSystem\\models\\" "C:\\Users\\work\\Code\\CPP_C\\PhysicsModelSystem\\bin\\debug\\models\\"
	@Xcopy "C:\\Users\\work\\Code\\CPP_C\\PhysicsModelSystem\\shaders\\" "C:\\Users\\work\\Code\\CPP_C\\PhysicsModelSystem\\bin\\debug\\shaders\\"
