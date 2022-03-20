#pragma once
#include "Object2D.h"

class AWorld
{
public:
	enum AWorldID { A_LOADING, A_LOGIN, A_LOBBY, A_ZONE, A_RESULT, };
	ID3D11Device*			m_pd3dDevice;	//����̽� ��ü
	ID3D11DeviceContext*	m_pContext;		//����̽� ���ؽ�Ʈ ��ü
	static AWorld*			m_pCurWorld;	//���� map
	bool					m_bLoadWorld = false;

public:
	vector <shared_ptr<AObject2D>>	m_UIObj;
	vector <shared_ptr<AObject2D>>	m_ItemObj;
	vector <shared_ptr<AObject2D>>	m_NpcObj; // npc, player
	vector <shared_ptr<AObject2D>>	m_MapObj;
	using m_woridIter = vector <shared_ptr<AObject2D>>::iterator;

public:
	//��üȭ �� �� ����, true(0)
	virtual bool	Load(wstring saveFile);
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release(); //������

	AWorld();
	virtual ~AWorld();
};


