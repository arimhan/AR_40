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

//ȭ����ǥ��
static const float T_EPSILON = 0.001f;
static const float T_PI = 3.141592654f;

//������ǥ��
struct Box
{
	Vector3 vPivot;
	Vector3 vMin;
	Vector3 vMax;
	Vector3 vSize;
	Vector3 vCenter;
	
	Box() //Rect���� �� �ʱ� ��
	{
		vPivot = { 0,0,0 };
		vMin = { 0,0,0 };
		vMax = { 0,0,0 };
		vSize = { 0,0,0 };
		vCenter = { 0,0,0 };
	}
	Box(Vector3 vMin, Vector3 vMax)
	{
		vCenter = (vMax + vMin) / 2.0f; //min + max���� ������ center��
		vSize = vMax - vCenter; // max - center ���� size
		Vector3 vHalf = vSize / 2.0f;
		vPivot = { vCenter.x - vHalf.x, vCenter.y - vHalf.y, vCenter.z + vHalf.z };
		//vPivot�� �� x,y���� center�� �� ��, z�� ���� ���ΰ�..
		this->vMin = vMin;
		this->vMax = vMax;
	}
};

struct Line
{
	//start, end�� �����ص� ����� ����..
	//�ٵ� ��+����(����)�� ���󼭵� Line�� �ǹǷ� ��� ��. => direction
	Vector3 vP1;
	float vflope;
};

struct Segment
{
	Vector3 vP1;
	Vector3 vP2;
};
struct Ray //Line, Segment�� ���� Ray�� �������� �����ؼ� �ϳ��� ����ص� ��.
{
	Vector3 vStart;
	Vector3 vDirection;
};
struct Sphere
{
	Vector3 vCenter;
	float fRadius;
};
struct Circle
{
	Vector3 vCenter;
	float fRadius;
};
