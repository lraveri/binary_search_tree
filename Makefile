EXE = exe.x
CXX = c++
CXXFLAGS = -I include -g -std=c++11 -Wall -Wextra -lncurses
SRC= main.cpp src/bst.cpp src/iterator.cpp src/node.cpp
OBJ=$(SRC:.cpp=.o)
INC = include/bst.h  include/node.h  include/iterator.h 

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cpp .o

all: $(EXE)

.PHONY: all

clean:
	rm -rf $(OBJ) $(EXE) src/*~ include/*~ *~ html latex

.PHONY: clean

$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE)

documentation: Doxygen/doxy.in
	doxygen $^

.PHONY: documentation

main.o: include/bst.h include/iterator.h include/node.h 

src/bst.o: include/bst.h src/bst.cpp
src/iterator.o: include/iterator.h 
src/node.o: include/node.h

format: $(SRC) $(INC)
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this commands"

.PHONY: format
