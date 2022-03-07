#pragma once
#include "State.h"
class AStateStop : public AState
{
public:
	virtual void Process(AObject2D * pPlayer) override;
	AStateStop(AObjectAI* owner) : AState(owner) {}
};

