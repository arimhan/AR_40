#include "Point.h"


APoint& APoint::operator++(void)
{
	++x, ++y;
	return *this;
}
APoint& APoint::operator++(int)
{
	APoint temp = *this;
	++x, ++y;
	return temp;
}

APoint APoint::operator+(const APoint& pt) const
{
	return APoint(x + pt.x, y + pt.y);
}
APoint APoint::operator-(const APoint& pt) const 
{
	return APoint(x - pt.x, y - pt.y);
}
APoint APoint::operator*(const APoint& c);
APoint APoint::operator/(const APoint& c);

APoint APoint::operator*(int mag) const
{
	return APoint(x * mag, y * mag);
}
APoint APoint::operator/(int div) const
{
	return APoint(x / div, y / div);
}

APoint operator*(int mag, const APoint& pt)
{
	return APoint(pt.x * mag, pt.y * mag);
}

APoint operator/(int div, const APoint& pt)
{
	return APoint(pt.x / div, pt.y / div);
}

APoint& APoint::operator=(const APoint& pt)
{
	x = pt.x; y = pt.y;
	return *this;
}
APoint& APoint::operator+=(const APoint& pt)
{
	x += pt.x; y += pt.y;
	return *this;
}
APoint& APoint::operator-=(const APoint& pt)
{
	x -= pt.x; y -= pt.y;
	return *this;
}
APoint& APoint::operator*=(const APoint& pt)
{
	x *= pt.x; y *= pt.y;
	return *this;
}
APoint& APoint::operator/=(const APoint& pt)
{
	x /= pt.x; y /= pt.y;
	return *this;
}
APoint& APoint::operator*=(int mag)
{
	x *= mag; y *= mag;
	return *this;
}
APoint& APoint::operator/=(int div)
{
	x /= div; y /= div;
	return *this;
}

bool APoint::operator==(const APoint& pt) const
{
	return (x == pt.x && y == pt.y);
}
bool APoint::operator!=(const APoint& pt) const
{
	return (x != pt.x || y != pt.y);
}

//¿Œµ¶ΩÃ √≥∏Æ p6[1] , p6(1)
int& operator[](int index);
int& operator()(int index);

void* operator new(size_t size);
void operator delete(void* p);

friend ostream& operator<< (ostream& os, const APoint& pt);
friend istream& operator>> (istream& is, APoint& pt);