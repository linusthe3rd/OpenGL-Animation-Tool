# Only works on linux
CC=g++
CFLAGS=-c -Wall 
LDFLAGS= -lglut -lGL -lGLU
SOURCES=homework4.cpp Camera.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=project1

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm *.o $(EXECUTABLE)