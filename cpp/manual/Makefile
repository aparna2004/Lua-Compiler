CXX = g++
CXXFLAGS = -std=c++17 -g
# -Wall -Wextra -g
SOURCES = main.cpp lexer.cpp parser.cpp ast.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = minilua

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET) 

.PHONY: all clean

# Dependencies
main.o: main.cpp lexer.h parser.h ast.h
lexer.o: lexer.cpp lexer.h
parser.o: parser.cpp parser.h ast.h
ast.o: ast.cpp ast.h