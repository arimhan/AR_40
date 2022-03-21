#include "Std.h"

class ADxState
{
public:
	static ID3D11RasterizerState* g_pRSBackCullWireFrame;
	static ID3D11RasterizerState* g_pRSNoneCullWireFrame;
	static ID3D11RasterizerState* g_pRSNoneCullSolid;
	static ID3D11DepthStencilState* g_pDSSDepthDisable;
public:
	static ID3D11BlendState*		m_AlphaBlend;
	static ID3D11BlendState*		m_AlphaBlendDisable;
	static ID3D11SamplerState*		m_pSamplerState;

	static ID3D11RasterizerState*	g_pRSBackCullSolid;
	static ID3D11DepthStencilState* g_pDSSDepthEnable;
	
public:
	static bool SetState(ID3D11Device* pd3dDevice);
	static bool Release();
};