#pragma once
#include "Std.h"
//2D -> È­¸éÁÂÇ¥°è
//3D -> Á÷°¢ÁÂÇ¥°è
class ACollision
{
public:
	static bool LineToPoint(Line desk, AVector3 src) { return true; };
	static bool LineToCircle(Line desk, Sphere src) { return true; };
	static bool RectToRect(ABox desk, ABox src) { return true; };
	static bool RectToPoint(ABox desk, AVector3 src) { return true; };
	static ABox UnionRegion(const ABox& r1, const ABox& r2);
	static bool IntersectRegion(const ABox& r1, const ABox& r2, ABox* rtIntersect);
};