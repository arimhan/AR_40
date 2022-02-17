#pragma once
#include "Object2D.h"
class AObjectNpc2D : public AObject2D
{
public:
	bool Frame() override;
	void HitOverlap(ABaseObject* pObj, DWORD dwState);
	void HitSelect(ABaseObject* pObj, DWORD dwState);
	AObjectNpc2D();
	virtual ~AObjectNpc2D();
};

