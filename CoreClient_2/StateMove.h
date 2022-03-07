#pragma once
#include "State.h"
class AStateMove : public AState
{
public:
	virtual void Process(AObject2D* pPlayer) override;
	AStateMove(AObjectAI* owner) : AState(owner) {}
};

