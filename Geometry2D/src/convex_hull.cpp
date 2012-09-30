#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <string>
#include "geometry2d.h"

using namespace std;

namespace geometry2d{

void GrahamScanAlgorithm::convexHull(vector<Point2D> & p){
	polarAngleSort(p);

	int n = p.size();
	int convHullSize = 2;
	for(int i=2; i<n; i++){
		while(convHullSize >= 2 && !isLeft(p[convHullSize - 2], p[convHullSize - 1], p[i])){
			convHullSize--;
		}
		p[convHullSize++] = p[i];
	}
	p.resize(convHullSize);

}

bool leftBottomCompare(const Point2D & p1, const Point2D & p2){
	if(p1.getX() < p2.getX())
		return true;
	if(p1.getX() > p2.getX())
		return false;
	return p1.getY() < p2.getY();
}

int nextCW(int index, int n){
	return (index == 0) ? n-1: index - 1;
}

int nextCCW(int index, int n){
	return (index + 1) % n;
}

int findIndexRighMostPoint(const vector<Point2D> & p){
	int n = p.size(), index = 0;
	for(int i=1; i<n; i++){
		if(p[i].getX() > p[index].getX())
			index = i;
	}
	return index;
}

int findIndexLeftMostPoint(const vector<Point2D> & p){
	int n = p.size(), index = 0;
	for(int i=1; i<n; i++){
		if(p[i].getX() < p[index].getX())
			index = i;
	}
	return index;
}

bool isLeftOriented(const Point2D & p0, int indexP1, const vector<Point2D> & p){
	int n = p.size();
	return isLeft(p0, p[indexP1], p[nextCCW(indexP1, n)]) && isLeft(p0, p[indexP1], p[nextCW(indexP1, n)]);
}

bool isRightOriented(const Point2D & p0, int indexP1, const vector<Point2D> & p){
	int n = p.size();
	return !isLeft(p0, p[indexP1], p[nextCCW(indexP1, n)]) && !isLeft(p0, p[indexP1], p[nextCW(indexP1, n)]);
}

pair<int, int> findUpperTangent(int idxRightMost, int idxLeftMost,
								 const vector<Point2D> & leftCH, const vector<Point2D> &rightCH){
	int nl = leftCH.size();
	int nr = rightCH.size();

	int indexPLeft = idxRightMost;
	int indexPRight = idxLeftMost;

	while(!(isLeftOriented(rightCH[indexPRight], indexPLeft, leftCH) &&
			 isRightOriented(leftCH[indexPLeft], indexPRight, rightCH))){

		while(!isLeftOriented(rightCH[indexPRight], indexPLeft, leftCH)){
			indexPLeft = nextCCW(indexPLeft, nl);
		}
		while(!isRightOriented(leftCH[indexPLeft], indexPRight, rightCH)){
			indexPRight = nextCW(indexPRight, nr);
		}
	}

	return pair<int, int>(indexPLeft, indexPRight);
}

pair<int, int> findLowerTangent(int idxRightMost, int idxLeftMost,
								 const vector<Point2D> & leftCH, const vector<Point2D> &rightCH){
	int nl = leftCH.size();
	int nr = rightCH.size();

	int indexPLeft = idxRightMost;
	int indexPRight = idxLeftMost;

	while(!(isRightOriented(rightCH[indexPRight], indexPLeft, leftCH) &&
			 isLeftOriented(leftCH[indexPLeft], indexPRight, rightCH))){

		while(!isRightOriented(rightCH[indexPRight], indexPLeft, leftCH)){
			indexPLeft = nextCW(indexPLeft, nl);
		}
		while(!isLeftOriented(leftCH[indexPLeft], indexPRight, rightCH)){
			indexPRight = nextCCW(indexPRight, nr);
		}
	}

	return pair<int, int>(indexPLeft, indexPRight);
}

void insertPointsInCCW(vector<Point2D> & ch, int ini, int end, const vector<Point2D> & p){
	int n = p.size();
	int index = ini;
	while(index != end){
		ch.push_back(p[index]);
		index = nextCCW(index, n);
	}
	ch.push_back(p[index]);
}

vector<Point2D> mergeCH(const vector<Point2D> & leftCH, const vector<Point2D> & rightCH){
	vector<Point2D> ch;

	int idxLeftMost = findIndexLeftMostPoint(rightCH);
	int idxRightMost = findIndexRighMostPoint(leftCH);

	pair<int, int> upperTangent = findUpperTangent(idxRightMost, idxLeftMost, leftCH, rightCH);
	pair<int, int> lowerTangent = findLowerTangent(idxRightMost, idxLeftMost, leftCH, rightCH);

	insertPointsInCCW(ch, upperTangent.first, lowerTangent.first, leftCH);
	insertPointsInCCW(ch, lowerTangent.second, upperTangent.second, rightCH);

	return ch;
}

vector<Point2D> divideAndConquerConvexHull(vector<Point2D> p){
	int n = p.size();
	if(n <= 2){
		return p;
	}
	else if(n == 3){
		if(!isLeft(p[0], p[1], p[2]))
			swap(p[1], p[2]);
		return p;
	}

	int middle = n / 2;

	vector<Point2D> leftP(p.begin(), p.begin() + middle);
	vector<Point2D> rightP(p.begin() + middle, p.end());

	vector<Point2D> leftCH = divideAndConquerConvexHull(leftP);
	vector<Point2D> rightCH = divideAndConquerConvexHull(rightP);

	return mergeCH(leftCH, rightCH);
}

void DivideAndConquerConvexHullAlgorithm::convexHull(vector<Point2D> & p){
	sort(p.begin(), p.end(), leftBottomCompare);

	vector<Point2D> ret = divideAndConquerConvexHull(p);

	p.clear();
	p.insert(p.begin(),ret.begin(), ret.end());
}

}
