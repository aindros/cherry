# ------------------------------------------------------------------------------
#  Sample Application makefile
#
#  Author: Alessandro Iezzi info@alessandroiezzi.it
#  Date  : 2020-05-06
#
#  Changelog:
#    2020-05-06 - first version
# ------------------------------------------------------------------------------

SRC=src
OBJ=build
BIN=bin

RM=DEL /Q

CC=cl
CFLAGS=/c /I..\..\bin\include

LINKER=link
LFLAGS=/DLL

application.exe: application.obj
	$(LINKER) /out:application.exe application.obj /LIBPATH:"..\..\bin\lib" cherry.lib
	copy ..\..\bin\lib\cherry.dll cherry.dll

application.obj: application.c
	$(CC) $(CFLAGS) application.c /Fo"application.obj"

clean:
	if exist application.obj $(RM) *.obj
	if exist application.exe $(RM) *.exe
	if exist cherry.dll $(RM) *.dll
