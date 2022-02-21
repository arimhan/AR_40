#pragma once
//#include "Std.h"
#include "Object2D.h"
class AWorld
{
public:
	enum AWorldID { A_LOADING, A_LOGIN, A_LOBBY, A_ZONE, A_RESULT, };
	static AWorld*					m_pCurWorld; //���� map

	ID3D11Device*					m_pd3dDevice;	//����̽� ��ü
	ID3D11DeviceContext*			m_pContext;		//����̽� ���ؽ�Ʈ ��ü

	map <wstring, AObject2D*>		m_UIObj;
	map <wstring, AObject2D*>		m_ItemObj;
	map <wstring, AObject2D*>		m_CharactorObj; // npc, player
	map <wstring, AObject2D*>		m_MapObj;
	using m_woridIter = map<wstring, AObject2D*>::iterator;

public:
	//��üȭ �� �� ����, true(0)
	virtual bool	Load(wstring saveFile);
	virtual bool	Init() = 0;
	virtual bool	Frame() = 0;
	virtual bool	Render() = 0;
	virtual bool	Release(); //������

	AWorld();
	virtual ~AWorld();
};

