#pragma once
#include "Object2D.h"

class APlayerObj2D :  public AObject2D
{
public:
	virtual void	HitOverlap(ABaseObject* pObj, DWORD dwState);
	bool			Frame() override;
public:
	APlayerObj2D();
	virtual ~APlayerObj2D();
};

