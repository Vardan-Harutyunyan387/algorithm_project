#pragma once
class Point
{
public:
	int x, y;
	Point() :x(-1), y(-1) {};
	Point(int x, int y) : x(x), y(y) {}
	bool operator ==(const Point& c);
	bool operator !=(const Point& c);
};

