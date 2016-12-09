#pragma once
#include <iostream>


class Vector2
{

private:
	float x, y;

public:
	Vector2() {};
	Vector2(float xx, float yy) {} 

	Vector2 operator +(const Vector2 &T)
	{
		return Vector2(x + T.x, y + T.y);
	}

	Vector2 operator -(const Vector2 &T)
	{
		return Vector2(x - T.x, y - T.y);
	}

	Vector2 operator *(const Vector2 &T)
	{
		return Vector2(x * T.x, y * T.y);
	}

	Vector2 operator +=(const Vector2 &T)
	{
		return Vector2(x += T.x, y += T.y);
	}

	Vector2 operator -=(const Vector2 &T)
	{
		return Vector2(x -= T.x, y -= T.y);
	}


	// Magnitude is needed for other functions in this class to work properly.
	float Magnitude() // Function gives the squareroot of the sum of varible of type int x squared and type int y squared.
	{
		float mag = sqrt ((x * x) + (y * y));
		return mag;
	}

	// Needs to use mag to Normalise the Vector
	Vector2 Normalise()
	{
		x = (x / Magnitude());
		y = (y / Magnitude());
	}

	
	
};
