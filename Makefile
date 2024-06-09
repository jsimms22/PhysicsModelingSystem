CC = g++
CFLAGS = -std=c++17 -Wall -Wpedantic -Wshadow -Wextra 
LDFLAGS = -lglfw3 -lglew32 -lopengl32

# Path to the glfw and glew libraries
GLFW_LIB_DIR = vendor/GLFW/include
GL_LIB_DIR = vendor/GL/include

# Path to the include directories of glfw and glew
GLFW_INCLUDE_DIR = vendor/GLFW/libs
GL_INCLUDE_DIR = vendor/GL/libs

# Name of the output executable
OUTPUT = app

# Source files and object files
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L $(GLFW_LIB_DIR) -L $(GL_LIB_DIR) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I $(GLFW_INCLUDE_DIR) -I $(GL_INCLUDE_DIR)

debug: CFLAGS += -DDEBUG -O0 -g
debug: clean $(OUTPUT)

clean:
	rm -f $(OBJ) $(OUTPUT)