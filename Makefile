# Only works on linux
CC=g++
CFLAGS=-c -Wall 
LDFLAGS= -lglut -lGL -lGLU
SOURCES=project2.cpp Camera.cpp Robot.cpp BodyPart.cpp stb_image.c Util.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=project2

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm *.o $(EXECUTABLE)