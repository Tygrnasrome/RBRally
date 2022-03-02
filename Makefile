ifeq ($(OS),Windows_NT)
	DIR_SEP = \\
	MKDIR = @mkdir
	LFLAGS = -L C:\Users\pskop\Documents\QT\SDL-1.2.15\lib \
		-L C:\Users\pskop\Documents\QT\SDL_image-1.2.12\lib\x86 \
		-L C:\Users\pskop\Documents\QT\SDL_mixer-1.2.12\lib\x86
	LFLAGS2 =-lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer
	CFLAGS = -ggdb -std=c++11 \
		-I C:\Users\pskop\Documents\QT\SDL-1.2.15\include \
		-I C:\Users\pskop\Documents\QT\SDL-1.2.15\include\SDL \
		-I C:\Users\pskop\Documents\QT\SDL_image-1.2.12\include \
		-I C:\Users\pskop\Documents\QT\SDL_mixer-1.2.12\include
else
	DIR_SEP = /
	MKDIR = @mkdir -p
	LFLAGS = -lglfw -lGL -lGLEW
	LFLAGS2 =
	CFLAGS = -std=c++17 -Wall -pedantic -Wno-long-long -Wno-class-memaccess -O0 -ggdb -Iinclude/glm
endif

COMPILER = g++
LINKER = g++
MODULES = src
SOURCE_DIR = .
TEMP_DIR = tmp
TARGET = program

SRC_DIR = $(addprefix $(SOURCE_DIR)$(DIR_SEP),$(MODULES))
BUILD_DIR = $(addprefix $(TEMP_DIR)$(DIR_SEP),$(MODULES))

SOURCES = $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJECTS = $(patsubst $(SOURCE_DIR)$(DIR_SEP)%.cpp,$(TEMP_DIR)$(DIR_SEP)%.o,$(SOURCES))
DEPS = $(patsubst $(SOURCE_DIR)$(DIR_SEP)%.cpp,$(TEMP_DIR)$(DIR_SEP)%.d,$(SOURCES))
INCLUDES = $(addprefix -I,$(SRC_DIR))

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(COMPILER) -MMD -MP $(CFLAGS) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: run all checkdirs clean

ifeq ($(OS),Windows_NT)
all: checkdirs $(TARGET)
else
all: checkdirs $(TARGET)
endif

run: all
	.$(DIR_SEP)$(TARGET)

$(TARGET): $(OBJECTS)
	$(LINKER) $(LFLAGS) $^ -o $(TARGET) $(LFLAGS2)

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	$(MKDIR) $@

clean:
	rm -rf $(BUILD_DIR)
	rm -f .$(DIR_SEP)$(TARGET)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))

-include $(DEPS)

