# Source filenames
FILES = robotlogic/robotlogic

# Source files with .o suffix
OBJECTS = $(addsuffix .o,$(FILES))

ifeq ($(OS),Windows_NT)
    OUTPUT = "simulation/robotlogic.dll"
else
    OUTPUT = "simulation/robotlogic.so"
endif

# Assembles object files into robotlogic.dll/.so
$(OUTPUT): $(OBJECTS)
	gcc -DNOTARDUINO -shared $^ -o $@

# Compiles source files into object files
$(OBJECTS): %.o : %.c %.h
	gcc -DNOTARDUINO -c $< -o $@
