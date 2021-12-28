#pragma once
#include "Core.h"
class Sample :public ACore
{
public:
	//Core 상속받아 사용
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	Sample();
	~Sample();
};
