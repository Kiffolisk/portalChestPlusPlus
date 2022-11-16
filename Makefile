# A simple Makefile for compiling small SDL projects

# set the compiler
CC := g++

# set the compiler flags
CFLAGS := -ggdb3 -O0 -Wall -lm -lncurses
# add header files here
HDRS := include/*.hpp

# add source files here
SRCS := src/*.cpp

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := portalChestPlusPlus

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	@$(CC) -o $@ $(OBJS) $(CFLAGS)
	@./$(EXEC)

# recipe for building object files
#$(OBJS): $(@:.o=.c) $(HDRS) Makefile
#    $(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean