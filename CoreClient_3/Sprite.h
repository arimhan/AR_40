#pragma once
#include "Object2D.h"
class ASprite : public AObject2D
{
public:
	float			   m_fAnimTime;
	std::vector<RECT>  m_rtArray;
public:
	void			SetRectSouceArray(RECT rt);
	virtual bool	Init() override;
	virtual bool	Frame()override;
	virtual bool	Render()override;
	virtual bool	Release()override;
public:
	bool	Load(ID3D11Device* pd3dDevice, std::wstring filename);
};

class ASpriteMgr : public ABaseMgr<ASprite, ASpriteMgr>
{
	friend class ASingleton<ASpriteMgr>;
public:
	ASprite*	Load(std::wstring filename) override;
private:
	ASpriteMgr() {};
public:
	~ASpriteMgr() {};
};
#define I_Sprite ASpriteMgr::Get()
