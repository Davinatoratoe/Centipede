/*
	File: Point2D.h
	Contains: Point2D
*/

#pragma once
#include <iostream>

using namespace std;

/// <summary>
/// Simple class to represent a point in 2D space.
/// </summary>
class Point2D
{
public:
	float x;
	float y;

	Point2D() { x = 0; y = 0; }
	Point2D(float _x, float _y) { x = _x; y = _y; }
	Point2D(const Point2D& copy) { x = copy.x; y = copy.y; }
	~Point2D() {};

	Point2D& operator= (const Point2D& other) { x = other.x; y = other.y; return *this; }
	bool operator== (const Point2D& other) { return x == other.x && y == other.y; }
	bool operator!= (const Point2D& other) { return !(*this == other); }
	Point2D& operator- (const Point2D& other) { return Point2D(x - other.x, y - other.y); }
	Point2D& operator+ (const Point2D& other) { return Point2D(x + other.x, y + other.y); }
	friend ostream& operator<< (ostream& os, const Point2D& point) { os << "(" << point.x << ", " << point.y << ")"; return os; }
};
