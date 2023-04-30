# A simple Makefile for compiling small SDL projects

# set the compiler
CXX := clang

# set the compiler flags
CXXFLAGS := -L/opt/homebrew/lib -lSDL2 -I/opt/homebrew/include -D_THREAD_SAFE -ggdb3 -O0 -Wall -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm 
# add header files here
HDRS := 

INC := 

# add source files here
SRCS := main.cpp Stick.cpp Renderer.cpp Puck.cpp SoundPlayer.cpp

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := main

# default recipe
all: $(EXEC)
 
# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CXX) -o $@ $(OBJS) $(CXXFLAGS)

# recipe for building object files
#$(OBJS): $(@:.o=.c) $(HDRS) Makefile
#    $(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean