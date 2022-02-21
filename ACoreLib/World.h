#pragma once
//#include "Std.h"
#include "Object2D.h"
class AWorld
{
public:
	enum AWorldID { A_LOADING, A_LOGIN, A_LOBBY, A_ZONE, A_RESULT, };
	static AWorld*					m_pCurWorld; //현재 map

	ID3D11Device*					m_pd3dDevice;	//디바이스 객체
	ID3D11DeviceContext*			m_pContext;		//디바이스 컨텍스트 객체

	map <wstring, AObject2D*>		m_UIObj;
	map <wstring, AObject2D*>		m_ItemObj;
	map <wstring, AObject2D*>		m_CharactorObj; // npc, player
	map <wstring, AObject2D*>		m_MapObj;
	using m_woridIter = map<wstring, AObject2D*>::iterator;

public:
	//객체화 될 수 없음, true(0)
	virtual bool	Load(wstring saveFile);
	virtual bool	Init() = 0;
	virtual bool	Frame() = 0;
	virtual bool	Render() = 0;
	virtual bool	Release(); //재정의

	AWorld();
	virtual ~AWorld();
};

