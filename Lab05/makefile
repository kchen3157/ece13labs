# compiler
CXX = gcc

# compiler flags
CXXFLAGS = -Wall -Werror -Wextra -pedantic -g -fsanitize=address $(addprefix -I,$(INC_FOLDERS))

# linker flags
LDFLAGS = -fsanitize=address -lncurses

# source files
SRC += ./Lab05_main.c
SRC += ./rpn.c
SRC += ./stack.c
# SRC += ./rpn_test.c
# SRC += ./stack_test.c
SRC += ../Common/BOARD.c

# includes
INC_FOLDERS += ../Common/

# object files
OBJ = $(foreach src,$(SRC),bin/$(notdir $(src:.c=.o)))

# final executable
EXEC = ./bin/a.out

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

bin/%.o: %.c | bin
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/%.o: ../Common/%.c | bin
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin:
	mkdir -p bin

run: $(EXEC)
	./$(EXEC)

clean:
	rm -rf $(OBJ) $(EXEC)