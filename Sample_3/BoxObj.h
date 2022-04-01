#pragma once
#include "Object3D.h"

class ABoxObj : public AObject3D
{
public:
	ATexture*		m_pTexCube;
public:
	virtual bool	SetVertexData();
	virtual bool	SetIndexData();
	bool			PostRender();
public:
	ABoxObj();
	virtual ~ABoxObj();
};

