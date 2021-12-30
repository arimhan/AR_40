#include "Vector.h"

// Vector2 -----------------------------------
float Vector2::operator | (Vector2 p)
{
	return x * p.x + y * p.y;
}
float Vector2::DotProduct (Vector2 a, Vector2 b)
{
	return a.x * b.x + a.y * b.y;
}
float Vector2::Length ()
{
	float ret = x * x + y * y;
	return sqrt(ret);
}
Vector2 Vector2::Normalize()
{
	Vector2 d;
	float length = 1.0f / Length();
	d.x = d.x * length;
	d.y = d.y * length;
	return d;
}
float Vector2::ProjectionPoint(Vector2 q1, Vector2 q2, Vector2 v)
{
	Vector2 a = q2 - q1;
	Vector2 b = v - q1;
	Vector2 p = a * ((b | a) / (a | a));
	Vector2 w = b - p;
	return w.Length();
}

// Vector3 -----------------------------------
float Vector3::operator | (Vector3 p)
{
	return x * p.x + y * p.y + p.z * z;
}
float Vector3::DotProduct(Vector3 a, Vector3 b, Vector3 c)
{
	return a.x * b.x * c.x + a.y * b.y * c.y + a.z * b.z * c.z;
}
float Vector3::Length()
{
	float ret = x * x + y * y;
	return sqrt(ret);
}
Vector3 Vector3::Normalize()
{
	Vector3 d;
	float length = 1.0f / Length();
	d.x = d.x * length;
	d.y = d.y * length;
	return d;
}
float Vector3::ProjectionPoint(Vector3 q1, Vector3 q2, Vector3 v)
{
	Vector3 a = q2 - q1;
	Vector3 b = v - q1;
	Vector3 p = a * ((b | a) / (a | a));
	Vector3 w = b - p;
	return w.Length();
}