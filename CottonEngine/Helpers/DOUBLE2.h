#pragma once

struct DOUBLE2
{
	double x;
	double y;

	DOUBLE2();
	DOUBLE2(double x, double y);

	DOUBLE2& operator=(const DOUBLE2& other);

	DOUBLE2 operator+(DOUBLE2 other);

	DOUBLE2 operator-(DOUBLE2 other);

	DOUBLE2 operator-();

	DOUBLE2 operator+();

	DOUBLE2 operator*(double factor);

	DOUBLE2 operator*(DOUBLE2 other);

	DOUBLE2 operator/(double divisor);

	DOUBLE2& operator+=(DOUBLE2 other);

	DOUBLE2& operator-=(DOUBLE2 other);

	DOUBLE2& operator*=(double factor);

	DOUBLE2& operator/=(double divisor);

	bool operator==(DOUBLE2 other);

	bool operator!=(DOUBLE2 other);
};
