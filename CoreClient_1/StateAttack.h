#pragma once
#include "State.h"
class AStateAttack : public AState
{
public:
	virtual void Process(AObject2D* pPlayer) override;
	AStateAttack(AObjectAI* owner) : AState(owner) {}
};

