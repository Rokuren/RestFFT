CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

SRCS=Server.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: rest

rest: $(OBJS)
    $(CXX) $(LDFLAGS) -o test $(OBJS) $(LDLIBS) 

rest.o: Server.cpp Server.h

support.o: support.hh support.cc

clean:
    $(RM) $(OBJS)

dist-clean: clean
    $(RM) tool