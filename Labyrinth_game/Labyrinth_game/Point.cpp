#include "Point.h"

bool Point::operator==(const Point& p) {
	if (p.x == x && p.y == y)
		return true;
	return false;
}

bool Point::operator!=(const Point& p) {
	return !(p.x == x && p.y == y);
}