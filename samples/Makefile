CC=g++
CFLAGS=-c -std=c++11 -Wall -I../ouzel -Winvalid-pch -include linux/Prefix.h
LDFLAGS=-L../build -louzel -lX11 -lGL
SOURCES=Application.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=samples

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(EXECUTABLE) *.o