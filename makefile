###
### Attempt OS-detection.
###
ifeq ($(OS), Windows_NT)
OSNAME = WINDOWS
else ifeq ($(shell uname),Darwin)
OSNAME = MAC
else
OSNAME = LINUX
endif

###
### Files.
###
SRC_PATH = .
SOURCES := $(wildcard $(SRC_PATH)/*.c)
OBJECT_PATH = objects
OBJECTS := $(patsubst $(SRC_PATH)/%.c, $(OBJECT_PATH)/%.o, $(SOURCES))

###
### Compiler.
###
CC = gcc
CFLAGS = -Ofast -Wformat=2 -Wall -Wextra -Wpedantic -std=c99 -D_POSIX_C_SOURCE=199309L
ALLFLAGS = $(CFLAGS)

###
### Compiler flags.
###
CXXFLAGS = -std=c99 -D_POSIX_C_SOURCE=199309L -Ofast -march=native -flto
CXXFLAGS += -Wall -Wextra -Wpedantic -Wconversion -Wshadow
CXXFLAGS += -DNDEBUG

###
### Linked library flags.
###
LDLIBS =

###
### Executable.
###
pgnstats : $(OBJECTS)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

$(OBJECT_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CXXFLAGS) -I$(SRC_PATH) -c $< -o $@
	
all: pgnstats

###
### Cleaning build.
###
ifeq ($(OSNAME), WINDOWS)
CLEAN_COMMAND = del /s pgnstats.exe $(OBJECT_PATH)\*.o
else
CLEAN_COMMAND = rm pgnstats $(OBJECT_PATH)/*.o
endif

clean:
	$(CLEAN_COMMAND)

.PHONY: clean
