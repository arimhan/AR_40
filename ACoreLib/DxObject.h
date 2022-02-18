#pragma once
#include "Std.h"
#include <d3dcompiler.h>
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"
#pragma comment	(lib, "d3dcompiler.lib")

struct ASimplevertex
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
	M_SELECTED = 8, };	//ACTIVE상태에서 왼쪽버튼을 놓았을 때
class ABaseObject
{
public:
	int			m_iCollisionID;
	float		m_fSpeed;
	AVector2	m_vPos;
	AVector2	m_vDirection;
	float		m_fWidth;
	float		m_fHeight;
	ARect		m_rtCollision;
	DWORD		m_dwCollisionType;
	bool		m_bAlphaBlend = true;
public:
	bool		m_bDead;
	int			m_iSelectID;
	bool		m_bSelect;
	DWORD		m_dwSelectType;
	DWORD		m_dwSelectState;

public:
	virtual void HitOverlap(ABaseObject* pObj, DWORD dwState);
	virtual void HitSelect(ABaseObject* pObj, DWORD dwState);

	ABaseObject()
	{
		m_bDead = false;
		m_bSelect = false;
		m_dwSelectState = M_DEFAULT;
		m_iCollisionID = -1;
		m_iSelectID = -1;
		m_vDirection.x = 0.0f;
		m_vDirection.y = 0.0f;
		m_dwCollisionType = ACollisionType::Overlap;
		m_dwSelectType = Overlap; //둘 다 ACollisionType열거형 내 Overlap임. enum Class사용 시 위와 같이 표기.
	}
};
class ADxObject : public ABaseObject
{
public:
	ID3D11ShaderResourceView*	m_pSRV0; //숫자 SRV 0번
	ID3D11ShaderResourceView*	m_pSRV1;
	ID3D11Texture2D*			m_pTexture0;
	ID3D11Texture2D*			m_pTexture1;
	ID3D11BlendState*			m_AlphaBlend;
	ID3D11BlendState*			m_AlphaBlendDisable;
	D3D11_TEXTURE2D_DESC		m_TextureDesc;

public:
	vector<ASimplevertex>	m_InitScreenList;
	vector<ASimplevertex>	m_VertexList;
	ID3D11Buffer*			m_pVertexBuffer;
	ID3D11InputLayout*		m_pVertexLayout;
	ID3D11VertexShader*		m_pVertexShader;
	ID3D11PixelShader*		m_pPixelShader;

	ID3D11Device*			m_pd3dDevice;
	ID3D11DeviceContext*	m_pContext;

	ID3DBlob*	m_pVSCodeResult = nullptr;
	ID3DBlob*	m_pErrorMsgs = nullptr;
	ID3DBlob*	m_pPSCodeResult = nullptr;

public:
	void SetDevice(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext);
	virtual bool LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName);
	virtual bool SetVertexData();
	virtual bool Create(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext, 
		const TCHAR* szTectureFileName =nullptr, const TCHAR* szMaskFileNmae= nullptr);

	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	ADxObject();
	~ADxObject();
};

