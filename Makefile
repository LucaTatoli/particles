# Compilatore
CXX = g++
CC = gcc

# Flags di compilazione
CXXFLAGS = -Wall -Wextra -std=c++17 -lGL -lglfw
CFLAGS = -Wall -Wextra -std=c11

# Directory
SRC_DIR = src
BUILD_DIR = out
GLAD_DIR = glad/src

# File sorgente
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/entity/*.cpp) $(wildcard $(SRC_DIR)/shaders/*.cpp) $(wildcard $(SRC_DIR)/controller/*.cpp) $(wildcard $(SRC_DIR)/sprite/*.cpp)
GLAD_SRC = $(GLAD_DIR)/glad.c

# File oggetto
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
OBJS += $(BUILD_DIR)/glad.o

# Output
TARGET = $(BUILD_DIR)/game

# Regola principale
all: $(TARGET)

# Compilazione del progetto
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilazione dei file sorgente
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/entity
	@mkdir -p $(BUILD_DIR)/shaders
	@mkdir -p $(BUILD_DIR)/controller
	@mkdir -p $(BUILD_DIR)/sprite
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilazione di glad
$(BUILD_DIR)/glad.o: $(GLAD_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Pulizia
clean:
	rm -rf $(BUILD_DIR)

# Esegui il programma
run: all
	./$(TARGET)
