#pragma once
#include "math.h"

class Vector2D
{
	double x = 0;
	double y = 0;
	int identity = 0;

public:
	Vector2D() {}
	Vector2D(double x, double y, int identity = 0) { this->x = x; this->y = y;  this->identity = identity; }
	double angle()const { return atan2(y, x); }
	double length()const { return pow(pow(x, 2) + pow(y, 2), 0.5); }

	int getIdentity() { return identity; }

	bool operator> (const Vector2D& vec)const { return this->length() > vec.length(); }
	bool operator< (const Vector2D& vec)const { return this->length() < vec.length(); }
	bool operator>=(const Vector2D& vec)const { return this->length() >= vec.length(); }
	bool operator<=(const Vector2D& vec)const { return this->length() <= vec.length(); }
};

