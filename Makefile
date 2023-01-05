# Makefile for building embedded application.
# by Jaspreet Shergill

# Edit this file to compile extra C files into their own programs.
SOURCES = PIRmotion.h PIRmotion.c main.c led.c photo.c capture.c i2c.c
TARGET= PIRmotion


PUBDIR = $(HOME)/cmpt433/public/myApps
OUTDIR = $(PUBDIR)
CROSS_TOOL = arm-linux-gnueabihf-
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror 
# -pg for supporting gprof profiling.
CFLAGS += -pg



# Convert the targets to full-path executables to delete.
#OUTPUTS= $(addprefix $(OUTDIR)/, $(TARGETS))

all: $(SOURCES)
	$(CC_C) $(CFLAGS) $(SOURCES) -o $(OUTDIR)/$(TARGET) -lpthread

clean:
	rm -f $(OUTPUTS)
