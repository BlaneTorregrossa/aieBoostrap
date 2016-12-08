#pragma once
#include <iostream>

/*
Currently working on:
Fixing problems with classes in the Math Libraries Vectors

Stopping point was:
Creating the functions for the Vector classes
*/

/*
v = Vectors		m = matrix		f = float
v = v + v		v = v - v		v = v * f		   v = m * v		m = m * m
f = v.dot(v)	v = v.cross(v)	f = v.magnitude()  v.noramlise()
m.setRotateX(f) m.setRotateY(f) m.setRotateZ(f)		mat4 + mat3
*/

/*
NOTE:
No templating with the matracies.
Cross Product for Matracies, not Vectors.
*/

/*
Classes of Math Library (No additions to this list)
Vector2
Vector3
Vector4
Matrix2
Matrix3
Matrix4
*/

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

	// Add lerp funtion to the math libraries

	
	
};

class Vector3
{

private:
	float x, y, z;

public:
	Vector3() {};
	Vector3(float xx, float yy, float zz) {}

	Vector3 operator +(const Vector3 &T)
	{
		return Vector3(x + T.x, y + T.y, z + T.z);
	}

	Vector3 operator -(const Vector3 &T)
	{
		return Vector3(x - T.x, y - T.y, z - T.z);
	}

	Vector3 operator *(const Vector3 &T)
	{
		return Vector3(x * T.x, y * T.y, z * T.z);
	}

	// Magnitude is needed for other functions in this class to work properly.
	float Magnitude() // Function gives the squareroot of the sum of varible of type int x squared type int y squared and type int z squared.
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}
	Vector3 Normalise()
	{
		x = (x / sqrt((x * x) + (y * y) + (z * z)));
		y = (y / sqrt((x * x) + (y * y) + (z * z)));
		z = (z / sqrt((x * x) + (y * y) + (z * z)));
	}

};

class Vector4
{

private:
	float x, y, z, w;

public:
	Vector4() {};
	Vector4(float xx, float yy, float zz, float ww) {}

	Vector4 operator +(const Vector4 &T)
	{
		return Vector4(x + T.x, y + T.y, z + T.z, w + T.w);
	}

	Vector4 operator -(const Vector4 &T)
	{
		return Vector4(x - T.x, y - T.y, z - T.z, w - T.w);
	}

	Vector4 operator *(const Vector4 &T)
	{
		return Vector4(x * T.x, y * T.y, z * T.z, w * T.w);
	}

	// Magnitude is needed for other functions in this class to work properly.
	float Magnitude() // Function gives the squareroot of the sum of varible of type int x squared type int y squared type int z squared and int w squared.
	{
		return sqrt((x * x) + (y * y) + (z * z) + (w + w));
	}

	Vector4 Normalise()
	{
		x = (x / sqrt((x * x) + (y * y) + (z * z) + (w + w)));
		y = (y / sqrt((x * x) + (y * y) + (z * z) + (w + w)));
		z = (z / sqrt((x * x) + (y * y) + (z * z) + (w + w)));
		w = (w / sqrt((x * x) + (y * y) + (z * z) + (w + w)));
	}
};