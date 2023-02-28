# Team #4546
#
# Authors:
# 	- Mehdi Benouhoud
# 	- Laurent Bourgon
# 	- Ihsane Majdoubi
# 	- Catalina-Andrea Araya-Figueroa
#
# Date: February 28th, 2023

# Making PHONY targets
.PHONY: all build clean

# Library variables

# Library name
LIB=library

# ==== INCLUDE C++ SOURCES HERE ====
CPP-SOURCES=led.cpp

# Compiler options
COMPILER=avr-gcc
CPP-VERSION=c++14
MCU=atmega324pa

# Linker options
LINKER=avr-ar
LINKER-OPTIONS=crs
OBJECT-FILES=$(CPP-SOURCES:.cpp=.o)
LIBRARY-FILE=$(LIB).a

# File clean options
REMOVE=rm
REMOVE-FLAGS=-f
ARTIFACTS=$(OBJECT-FILES) $(LIBRARY-FILE)

all: build

build:
	@echo [$(LIB)] Compiling library...
	$(COMPILER) -I. -std=$(CPP-VERSION) -mmcu=$(MCU) -c $(CPP-SOURCES) 
	@echo [$(LIB)] Compiled .o files
	@echo [$(LIB)] Linking/archiving links...
	$(LINKER) $(LINKER-OPTIONS) $(LIBRARY-FILE) $(OBJECT-FILES)
	@echo [$(LIB)] Linked/archived links into $(LIBRARY-FILE)
clean:
	@echo [$(LIB)] Cleaning files...
	rm -f $(ARTIFACTS)
	@echo [$(LIB)] Cleaned files
