CC = gcc
CFLAGS = -Wall -Iinclude
SRC_DIR = src
OBJ_DIR = obj

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
# List of object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
# Output executable
TARGET = school_management.exe

# Create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
