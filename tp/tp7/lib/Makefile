# Build library.
#
# Team #4546
# 	Catalina Andrea Araya Figueroa
# 	Mehdi Benouhoud
# 	Laurent Bourgon
# 	Ihsane Majdoubi
#
# March 1, 2023
#
# Rules:
# 	make all (default): build the library
# 	make clean: remove compilation artifacts


##### CONFIG #####

# Name of the library (must start with 'lib')
LIBNAME=lib1900

INC=-I../

LIB=$(LIBNAME).a

# Source files
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

ARTIFACTS=$(LIB) $(OBJECTS) $(OBJECTS:.o=.d)

# Archiver
ARCHIVER=avr-ar
ARCHIVERFLAGS=-crs

##### RULES #####

.PHONY: all clean

# make all (default): build library
all: $(LIB)

# Include common variables and rules
include ../../../Makefile.common

$(LIB): $(OBJECTS)
	$(ARCHIVER) $(ARCHIVERFLAGS) $(LIB) $(OBJECTS)
