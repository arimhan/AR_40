#pragma once
#include "Object2D.h"
class AWorld
{
public:
	enum AWorldID{ M_LOADING, M_LOGIN, M_LOBBY, M_ZONE, M_RESULT, };
	ID3D11Device*		 m_pd3dDevice;	// 디바이스 객체
	ID3D11DeviceContext* m_pContext;// 디바이스 컨텍스트 객체
	bool							m_bLoadWorld = false;
public:
	static AWorld*					m_pCurWorld;
	vector<shared_ptr<AObject2D>> m_UIObj;
	vector<shared_ptr<AObject2D>> m_ItemObj;
	vector<shared_ptr<AObject2D>> m_NpcObj;
	vector<shared_ptr<AObject2D>> m_MapObj;
	using m_mapIter = vector<shared_ptr<AObject2D>>::iterator;
public:
	virtual bool	Load(wstring saveFile);
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
public:
	AWorld();
	virtual ~AWorld();
};

