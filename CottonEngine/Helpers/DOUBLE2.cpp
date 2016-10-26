#include "DOUBLE2.h"

DOUBLE2::DOUBLE2() : x(0), y(0)
{}

DOUBLE2::DOUBLE2(double x, double y) : x(x), y(y)
{}

DOUBLE2& DOUBLE2::operator=(const DOUBLE2& other)
{
	if (&other != this)			// check for self assignment
	{
		x = other.x;
		y = other.y;
	}

	return *this;
}

DOUBLE2 DOUBLE2::operator+(DOUBLE2 other)
{
	return DOUBLE2(x + other.x, y + other.y);
}

DOUBLE2 DOUBLE2::operator-(DOUBLE2 other)
{
	return DOUBLE2(x - other.x, y - other.y);
}

DOUBLE2 DOUBLE2::operator-()
{
	return DOUBLE2(-x, -y);
}

DOUBLE2 DOUBLE2::operator+()
{
	return *this;
}

DOUBLE2 DOUBLE2::operator*(double factor)
{
	return DOUBLE2(x * factor, y * factor);
}

DOUBLE2 DOUBLE2::operator*(DOUBLE2 other)
{
	return DOUBLE2(x * other.x, y * other.y);
}

DOUBLE2 DOUBLE2::operator/(double divisor)
{
	return DOUBLE2(x / divisor, y / divisor);
}

DOUBLE2& DOUBLE2::operator+=(DOUBLE2 other)
{
	x += other.x;
	y += other.y;

	return *this;
}

DOUBLE2& DOUBLE2::operator-=(DOUBLE2 other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

DOUBLE2& DOUBLE2::operator*=(double factor)
{
	x *= factor;
	y *= factor;

	return *this;
}

DOUBLE2& DOUBLE2::operator/=(double divisor)
{
	x /= divisor;
	y /= divisor;

	return *this;
}

bool DOUBLE2::operator==(DOUBLE2 other)
{
	return x == other.x && y == other.y;
}

bool DOUBLE2::operator!=(DOUBLE2 other)
{
	return !(*this == other);
}