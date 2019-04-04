/*
	File: Point2D.h
	Contains: Point2D
*/

#pragma once

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
};