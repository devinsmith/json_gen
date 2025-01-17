# Makefile for tfstool

.PHONY: all clean

SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

CC = gcc
CXX? = g++

# Dependencies
DEP_INCLUDES = $(shell pkg-config libcjson --cflags)
DEP_LIBS = $(shell pkg-config libcjson --libs)

CFLAGS = -Wall -O3 -I.

EXE = json_gen

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CFLAGS) -o $(EXE) $(OBJS) $(DEP_LFLAGS) $(DEP_LIBS)

.cpp.o:
	$(CXX) $(CFLAGS) $(DEP_INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	rm -f $(OBJS) $(EXE) $(DEPS)

# Include automatically generated dependency files
-include $(DEPS)
