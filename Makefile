# Source filenames
FILES = robotlogic/robotlogic robotlogic/states

# Source files with .o suffix
OBJECTS = $(addsuffix .o,$(FILES))

ifeq ($(OS),Windows_NT)
    OUTPUT = "simulation/robotlogic.dll"
else
    OUTPUT = "simulation/robotlogic.so"
endif

# Assembles object files into robotlogic.dll/.so
$(OUTPUT): $(OBJECTS)
	gcc -DNOTARDUINO -shared -fPIC $^ -o $@

# Compiles source files into object files
$(OBJECTS): %.o : %.c %.h
	gcc -DNOTARDUINO -Wall -c -std=c99 -fPIC $< -o $@

# Runs blender simulation
simu:
	blender simulation/robotsimulation.blend

