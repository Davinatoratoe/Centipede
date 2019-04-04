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
	float x;	//x componet
	float y;	//y component

	Point2D() { x = 0; y = 0; }		//Overloaded contructors
	Point2D(float _x, float _y) { x = _x; y = _y; }
	Point2D(const Point2D& copy) { x = copy.x; y = copy.y; }	//Copy constructor
	~Point2D() {};					//Deconstructor
	
	//Assignment operator overload
	Point2D& operator= (const Point2D& other) { x = other.x; y = other.y; return *this; }
	
	//Equal to and not equal to operator overloads
	bool operator== (const Point2D& other) const { return x == other.x && y == other.y; }
	bool operator!= (const Point2D& other) const { return !(*this == other); }
	
	//Addition and subtraction operator overloads
	Point2D operator- (const Point2D& other) const { return Point2D(x - other.x, y - other.y); }
	Point2D& operator-= (const Point2D& other) { x += other.x; y += other.y; return *this; }
	Point2D operator+ (const Point2D& other) const { return Point2D(x + other.x, y + other.y); }
	Point2D& operator += (const Point2D& other) { x -= other.x; y -= other.y; return *this; }
	
	//output stream operator overload
	friend ostream& operator<< (ostream& os, const Point2D& point) { os << "(" << point.x << ", " << point.y << ")"; return os; }
};
