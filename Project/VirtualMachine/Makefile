#
# COMPILER OPTIONS
#
CC = g++
C_EXT =.cpp
C_FLAGS = -Wall -g

#
# MAIN DIRECTORIES
#
BIN_DIR =    bin
TEMP_DIR =   temp
TEST_DIR =   test
SOURCE_DIR = src
BUILD_DIR =  build
HEADER_DIR = include

#
# MAIN TARGETS
#
TARGET =  $(BIN_DIR)/runner
TARGET_TEST = $(BIN_DIR)/tester

#
# GENERAL DEPENDENCIES
#
TESTS =   $(wildcard $(TEST_DIR)/*$(C_EXT))
SOURCES = $(wildcard $(SOURCE_DIR)/*$(C_EXT))
OBJECTS = $(patsubst $(SOURCE_DIR)/%, $(BUILD_DIR)/%, $(SOURCES:$(C_EXT)=.o))
OBJECTS_TEST = $(patsubst $(TEST_DIR)/%, $(BUILD_DIR)/%, $(TESTS:$(C_EXT)=.o))

#
# TARGET'S RECIPE
#
$(TARGET): $(OBJECTS)
	$(CC) $(C_FLAGS) $^ -o $@

$(TARGET_TEST): $(filter-out $(BUILD_DIR)/main.o, $(OBJECTS)) $(OBJECTS_TEST)
	$(CC) $(C_FLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%$(C_EXT) 
	$(CC) $(C_FLAGS) -I $(HEADER_DIR) -c -o $@ $<

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%$(C_EXT)
	$(CC) $(C_FLAGS) -I $(HEADER_DIR) -c -o $@ $<

all: $(TARGET)

test: $(TARGET_TEST)
	$(TARGET_TEST)

project:
	mkdir -p $(TEST_DIR) $(SOURCE_DIR) $(BUILD_DIR);
	mkdir -p $(HEADER_DIR) $(BIN_DIR) $(TEMP_DIR)

clean:
	@echo Cleaning...
	$(RM) $(BUILD_DIR)/* $(BIN_DIR)/*

.PHONY: all test project clean

.SILENT: project