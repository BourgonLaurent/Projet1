# Compile C/C++ for AVR
#
# Team #4546
# 	Catalina-Andrea Araya-Figueroa
# 	Mehdi Benouhoud
# 	Laurent Bourgon
# 	Ihsane Majdoubi
#
# Requirements:
# 	`make clean`: set ARTIFACTS
#		ex. ARTIFACTS=$(OBJECTS) $(OBJECTS:.o=.d)
#	`make install`: set HEXTRG
#		ex. HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex
#
# March 1, 2023

#####      Details specifique a la cible       #####

# Project name (in one word)
PROJECTNAME=TP7_exec

# Source files (delimiter: space)
PRJSRC=main.cpp

# Additional inclusions (ex: -I/path/to/mydir)
INC=-I../../

# Librairies (ex: -lmylib)
LIBS=-l1900 -L ../lib

####### Target #######

TRG=$(PROJECTNAME).elf
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex

####### Objects #######

# C
CFILES=$(filter %.c, $(PRJSRC))
# C++
CPPFILES=$(filter %.cpp, $(PRJSRC))

# All Objects
OBJDEPS=$(CFILES:.c=.o) \
	$(CPPFILES:.cpp=.o)

# will be removed when `make clean` is run
# (delimiter: space)
ARTIFACTS=$(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) $(OBJDEPS:.o=.d)

##### RULES #####

.PHONY: all install clean
all: $(TRG) $(HEXROMTRG)

# Include common variables and rules
include ../../../Makefile.common

# Implementation de la cible
$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) \
	-lm $(LIBS)
