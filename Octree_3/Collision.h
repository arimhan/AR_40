#pragma once
#include "Std.h"
//2D -> ȭ����ǥ��
//3D -> ������ǥ��
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