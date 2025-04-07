# compiler
CXX = gcc

# compiler flags
CXXFLAGS = -Wall -Werror -Wextra -pedantic -g -fsanitize=address

# linker flags
LDFLAGS = -fsanitize=address -lncurses

# source files
SRC += ./MatrixMath.c
SRC += ./mml_test.c

# includes
INC_FOLDERS += ../Common/

# object files
OBJ = $(patsubst %.c, bin/%.o, $(SRC))

# final executable
EXEC = bin/a.out

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

bin/%.o: %.c | bin
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin:
	mkdir -p bin

run: $(EXEC)
	./$(EXEC)

clean:
	rm -rf $(OBJ) $(EXEC)