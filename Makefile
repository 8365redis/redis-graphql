#!/bin/bash

CURRENTDIR:=$(strip $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))
SHELL := /bin/bash
VERSION := $(shell git describe --abbrev=0 --tags)

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CPPFLAGS = -Wall -g -fPIC -std=c++11 -I$(INCDIR) -D REDIS_GRAPHQL_MODULE_VERSION=\"$(VERSION)\" -D _DEBUG -O0
else
    CPPFLAGS = -Wall -g -fPIC -std=c++11 -I$(INCDIR) -D REDIS_GRAPHQL_MODULE_VERSION=\"$(VERSION)\" -D NDEBUG -O3
endif

CC = g++
LDFLAGS = -shared -o
 
BINDIR = bin
SRCDIR = src
INCDIR = include
UNITTESTDIR = tests

SOURCES = $(shell echo src/*.cpp)
HEADERS = $(shell echo include/*.h)
OBJECTS = $(SOURCES:.cpp=.o)

MODULENAME = redis-graphql.so

TARGET  = $(BINDIR)/$(MODULENAME)

all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(TARGET) $(OBJECTS)
	rm -rf  $(SRCDIR)/*.o

.PHONY: clean load test

clean:
	rm -rf  $(SRCDIR)/*.o $(BINDIR)/*.so 
	rm -f dump.rdb

load: 
	redis-stack-server --loadmodule $(CURRENTDIR)/$(BINDIR)/$(MODULENAME)

test:
	pytest -rP

unit_test:
	g++ -std=c++11 -Wall -I$(INCDIR) $(SRCDIR)/query_parser.cpp -c
	g++ -std=c++11 -Wall query_parser.o $(UNITTESTDIR)/tests_parser.cpp -o tests_parser && ./tests_parser --reporter compact --success
	rm tests_parser
	rm query_parser.o