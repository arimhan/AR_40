#pragma once
#include "Object2D.h"
class APlayerObj2D : public AObject2D
{
public:
	bool Frame() override;
	APlayerObj2D();
	virtual ~APlayerObj2D();
};

