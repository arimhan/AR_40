#pragma once
#include "ShaderMgr.h"
#include "TextureMgr.h"

struct ASimplevertex
{
	AVector2 v;
	AVector2 t;
};
enum ACollisionType { Block = 0, Overlap, Ignore, };
enum ASelectType { Select_Block = 0, Select_Overlap, Select_Ignore, };
enum ASelectState { 
	M_DEFAULT = 0,		//Ŀ�� ���� X , FOCUS���¿��� �ٸ� ���� ACTIVE�ϸ� ��ȯ��
	M_HOVER = 1,		//Ŀ���� ���� X
	M_FOCUS = 2,		//ACTIVE���¿��� ���� ��ư�� �ٸ� ������ ������ �� ���
	M_ACTIVE = 4,		//���콺 ���ʹ�ư�� ������ ���� ��
	M_SELECTED = 8, };	//ACTIVE���¿��� ���ʹ�ư�� ������ ��
class ABaseObject
{
public:
	wstring		m_csName;

	float		m_fSpeed;
	AVector2	m_vPos;
	AVector2	m_vDirection;
	float		m_fWidth;
	float		m_fHeight;

	int			m_iCollisionID;
	ARect		m_rtCollision;
	DWORD		m_dwCollisionType;
	bool		m_bAlphaBlend;

public:
	bool		m_bDead;
	int			m_iSelectID;
	bool		m_bSelect;
	DWORD		m_dwSelectType;
	DWORD		m_dwSelectState;
	DWORD		m_dwPreSelectState;

public:
	virtual void HitOverlap(ABaseObject* pObj, DWORD dwState);
	virtual void HitSelect(ABaseObject* pObj, DWORD dwState);
	virtual void SetCollisionType(DWORD dwCollisionType, DWORD dwSelectType)
	{
		m_dwCollisionType = dwCollisionType;
		m_dwSelectType = dwSelectType;
	}

	ABaseObject()
	{
		m_bDead = false;
		m_bSelect = false;
		m_bAlphaBlend = true;
		m_dwSelectState = M_DEFAULT;
		m_iCollisionID = -1;
		m_iSelectID = -1;
		m_vDirection.x = 0.0f;
		m_vDirection.y = 0.0f;
		m_dwCollisionType = ACollisionType::Ignore;
		m_dwSelectType = Select_Ignore; //�� �� ACollisionType������ �� Overlap��. enum Class��� �� ���� ���� ǥ��.
	}
};
// Index, Constance Buffer (�ε���, ������� �߰�)
struct AIndex
{
	DWORD _0;
	DWORD _1;
	DWORD _2;
};
struct AConstanceData
{
	AVector4 Color;
	AVector4 Timer;
};
class ADxObject : public ABaseObject
{
public:
	ATexture*	m_pColorTex = nullptr;
	ATexture*	m_pMaskTex	= nullptr;
	AShader*	m_pVSShader = nullptr;
	AShader*	m_pPSShader = nullptr;
public:

	ID3D11BlendState*			m_AlphaBlend;
	ID3D11BlendState*			m_AlphaBlendDisable;
	D3D11_TEXTURE2D_DESC		m_TextureDesc;
public:
	vector<ASimplevertex>	m_InitScreenList;
	vector<ASimplevertex>	m_VertexList;
	ID3D11Buffer*			m_pVertexBuffer;

	vector<DWORD>			m_IndexList;
	ID3D11Buffer*			m_pIndexBuffer;

	AConstanceData			m_ConstantList;
	ID3D11Buffer*			m_pConstantBuffer;

	ID3D11InputLayout*		m_pVertexLayout;
	ID3D11Device*			m_pd3dDevice;
	ID3D11DeviceContext*	m_pContext;
public:
	void			SetDevice(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext);
	virtual bool	LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName);
	virtual bool	SetVertexData();
	virtual bool	SetIndexData();
	virtual bool	SetConstantData();
	virtual bool	Create(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext, 
					const TCHAR* szShaderFileName =nullptr, 
					const TCHAR* szTectureFileName = nullptr,
					const TCHAR* szMaskFileNmae = nullptr);
		//Create�� ��ɺ��� �и��Ͽ� �Լ�ȭ
		virtual bool	CreateVertexBuffer();
		virtual bool	CreateIndexBuffer();
		virtual bool	CreateConstantBuffer();
		virtual bool	CreateVertexShader(const TCHAR* szFile);
		virtual bool	CreatePixelShader(const TCHAR* szFile);
		virtual bool	CreateInputLayout();
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
public:
	ADxObject() { m_fSpeed = 0.0001f; }
	~ADxObject() {}
};

