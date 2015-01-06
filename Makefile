# Source filenames
FILES = robotlogic/robotlogic

# Source files with .o suffix
OBJECTS = $(addsuffix .o,$(FILES))

# Assembles object files into robotlogic.dll
simulation/robotlogic.dll: $(OBJECTS)
	gcc -DNOTARDUINO -shared $^ -o $@

# Compiles source files into object files
$(OBJECTS): %.o : %.c %.h
	gcc -DNOTARDUINO -c $< -o $@
