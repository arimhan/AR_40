#pragma once
#include "Object2D.h"
class APlayerObj2D : public AObject2D
{
public:
	bool Frame() override;
	virtual void HitOverlap(ABaseObject* pObj, DWORD dwState);
public:
	APlayerObj2D();
	virtual ~APlayerObj2D();
};

