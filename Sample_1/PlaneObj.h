#pragma once
#include "Object3D.h"

class APlaneObj : public AObject3D
{
public:
	virtual bool	SetVertexData();
	virtual bool	SetIndexData();

public:
	APlaneObj();
	virtual ~APlaneObj();
};
