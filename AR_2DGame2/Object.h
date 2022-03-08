#pragma once
#include "Object2D.h"
#include "Input.h"

//Player, NPC

class AObjectPlayer2D : public AObject2D
{
public:
	bool			Frame();// override;
	virtual void	HitOverlap(ABaseObject* pObj, DWORD dwState);
	AObjectPlayer2D();
	virtual ~AObjectPlayer2D();
};

class AObjectNPC2D : public AObject2D
{
public:
	bool			Frame();// override;
	virtual void	HitOverlap(ABaseObject* pObj, DWORD dwState);
	virtual void	HitSelect(ABaseObject* pObj, DWORD dwState);

	AObjectNPC2D();
	virtual ~AObjectNPC2D();
};
class AObject : public ADxObject
{
public:
	int m_iExcueteCollisionID;
	int m_iExcueteSelectID;
};
