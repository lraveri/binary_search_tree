CXX = c++
CXXFLAGS = -Wall -Wextra -I include -g -std=c++11 

SRC = main.cpp src/bst.cpp src/node.cpp src/iterator.cpp

EXE = $(SRC:.cpp=.x)

INC = include/bst.h  include/node.h  include/iterator.h include/methods.h 

all: $(EXE)

.PHONY: all

%.x: %.cpp 
	$(CXX) $< -o $@ $(CXXFLAGS)

format: $(SRC)
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this command"

.PHONY: format

clean:
	rm -f $(EXE) *~

.PHONY: clean