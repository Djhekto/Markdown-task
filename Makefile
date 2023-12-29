#
CXX = g++
CXX_FLAGS = -g -Wall -Wextra#-I/directory/path

SOURCES =   main.cpp\
			xtextviewer.cpp\
			yabstract.cpp\
			zcode.cpp\
			zheader.cpp\
			zlist.cpp\
			ztext.cpp\

OBJECTS = $(SOURCES:.cpp=.o)

GENERATES = $(OBJECTS) prog

prog:		$(OBJECTS)
			$(CXX) $(CXX_FLAGS) $^ -o $@

%.o:		%.cpp
			$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
		rm -f $(GENERATES)