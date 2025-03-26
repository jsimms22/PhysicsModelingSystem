CC = g++
CFLAGS = -std=c++17 -Wall -Wpedantic -Wshadow -Wextra
LDFLAGS = -lglfw3 -lglew32 -lopengl32

# Path to the vendor libs
GLFW_LIB_DIR = vendor/GLFW/libs
GL_LIB_DIR = vendor/GL/libs

# Path to the vendor include dirs
GLFW_INCLUDE_DIR = vendor/GLFW/include
GL_INCLUDE_DIR = vendor/GL/include

# Name of the output executable
OUTPUT_DIR = build
OUTPUT = $(OUTPUT_DIR)/app

# Source files and object files
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_DIR = $(OUTPUT_DIR)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Ensure the build directory exists
$(shell mkdir -p $(OBJ_DIR))

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L $(GLFW_LIB_DIR) -L $(GL_LIB_DIR) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I $(GLFW_INCLUDE_DIR) -I $(GL_INCLUDE_DIR)

debug: CFLAGS += -DDEBUG -O0 -g
debug: clean $(OUTPUT)

clean:
	rm -f $(OBJ) $(OUTPUT)