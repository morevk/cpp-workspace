# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -I./inc

# Directories
SRC_DIR := src
INCLUDE_DIR := inc
OBJ_DIR := obj
BIN_DIR := bin

# Source files
SRC := $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
# Object files
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

# Targets
TARGET := $(BIN_DIR)/main.exe

# Default target
all: $(TARGET)

# Rule for creating object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for linking the executable
$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $^ -o $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony target to avoid conflicts with files named clean
.PHONY: clean