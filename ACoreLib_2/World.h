#pragma once
#include "Object2D.h"

class AWorld
{
public:
	enum AWorldID { A_LOADING, A_LOGIN, A_LOBBY, A_ZONE, A_RESULT, };
	ID3D11Device*			m_pd3dDevice;	//디바이스 객체
	ID3D11DeviceContext*	m_pContext;		//디바이스 컨텍스트 객체
	static AWorld*			m_pCurWorld;	//현재 map
	bool					m_bLoadWorld = false;

public:
	vector <shared_ptr<AObject2D>>	m_UIObj;
	vector <shared_ptr<AObject2D>>	m_ItemObj;
	vector <shared_ptr<AObject2D>>	m_NpcObj; // npc, player
	vector <shared_ptr<AObject2D>>	m_MapObj;
	using m_woridIter = vector <shared_ptr<AObject2D>>::iterator;

public:
	//객체화 될 수 없음, true(0)
	virtual bool	Load(wstring saveFile);
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release(); //재정의

	AWorld();
	virtual ~AWorld();
};


