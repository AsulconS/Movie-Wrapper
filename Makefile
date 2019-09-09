CXX = g++

CXX_FLAGS = -std=c++11
INCLUDE = -Iinclude/
OBJECTS = main.o

C_OS		:=
LIBS		:=
ifeq ($(OS),Windows_NT)
	C_OS += Windows
	LIBS += -lcurl -lz
else
	C_OS += Linux
	LIBS += -lcurl -lz
endif

all: os build trash

os:
	@echo $(C_OS)

build: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) $(INCLUDE) $(LIBS) -o main

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c main.cpp

trash:
	rm -rf *.o

clean:
	rm -rf *.o main