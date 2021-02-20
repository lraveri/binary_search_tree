CXX = c++
CXXFLAGS = -Wall -Wextra -g -std=c++11 

SRC = src/main.cpp 

EXE = $(SRC:.cpp=.x)

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