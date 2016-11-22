#####################################
#  Makefile for compiling earth.
#
# OBJ_SRC = $(patsubst $(SRC_PATH)%,$(OBJ_PATH)%,$(OBJ)) 
# OBJECTS = $(patsubst $(NUM_PATH)%,$(OBJ_PATH)%,$(OBJ_SRC)) 

# OBJ=$(SRC:.c=.o)
# $(TARGET) : $(OBJ) 
#	$(CC) $^ -o $@ $(CFLAGS)
#
#  DEP := $(OBJECTS:.o=.d)
#  DEP := $(addprefix $(OBJ_PATH),$(OBJECTS:.o=.d))
#  -include $(addprefix $(OBJ_PATH),$(DEP))
#  -include $(DEP)
#
# Will Grey
# v1: 18 Nobember 2015
# v2: 16 October 2016
#####################################

CC=gcc
BIN_PATH = bin/
SRC_PATH = src/
OBJ_PATH = obj/
NUM_PATH = numerical/
HDR_PATH = header/
TARGET = $(BIN_PATH)earth
CFLAGS = -Wall -Iheader -lm -MMD -MP

VPATH = $(SRC_PATH):$(HDR_PATH):$(NUM_PATH):$(OBJ_PATH)
OUTPUT_OPTION = -o $(OBJ_PATH)$@
SRC=$(wildcard $(SRC_PATH)*.c $(NUM_PATH)*.c)
OBJECTS = $(notdir $(SRC:.c=.o))
OBJ = $(addprefix $(OBJ_PATH),$(OBJECTS)) 
DEP=$(wildcard $(HDR_PATH)*.h)

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJ) $(CFLAGS)

# This is run implicitly 
# so not strictly necessary
%.o : %.c $(DEP)
	$(CC) $(CFLAGS) -o $(OBJ_PATH)$@ -c $<

.PHONEY: clean debug

clean :
	rm -f $(TARGET) $(OBJ) $(addprefix $(OBJ_PATH),$(OBJECTS:.o=.d))

debug :
	@echo $(OBJECTS)	
