#pragma once
#include "Core.h"
#include "DxObject.h"
class Sample :public ACore
{
	vector<ADxObject> m_ObjectList;
public:
	//Core ��ӹ޾� ���
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	Sample();
	~Sample();
};
