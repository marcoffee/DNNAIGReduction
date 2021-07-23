ifndef CCACHE_BASEDIR
export CCACHE_BASEDIR=$(shell pwd)
export CCACHE_NOHASHDIR=1
endif

CCACHE_BIN :=

ifndef CCACHE_DISABLE
CCACHE_BIN := $(shell which ccache)
endif

SHELL      := /bin/sh

CXX        ?= g++
CXX        := $(CCACHE_BIN) $(CXX)
CXXFLAGS   := $(THIRDFLAGS) \
							-fPIC -std=c++20 -O3 -fopenmp -Wall -fvisibility=hidden -Wfatal-errors \
							-fdiagnostics-color=always -Wno-unused-command-line-argument

SRC        := AIG.cpp aigraph.cpp AND.cpp input.cpp latch.cpp main.cpp mnist.cpp nodeAig.cpp \
							output.cpp synthesizer.cpp
OBJ        := $(patsubst %.cc,%.o,$(patsubst %.cpp,%.o,$(SRC)))

dnna: Makefile $(OBJ)
	$(CXX) $(OBJ) -o dnna

clean:
	$(RM) $(OBJ)
