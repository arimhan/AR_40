#pragma once
#include "Core.h"
#include "DxObject.h"
class Sample :public ACore
{
	vector<ADxObject> m_ObjectList;
public:
	//Core 상속받아 사용
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	Sample();
	~Sample();
};
