#include "Vector.h"

float AVector3::operator | (AVector3 p)
{
	return x * p.x + y * p.y + z * p.z;
}
float AVector3::DotProduct (AVector3 a, AVector3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
float AVector3::Length ()
{
	float ret = x * x + y * y + z * z;
	return sqrt(ret);
}
AVector3 AVector3::Normalize()
{
	AVector3 d;
	float length = 1.0f / Length();
	d.x = d.x * length;
	d.y = d.y * length;
	d.z = d.z * length;
	return d;
}
float AVector3::ProjectionPoint(AVector3 q1, AVector3 q2, AVector3 v)
{
	AVector3 a = q2 - q1;
	AVector3 b = v - q1;
	AVector3 p = a * ((b | a) / (a | a));
	AVector3 w = b - p;
	return w.Length();
}