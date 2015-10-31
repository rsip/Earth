#####################################
#  Makefile for compiling Numerical.
#  Creates both a static and a
#  dynamic library. 
#
# Need to set up LD_LIBRARY_PATH
# for shared libraries.
#
# Will Grey
# 14 June 2015
#####################################

CC=gcc
BINDIR = bin/
SRCDIR = src/
LIBDIR = lib/
LIB = -lm
CFLAGS = -Wall -I.

SRC = leaf.c swap.c\
      flip.c utility.c
      
CSources = $(addprefix $(SRCDIR),$(SRC))

all : $(BINDIR)leaf

$(BINDIR)leaf : $(CSources)
	$(CC) $(CSources) -o $(BINDIR)leaf -Llib $(LIB) $(CFLAGS)

clean :
	rm -f $(BINDIR)leaf
	
