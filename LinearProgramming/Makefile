CXX	:= g++
CXXFLAGS := -g
LIBGL=-lGL -lGLU -lglut

OBJECTS:=constraint2d.o linear_program2d.o lp2d_reader.o lp2d_solver.o

all: linearProgramming linearProgrammingGl

linearProgrammingGl: linearProgrammingGl.cpp $(OBJECTS)
	$(CXX) -o lpGl linearProgrammingGl.cpp $(LIBGL) $(OBJECTS)

linearProgramming: linearProgramming.cpp $(OBJECTS)
	$(CXX) -o lp linearProgramming.cpp $(OBJECTS)

constraint2d.o: constraint2d.cpp constraint2d.h
	$(CXX) $(CXXFLAGS) -c constraint2d.cpp -o constraint2d.o

linear_program2d.o: linear_program2d.cpp linear_program2d.h
	$(CXX) $(CXXFLAGS) -c linear_program2d.cpp -o linear_program2d.o

lp2d_reader.o: lp2d_reader.cpp lp2d_reader.h
	$(CXX) $(CXXFLAGS) -c lp2d_reader.cpp -o lp2d_reader.o

lp2d_solver.o: lp2d_solver.cpp lp2d_solver.h
	$(CXX) $(CXXFLAGS) -c lp2d_solver.cpp -o lp2d_solver.o

clean :
	rm -rf $(OBJECTS)

