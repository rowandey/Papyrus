# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++23

# Source files and object files
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Output executable
TARGET = $(BIN_DIR)/papy

# Default target to build
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ_FILES) | copy-mapping-files
	$(CXX) $(OBJ_FILES) -o $@

# Rule to compile .cpp to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET) $(BIN_DIR)/mappingFiles

# Rebuild the project
rebuild: clean all

# Install (optional, you can customize)
install:
	# commands to install the program, e.g. copy the binary to a directory
	cp $(TARGET) /usr/local/bin/

.PHONY: all clean rebuild install copy-mapping-files
