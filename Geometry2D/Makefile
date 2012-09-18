CXX	:= g++
CXXFLAGS := -g

OBJECTS	:= primitives.o point2d.o point_in_polygon.o convex_hull.o

all: point_in_polygon_test convex_hull_test

point_in_polygon_test: point_in_polygon_test.cpp $(OBJECTS)
	$(CXX) $(OBJECTS) point_in_polygon_test.cpp -o point_in_polygon_test

convex_hull_test: convex_hull_test.cpp $(OBJECTS)
	$(CXX) $(OBJECTS) convex_hull_test.cpp -o convex_hull_test

primitives.o: primitives.cpp primitives.h
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c primitives.cpp -o primitives.o

point2d.o: point2d.cpp point2d.h
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c point2d.cpp -o point2d.o

point_in_polygon.o: point_in_polygon.cpp point_in_polygon.h
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c point_in_polygon.cpp -o point_in_polygon.o

convex_hull.o: convex_hull.cpp convex_hull.h
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c convex_hull.cpp -o convex_hull.o

clean :
	rm -rf $(OBJECTS)
