#pragma once
#include "ShaderMgr.h"
#include "TextureMgr.h"
#include "DxState.h"
#include "Collision.h"

struct ASimpleVertex
{
	AVector2 v;
	AVector2 t;
};
enum ACollisionType { Block = 0, Overlap, Ignore, };
enum ASelectType { Select_Block = 0, Select_Overlap, Select_Ignore, };
enum ASelectState {
	M_DEFAULT = 0,		//커서 위에 X , FOCUS상태에서 다른 곳을 ACTIVE하면 전환됨
	M_HOVER = 1,		//커서가 위에 X
	M_FOCUS = 2,		//ACTIVE상태에서 왼쪽 버튼을 다른 곳에서 놓았을 때 취소
	M_ACTIVE = 4,		//마우스 왼쪽버튼을 누르고 있을 때
	M_SELECTED = 8,};	//ACTIVE상태에서 왼쪽버튼을 놓았을 때
class ABaseObject
{
public:
	wstring   m_csName;
public:
	ABaseObject*   m_pParent = nullptr;
	bool		m_bDead;
	int			m_iCollisionID;
	int			m_iSelectID;
	float		m_fSpeed;
	AVector2	m_vPos;
	AVector2	m_vDirection;
	float		m_fWidth;
	float		m_fHeight;
	ARect		m_rtCollision;
	DWORD		m_dwCollisionType;
	DWORD		m_dwSelectType;
	DWORD		m_dwSelectState;
	DWORD		m_dwPreSelectState;
	bool		m_bSelect;
	bool		m_bAlphaBlend;
public:
	virtual void	HitOverlap(ABaseObject* pObj, DWORD dwState);
	virtual void	HitSelect(ABaseObject* pObj, DWORD dwState);
	virtual void	SetCollisionType(DWORD dwCollisionType, DWORD dwSelectType)
	{
		m_dwCollisionType = dwCollisionType;
		m_dwSelectType = dwSelectType;
	}
public:
	
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
		m_dwSelectType = ASelectType::Select_Ignore; //둘 다 ACollisionType열거형 내 Overlap임. enum Class사용 시 위와 같이 표기.
	}
};
struct AIndex
{
	DWORD _0;
	DWORD _1;
	DWORD _2;
};

struct AConstantData
{
	AVector4 Color;
	AVector4 Timer;
};
class ADxObject : public ABaseObject
{
public:
	ATexture* m_pColorTex = nullptr;
	ATexture* m_pMaskTex = nullptr;
	AShader*  m_pVSShader = nullptr;
	AShader*  m_pPSShader = nullptr;
	D3D11_TEXTURE2D_DESC		m_TextureDesc;
public:
	vector<ASimpleVertex> m_InitScreenList;
	vector<ASimpleVertex> m_VertexList;
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	
	vector<DWORD> m_IndexList;
	ID3D11Buffer* m_pIndexBuffer = nullptr;

	AConstantData    m_ConstantList;
	ID3D11Buffer*    m_pConstantBuffer = nullptr;

	ID3D11InputLayout* m_pVertexLayout = nullptr;
	ID3D11Device*		 m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pContext=nullptr;
public:	
	void    SetDevice(ID3D11Device* m_pd3dDevice,
					  ID3D11DeviceContext* m_pContext);
	virtual bool    LoadTexture(const TCHAR* szColorFileName,
								const TCHAR* szMaskFileName);
	virtual bool    SetVertexData();
	virtual bool    SetIndexData();
	virtual bool    SetConstantData();
	virtual bool	Create( ID3D11Device* m_pd3dDevice,
					ID3D11DeviceContext* m_pContext,	
					const TCHAR* szShaderFileName = nullptr,
					const TCHAR* szTextureFileName=nullptr,
					const TCHAR* szMaskFileName = nullptr);
	virtual bool	CreateVertexBuffer();
	virtual bool    CreateIndexBuffer();
	virtual bool	CreateConstantBuffer();
	virtual bool    CreateVertexShader(const TCHAR* szFile);
	virtual bool    CreatePixelShader(const TCHAR* szFile);
	virtual bool    CreateInputLayout();
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
public:
	ADxObject();
	~ADxObject();
};

