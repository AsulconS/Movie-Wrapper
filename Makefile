CXX = g++

CXX_STANDARD        = -std=c++11
CXX_STANDARD_FLAGS  = -Wall -Wextra
CXX_EXTRA_FLAGS     = -Wshadow -Wnon-virtual-dtor -pedantic

CXX_FLAGS = $(CXX_STANDARD) $(CXX_STANDARD_FLAGS) $(CXX_EXTRA_FLAGS)

STATIC_CXX = -static-libgcc -static-libstdc++
LINK_FLAGS = -Wl,-Bstatic -lstdc++ -lpthread

INCLUDE_PATH = -Iinclude/
OBJECTS = main.o

ifeq ($(OS),Windows_NT)
    C_OS += Windows
    LIBS += -lcurl -lz
else
    C_OS += Linux
    LIBS += -lcurl -lz
endif

all: os build trash

os:
	@printf "$(C_OS)\n"

build: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) -o main $(INCLUDE_PATH) $(LIBS) $(STATIC_CXX) $(LINK_FLAGS)

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE_PATH) -c main.cpp

trash:
	rm -rf *.o

clean:
	rm -rf *.o main
