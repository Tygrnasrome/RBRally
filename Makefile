SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = $(SOURCES:.cpp=.d)
TARGET = program

CFLAGS = -ggdb -std=c++11 \
	-I C:\Users\pskop\Documents\QT\SDL-1.2.15\include \
	-I C:\Users\pskop\Documents\QT\SDL-1.2.15\include\SDL \
	-I C:\Users\pskop\Documents\QT\SDL_image-1.2.12\include \
	-I C:\Users\pskop\Documents\QT\SDL_mixer-1.2.12\include

LFLAGS = -L C:\Users\pskop\Documents\QT\SDL-1.2.15\lib \
	-L C:\Users\pskop\Documents\QT\SDL_image-1.2.12\lib\x86 \
	-L C:\Users\pskop\Documents\QT\SDL_mixer-1.2.12\lib\x86 \
	-lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ $(OBJECTS) -o $(TARGET) $(LFLAGS)

%.o: %.cpp
	g++ -MMD -MP $(CFLAGS) -c $< -o $@

-include $(DEPENDS)
