CC       ?= cc
CFLAGS   ?= -std=c11 -Wall -Wextra -O2 -g
CPPFLAGS ?= -Iminiaudio-0.11.25
LDLIBS   ?= -lm -lpthread -ldl

TARGET := morse2audio
SOURCES := src/main.c src/morse2audio.c miniaudio-0.11.25/miniaudio.c
OBJECTS := $(SOURCES:.c=.o)

.PHONY: all clean run help

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	$(RM) $(OBJECTS) $(OBJECTS:.o=.d)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	$(RM) $(TARGET) $(OBJECTS) $(OBJECTS:.o=.d)

help:
	@printf '%s\n' \
		'Available targets:' \
		'  all    Build the morse2audio executable (default)' \
		'  run    Run it with ARGS=<input-file>' \
		'  clean  Remove build artifacts' \
		'  help   Show this help'

-include $(OBJECTS:.o=.d)