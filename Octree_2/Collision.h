#pragma once
#include "Std.h"
//2D -> È­¸éÁÂÇ¥°è

class Collision2D
{
public :
//	static bool PointToPoint(Vector2 desk, Vector2 src);
//	static bool LineToLine(Line desk, Line src);
//	static bool LineToPoint(Line desk, Vector2 src);
//	static bool LineToCircle(Line desk, Circle src);
//	static bool RectToRect(Rect desk, Rect src);
//	static bool RectToPoint(Rect desk, Vector2 src); //Vector2 pos?
//	static bool CircleToCircle(Circle desk, Circle src);
//	static bool CircleToPoint(Circle desk, Vector2 src);
//	static bool UnionRegion(const Rect& r1, const Rect& r2);
//	static bool IntersectRegion(const Rect& r1, const Rect& r2, Rect* rtIntersect);
};


//3D -> Á÷°¢ÁÂÇ¥°è
class Collision
{
public:
	static bool LineToPoint(Line desk, Vector3 src) { return true; };
	static bool LineToCircle(Line desk, Sphere src) { return true; };
	static bool RectToRect(Box desk, Box src) { return true; };
	static bool RectToPoint(Box desk, Vector3 src) { return true; };
	static Box UnionRegion(const Box& r1, const Box& r2);
	static bool IntersectRegion(const Box& r1, const Box& r2, Box* rtIntersect);
};