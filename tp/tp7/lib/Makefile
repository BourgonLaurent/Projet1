# Build library
#
# Team #4546
# 	Catalina Andrea Araya Figueroa
# 	Mehdi Benouhoud
# 	Laurent Bourgon
# 	Ihsane Majdoubi
#
# March 1, 2023
#
# all (default): build the .a of the library
# clean: remove all compilation files

##### CONFIG #####

# Name of the library (must start with 'lib')
LIBNAME=lib1900

INC=-I../

LIB=$(LIBNAME).a

# Source files
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

ARTIFACTS=$(LIB) $(OBJECTS) $(OBJECTS:.o=.d)


##### RULES #####

.PHONY: all clean

# make all (default): build library
all: $(LIB)

# Include common variables and rules
include ../../../Makefile.common

$(LIB): $(OBJECTS)
	$(ARCHIVER) $(ARCHIVERFLAGS) $(LIB) $(OBJECTS)
