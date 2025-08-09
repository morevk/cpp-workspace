# Compiler and flags
CXX := g++
#CXXFLAGS := -std=c++23 -Wall -I./inc -DBOOST_ASIO_DISABLE_THREADS -DBOOST_ALL_NO_LIB -DBOOST_SYSTEM_NO_DEPRECATED -DBOOST_ERROR_CODE_HEADER_ONLY -DBOOST_COROUTINES_NO_DEPRECATION_WARNING -I/usr/local/include -I/home/dev/sdbusplus/subprojects/nlohmann_json/include
CXXFLAGS := -fdiagnostics-color=always -D_GLIBCXX_ASSERTIONS=1 -D_FILE_OFFSET_BITS=64 -Wall -Winvalid-pch -Wextra -Wpedantic -Werror -std=c++23 -O2 -g -DBOOST_ASIO_DISABLE_THREADS -DBOOST_ALL_NO_LIB -DBOOST_SYSTEM_NO_DEPRECATED -DBOOST_ERROR_CODE_HEADER_ONLY -DBOOST_COROUTINES_NO_DEPRECATION_WARNING -I/usr/local/include -I/home/dev/sdbusplus/subprojects/nlohmann_json/include -I./inc 
#LINKFLAGS := -Wl,--as-needed -Wl,--no-undefined -Wl,/home/dev/sdbusplus/build/libsdbusplus.so.1.0.0  /usr/lib/x86_64-linux-gnu/libsystemd.so /usr/local/lib/libboost_coroutine.so.1.83.0 /usr/local/lib/libboost_context.so.1.83.0
LINKFLAGS := -Wl,--as-needed -Wl,--no-undefined -lsdbusplus -lsystemd
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
	$(CXX) $^ -o $@ $(LINKFLAGS)

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony target to avoid conflicts with files named clean
.PHONY: clean
