CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
LDFLAGS = -lSDL2

SRCDIR = src
INCDIR = inc
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
EXECUTABLE = $(BINDIR)/maze_game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(BINDIR):
	mkdir -p $@

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
