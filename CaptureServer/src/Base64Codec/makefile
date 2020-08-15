# makefile written for gnu make
# You can change the param according your requirement.
# VPATH: The source derectory path. Multi file directorys can be
# seperated by space.
# OBJ: The "o." file need by target file.
# Of course you need not modify this file, and use the "make"
# command like this:
# make VPATH = "path1 #path2" OBJ = "main.o a.o b.o"

CC = g++
COMPILE.C =$(CC) -c

# Vitual path, provide the search path with the relied relationship.
VPATH = ./
PROINCLUDE = $(INCLUDE) -I./

#Link param
CPPFLAGS = 
DEBUG = -g
OPTIMIZE_D = #-o2
GCCWARN = -Wall
RELEASE =
OPTIMIZE_R = -O2
LINKLIB_D = 
LINKLIB_R = 
CXXFLAGS_D = $(DEBUG) $(GCCWARN) $(OPTIMIZE_D) $(PROINCLUDE) $(CPPFLAGS)
CXXFLAGS_R = $(RELEASE) $(GCCWARN) $(OPTIMIZE_R) $(PROINCLUDE) $(CPPFLAGS)
CXXFLAGS = -o

AR = ar
ARFLAGS = -rv
MAKEEXE = $(CC) $(CXXFLAGS)
MAKELIB = $(AR) $(ARFLAGS)

# The "o." file relied by target file. If you expect "o." file to 
# produce in the relied directory, you can use like: ../pub/b.o
OBJ_D = Base64CodecApi.D.o stdafx.D.o
OUTLIB_D = libBase64Codec.D.a
OBJ_R = Base64CodecApi.o stdafx.o
OUTLIB_R = libBase64Codec.a
OUTEXE = 

all: $(OUTLIB_D) $(OUTLIB_R)

# debug version
$(OUTLIB_D): $(OBJ_D)
	$(MAKELIB) $(OUTLIB_D) $(OBJ_D)
	cp ./$(OUTLIB_D) ../../../../Common/Other/Base64Codec/Linux/Debug/$(OUTLIB_D)
	cp ./Base64CodecApi.h ../../../../Common/Other/Base64Codec/Include/Base64CodecApi.h
	#now $@ is $(LIB_D)

# '$^' and '$@' is automatic variables, it can find corrording infomation
# according with variable "VPATH"

%.D.o:	%.cpp
	$(COMPILE.C) $(CXXFLAGS_D) $^ -o $@
	#now $@ is $(%.D.o)

# release version
$(OUTLIB_R): $(OBJ_R)
	$(MAKELIB) $(OUTLIB_R) $(OBJ_R)
	cp ./$(OUTLIB_R) ../../../../Common/Other/Base64Codec/Linux/Release/$(OUTLIB_R)
	cp ./Base64CodecApi.h ../../../../Common/Other/Base64Codec/Include/Base64CodecApi.h
	#now $@ is $(LIB_R)

# '$^' and '$@' is automatic variables, it can find corrording infomation
# according with variable "VPATH"

%.o:	%.cpp
	$(COMPILE.C) $(CXXFLAGS_R) $^ -o $@
	#now $@ is $(%.o)

.PHONY clean:
	-rm -f $(OUTLIB_D) $(OBJ_D) $(OUTLIB_R) $(OBJ_R)
