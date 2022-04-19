struct VS_INPUT
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;    // COLOR0 ~ COLOR1
	float2 t : TEXCOORD0; // TEXCOORD0 ~ TEXCOORD15
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION; // 3 -> 4
	float3 n : NORMAL;
	float4 c : COLOR0;    // COLOR0 ~ COLOR1
	float2 t : TEXCOORD0; // TEXCOORD0 ~ TEXCOORD15

	float3 r  : TEXCOORD1;
	float4 l  : TEXCOORD2;
};

// 상수버퍼(단위:레지스터 단위(float4)로 할당되어야 한다.)
cbuffer cb0 : register(b0)
{
	// 1개의 레지스터(x,y,z,w)
	matrix   g_matWorld : packoffset(c0);
	matrix   g_matView : packoffset(c4);
	matrix   g_matProj : packoffset(c8);
	float4   Color0 : packoffset(c12);
	float    TimerX : packoffset(c13.x); // Timer.x, Timer.y, Timer.z, Timer.w	
};
cbuffer cb1 : register(b1)
{
	float4   vLightDir	: packoffset(c0);
	float4   vLightPos	: packoffset(c1);
	matrix	 g_matLight	: packoffset(c2);	//L(WVPT)행렬
};
VS_OUTPUT VS(VS_INPUT v)
{
	VS_OUTPUT pOut = (VS_OUTPUT)0;
	float4 vLocal = float4(v.p.xyz, 1.0f);// float4(v.p.x, v.p.y, v.p.z, 1.0f);
	float4 vWorld = mul(vLocal, g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	pOut.p = vProj;

	float4 vLight = mul(vLocal, g_matLight);	//Light에서 바라본 Texture변환좌표 ->PS 에 넘긴다.

	float3 vNormal = mul(v.n, (float3x3)g_matWorld);
	pOut.n = normalize(vNormal);
	pOut.t = v.t * 2.0f;	//텍스쳐 갯수
	float fDot = max(0.5f, dot(pOut.n, -vLightDir.xyz));
	pOut.c = v.c * float4(fDot, fDot, fDot, 1);// *Color0;

	
	float fNear = 0.1f;
	float fFar = 5000.0f;

	pOut.r = normalize(vLocal.xyz);
	return pOut;
}

Texture2D		g_txColor	: register(t0);
Texture2D		g_txMask	: register(t1);
TextureCube	    g_txCubeMap : register(t3);
SamplerState	g_Sample	: register(s0);

PBUFFER_OUTPUT PS(VS_OUTPUT input) : SV_TARGET
{
	PBUFFER_OUTPUT output;
	//텍스쳐에서 T좌표에 해당하는 컬러값(픽셀)반환
	float4 color = g_txColor.Sample(g_Sample, input.t);
	output.Color0 = color;
	float3 vNormal = input.n * 0.5f + 0.5f;

	//알파블렌딩 OFF
	output.color1 = float4(vNormal, input.c.a);
	return output;
}


float4 PSAlphaBlend(VS_OUTPUT input) : SV_TARGET
{
	float4 color = g_txColor.Sample(g_Sample, input.t);
	float4 final = color * input.c;
	final.a = color.a;
	return final;
}

