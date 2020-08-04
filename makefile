CC = gcc
CFLAGS = -Ofast -Wformat=2 -Wall -Wextra -Wpedantic -std=c99 -D_POSIX_C_SOURCE=199309L -mpopcnt -march=native -mfpmath=sse -DNDEBUG
ALLFLAGS = $(CFLAGS)

SRC_PATH = .
OBJECT_PATH = .

SOURCES := $(wildcard $(SRC_PATH)/*.c) $(wildcard $(SRC_PATH)/*/*.c)
OBJECTS := $(patsubst $(SRC_PATH)/%.c, $(OBJECT_PATH)/%.o, $(SOURCES))

pgnstats : $(OBJECTS)
	$(CC) $(ALLFLAGS) -o $@ $^

$(OBJECT_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(ALLFLAGS) -I$(SRC_PATH) -c $< -o $@

.PHONY: clean
clean:
	rm pgnstats $(OBJECT_PATH)/*.o
