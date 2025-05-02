# compiler
CXX = gcc

# compiler flags
CXXFLAGS = -Wall -Werror -Wextra -pedantic -g -fsanitize=address $(addprefix -I,$(INC_FOLDERS))

# linker flags
LDFLAGS = -fsanitize=address

# source files
SRC += ./src/Lab06_main.c
SRC += ./src/LinkedList.c
#SRC += ./src/LinkedListTest.c
SRC += ./src/sort.c
SRC += ./src/stopwatch.c
SRC += ../Common/BOARD.c

# includes
INC_FOLDERS += ../Common/
INC_FOLDERS += ./include/

# object files
OBJ = $(foreach src,$(SRC),bin/$(notdir $(src:.c=.o)))

# final executable
EXEC = ./bin/a.out

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

bin/%.o: ./src/%.c | bin
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/%.o: ../Common/%.c | bin
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin:
	mkdir -p bin

run: $(EXEC)
	./$(EXEC)

clean:
	rm -rf $(OBJ) $(EXEC)