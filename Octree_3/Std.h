#pragma once

#include<iostream>
#include<vector>
#include<list>
#include<map>
#include<string>
#include"Vector.h"
using namespace std;

#define DegreeToRadian( degree ) ((degree) * (TBASIS_PI / 180.0f))
#define RadianToDegree( radian ) ((radian) * (180.0f / TBASIS_PI))
#define randf(x) (x*rand()/(float)RAND_MAX)
#define randf2(x,off) (off+x*rand()/(float)RAND_MAX)
#define randstep(fMin,fMax) (fMin+((float)fMax-(float)fMin)*rand()/(float)RAND_MAX)
#define clamp(x,MinX,MaxX) if (x>MaxX) x=MaxX; else if (x<MinX) x=MinX;

//화면좌표계
static const float T_EPSILON = 0.001f;
static const float T_PI = 3.141592654f;

//직각좌표계
struct ABox
{
	AVector3 vPivot;
	AVector3 vMin;
	AVector3 vMax;
	AVector3 vSize;
	AVector3 vCenter;
	
	ABox() //Rect생성 시 초기 값
	{
		vPivot = { 0,0,0 };
		vMin = { 0,0,0 };
		vMax = { 0,0,0 };
		vSize = { 0,0,0 };
		vCenter = { 0,0,0 };
	}
	ABox(AVector3 vMin, AVector3 vMax)
	{
		vCenter = (vMax + vMin) / 2.0f; //min + max값의 절반이 center값
		vSize = vMax - vCenter; // max - center 값이 size
		AVector3 vHalf = vSize / 2.0f;
		vPivot = { vCenter.x - vHalf.x, vCenter.y - vHalf.y, vCenter.z + vHalf.z };
		//vPivot이 왜 x,y값만 center를 뺀 값, z는 더한 값인가..
		this->vMin = vMin;
		this->vMax = vMax;
	}
};

struct Line
{
	//start, end로 구분해도 상관은 없음..
	//근데 점+방향(기울기)에 따라서도 Line이 되므로 없어도 됨. => direction
	AVector3 vP1;
	float vflope;
};

struct Segment
{
	AVector3 vP1;
	AVector3 vP2;
};
struct Ray //Line, Segment를 전부 Ray내 선언으로 변경해서 하나만 사용해도 됨.
{
	AVector3 vStart;
	AVector3 vDirection;
};
struct Sphere
{
	AVector3 vCenter;
	float fRadius;
};
struct Circle
{
	AVector3 vCenter;
	float fRadius;
};
