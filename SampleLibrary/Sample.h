#pragma once
#include "Core.h"
class Sample :public ACore
{
public:
	//Core ��ӹ޾� ���
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	Sample();
	~Sample();
};
