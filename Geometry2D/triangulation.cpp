#include <vector>
#include <algorithm>
#include <list>
#include <iostream>
#include "geometry2d.h"

using namespace std;

namespace geometry2d{

PolygonTriangulation::PolygonTriangulation(){
}

PolygonTriangulation::PolygonTriangulation(const vector<Point2D> & polygon) : m_p(polygon){
}

int PolygonTriangulation::getNumberOfTriangles(){
	return m_he.size() / 3;
}

vector<Point2D> PolygonTriangulation::getTriangle(int index){
	vector<Point2D> t;
	if(index >= getNumberOfTriangles())
		return t;

	t.push_back(m_p[m_he[index * 3]]);
	t.push_back(m_p[m_he[index * 3 + 1]]);
	t.push_back(m_p[m_he[index * 3 + 2]]);

	return t;
}

void PolygonTriangulation::addTriangle(int indexP0, int indexP1, int indexP2){
	m_he.push_back(indexP0);
	m_he.push_back(indexP1);
	m_he.push_back(indexP2);
}

void PolygonTriangulation::clearTriangles(){
	m_he.clear();
}

list<int>::iterator getPrevIterator(list<int> & l, list<int>::iterator & it){
	list<int>::iterator prevIterator = (it == l.begin()) ? l.end(): it;
	prevIterator--;
	return prevIterator;
}

list<int>::iterator getNextIterator(list<int> & l, list<int>::iterator & it){
	if(it == l.end())
		return l.begin();

	list<int>::iterator nextIt = it;
	nextIt++;
	return (nextIt == l.end()) ? l.begin(): nextIt;
}

int checkEar(list<int> & currPoly, list<int>::iterator & pIterator, const vector<Point2D> & p){
	list<int>::iterator prevIterator = getPrevIterator(currPoly, pIterator);
	list<int>::iterator nextIterator = getNextIterator(currPoly, pIterator);

	int p0 = *prevIterator;
	int p1 = *pIterator;
	int p2 = *nextIterator;
	if(!isLeft(p[p0], p[p1], p[p2]))
		return 0;

	list<int>::iterator currIterator = getNextIterator(currPoly, nextIterator);
	while(currIterator != prevIterator){
		int currP = *currIterator;
		if(inTriangle(p[p0], p[p1], p[p2], p[currP])){
			return 0;
		}
		currIterator = getNextIterator(currPoly, currIterator);
	}

	return 1;
}

PolygonTriangulation EarRemovalAlgorithm::triangulate(const vector<Point2D> & polygon){
	int n = polygon.size();
	PolygonTriangulation t(polygon);
	if(n < 3) return t;

	list<int> currPoly;
	vector<int> isEar(n, 0);

	for(int i=0; i<n; i++){
		currPoly.push_back(i);
	}

	for(list<int>::iterator it = currPoly.begin(); it != currPoly.end(); it++){
		int p = *it;
		isEar[p] = checkEar(currPoly, it, polygon);
	}

	while(currPoly.size() > 3){
		for(list<int>::iterator it = currPoly.begin(); it != currPoly.end(); it++){
			int p = *it;
			if(isEar[p]){
				list<int>::iterator prevIt = getPrevIterator(currPoly, it);
				list<int>::iterator nextIt = getNextIterator(currPoly, it);
				int p0 = *prevIt;
				int p1 = *it;
				int p2 = *nextIt;
				t.addTriangle(p0, p1, p2);
				currPoly.erase(it);
				isEar[p0] = checkEar(currPoly, prevIt, polygon);
				isEar[p2] = checkEar(currPoly, nextIt, polygon);
				break;
			}
		}
	}
	list<int>::iterator it = currPoly.begin();
	int p0 = *it; it++;
	int p1 = *it; it++;
	int p2 = *it;

	t.addTriangle(p0, p1, p2);

	return t;
}


}
