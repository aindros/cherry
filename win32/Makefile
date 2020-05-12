# ------------------------------------------------------------------------------
#  Generic makefile
#
#  Author: Alessandro Iezzi info@alessandroiezzi.it
#  Date  : 2020-05-06
#
#  Changelog:
#    2020-05-06 - first version
# ------------------------------------------------------------------------------

SRC    = ..\src
OBJ    = ..\build
BIN    = ..\bin
RM     = DEL /Q
CC     = cl
CFLAGS = /c /DUNICODE /D_UNICODE
LINKER = link
LFLAGS = /DLL User32.lib

OBJECT_FILES  = $(OBJ)/cherry.obj \
                $(OBJ)/main.obj
INCLUDE_FILES = $(BIN)/include/cherry.h

$(BIN)/cherry.dll: $(BIN) $(INCLUDE_FILES) $(OBJECT_FILES)
	lib /out:$(BIN)/lib/cherry.lib $(OBJECT_FILES)
	@$(LINKER) $(LFLAGS) /out:$(BIN)/lib/cherry.dll $(OBJECT_FILES)

$(BIN)/include/cherry.h: $(SRC)/cherry.h
	copy $(SRC)\cherry.h $(BIN)\include\cherry.h

$(OBJ)/cherry.obj: $(OBJ) $(SRC)/cherry.c $(SRC)/cherry.h
	$(CC) $(CFLAGS) $(SRC)/cherry.c /Fo"$(OBJ)\cherry.obj"

$(OBJ)/main.obj: $(OBJ) main.c
	$(CC) $(CFLAGS) main.c /Fo"$(OBJ)\main.obj"

all: $(OBJ) $(BIN)

$(OBJ):
	mkdir $(OBJ)

$(BIN):
	mkdir $(BIN)
	mkdir $(BIN)\lib
	mkdir $(BIN)\include

clean:
# Remove OBJ directory
	if exist $(OBJ) $(RM) $(OBJ)
	if exist $(OBJ) rmdir /Q $(OBJ)
# Remove lib directory
	if exist $(BIN)\lib $(RM) $(BIN)\lib
	if exist $(BIN)\lib rmdir $(BIN)\lib
# Remove include directory
	if exist $(BIN)\include $(RM) $(BIN)\include
	if exist $(BIN)\include rmdir $(BIN)\include
# Remove BIN directory
	if exist $(BIN) $(RM) $(BIN)
	if exist $(BIN) rmdir /Q $(BIN)
