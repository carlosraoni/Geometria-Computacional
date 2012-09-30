CXX	:= g++
CXXFLAGS := -g
LIBGL=-lGL -lGLU -lglut

SRCDIR=src
BINDIR=bin
GLGUIDIR=bin/glGUI

OBJECTS:=primitives.o point2d.o point_in_polygon.o convex_hull.o triangulation.o
OBJECTSBIN:=$(BINDIR)/*.o

all: convex_hull_gl point_in_polygon_gl triangulation_gl

convex_hull_gl: $(SRCDIR)/convex_hull_gl.cpp $(OBJECTS)
	$(CXX) -o $(GLGUIDIR)/convex_hull_gl $(SRCDIR)/convex_hull_gl.cpp $(LIBGL) $(OBJECTSBIN)

point_in_polygon_gl: $(SRCDIR)/point_in_polygon_gl.cpp $(OBJECTS)
	$(CXX) -o $(GLGUIDIR)/point_in_polygon_gl $(SRCDIR)/point_in_polygon_gl.cpp $(LIBGL) $(OBJECTSBIN)

triangulation_gl: $(SRCDIR)/triangulation_gl.cpp $(OBJECTS)
	$(CXX) -o $(GLGUIDIR)/triangulation_gl $(SRCDIR)/triangulation_gl.cpp $(LIBGL) $(OBJECTSBIN)

primitives.o: $(SRCDIR)/primitives.cpp $(SRCDIR)/primitives.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/primitives.cpp -o $(BINDIR)/primitives.o

point2d.o: $(SRCDIR)/point2d.cpp $(SRCDIR)/point2d.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/point2d.cpp -o $(BINDIR)/point2d.o

point_in_polygon.o: $(SRCDIR)/point_in_polygon.cpp $(SRCDIR)/point_in_polygon.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/point_in_polygon.cpp -o $(BINDIR)/point_in_polygon.o

convex_hull.o: $(SRCDIR)/convex_hull.cpp $(SRCDIR)/convex_hull.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/convex_hull.cpp -o $(BINDIR)/convex_hull.o

triangulation.o: $(SRCDIR)/triangulation.cpp $(SRCDIR)/triangulation.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/triangulation.cpp -o $(BINDIR)/triangulation.o

clean :
	rm -rf $(OBJECTSBIN)
