CXX = g++

CXX_FLAGS = -std=c++11
INCLUDE = -Iinclude/
OBJECTS = main.o

C_OS		:=
ifeq ($(OS),Windows_NT)
	C_OS += Windows
else
	C_OS += Linux
endif

all: os build trash

os:
	@echo $(C_OS)

build: $(OBJECTS)
	$(CXX) $(OBJECTS) $(INCLUDE) -o main $(CXX_FLAGS)

main.o: main.cpp
	$(CXX) $(INCLUDE) -c main.cpp $(CXX_FLAGS)

trash:
	rm -rf *.o

clean:
	rm -rf *.o main