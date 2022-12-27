struct VS_INPUT
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;    // COLOR0 ~ COLOR1
	float2 t : TEXCOORD0; // TEXCOORD0 ~ TEXCOORD15
};
struct VS_OUTPUT
{
	float4 p	: SV_POSITION; // 3 -> 4
	float3 n	: NORMAL;
	float4 c	: COLOR0;    // COLOR0 ~ COLOR1
	float2 t	: TEXCOORD0; // TEXCOORD0 ~ TEXCOORD15
	float3 r	: TEXCOORD1;
	float4 L	: TEXCOORD2;
};

// 상수버퍼(단위:레지스터 단위(float4)로 할당되어야 한다.)
cbuffer cb0 : register(b0)
{
	// 1개의 레지스터(x,y,z,w)
	matrix   g_matWorld : packoffset(c0);
	matrix   g_matView	: packoffset(c4);
	matrix   g_matProj	: packoffset(c8);
	matrix	 g_matNormal: packoffset(c12);
	float4   Color0		: packoffset(c16);
	float    TimerX		: packoffset(c17.x); // Timer.x, Timer.y, Timer.z, Timer.w	
};
cbuffer cb1 : register(b1)	//상수버퍼 전부 구조 맞춰야 넘어감 (packoffset의 값에 엉뚱한게 들어가면 안됨)
{
	float4   vLightDir	: packoffset(c0);
	float4   vLightPos	: packoffset(c1);
	float4	 vEyeDir	: packoffset(c2);
	float4	 vEyePos	: packoffset(c3);
	matrix	 g_matLight	: packoffset(c4);	//L(WVPT)행렬
};
VS_OUTPUT VS(VS_INPUT v)
{
	VS_OUTPUT pOut = (VS_OUTPUT)0;
	float4 vLocal = float4(v.p.xyz, 1.0f);// float4(v.p.x, v.p.y, v.p.z, 1.0f);
	float4 vWorld = mul(vLocal, g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	pOut.p = vProj;
	pOut.L = mul(vWorld, g_matLight);

	float3 vNormal = mul(v.n, (float3x3)g_matWorld);
	pOut.n = normalize(vNormal);
	pOut.t = v.t * 2.0f;	//텍스쳐 수

	float fDot = max(0.5f, dot(pOut.n, -vLightDir.xyz));
	pOut.c = v.c * float4(fDot, fDot, fDot, 1);
	pOut.c.w = pOut.L.z / pOut.L.w; //(pOut.p.w - Color0.z) / (Color0.w - Color0.z);
	//float4 vLight = mul(vLocal, g_matLight);	//Light에서 바라본 Texture변환좌표 ->PS 에 넘긴다.

	//float fNear = 0.1f;
	//float fFar = 5000.0f;


	pOut.r = normalize(vLocal.xyz);
	return pOut;
}

Texture2D				g_txColor			: register(t0);
Texture2D				g_txMask			: register(t1);
TextureCube				g_txCubeMap			: register(t3);
SamplerState			g_Sample			: register(s0);
SamplerState			g_SampleClamp		: register(s1);	//SampleClamp 추가
SamplerComparisonState	g_samComShadowMap	: register(s2);

struct PBUFFER_OUTPUT
{
	float4 color0 : SV_TARGET0;
	float4 color1 : SV_TARGET1;
};

float PS_NO_CMP(float4 uvw)
{
	float SMAP_SIZE = 4096 * 4;
	float LightAmount = 0.0f;
	float2 uv = uvw.xy / uvw.w;
	float2 texelpos = SMAP_SIZE * uv;
	float2 lerps = frac(texelpos);
	float sourcevals[4];
	sourcevals[0] = (g_txMask.Sample(g_SampleClamp, uv) < uvw.z / uvw.w) ? 0.0f : 1.0f;
	sourcevals[1] = (g_txMask.Sample(g_SampleClamp, uv + float2(1.0 / SMAP_SIZE, 0)) < uvw.z / uvw.w) ? 0.0f : 1.0f;
	sourcevals[2] = (g_txMask.Sample(g_SampleClamp, uv + float2(0, 1.0 / SMAP_SIZE)) < uvw.z / uvw.w) ? 0.0f : 1.0f;
	sourcevals[3] = (g_txMask.Sample(g_SampleClamp, uv + float2(1.0 / SMAP_SIZE, 1.0 / SMAP_SIZE)) < uvw.z / uvw.w) ? 0.0f : 1.0f;
	LightAmount = lerp(lerp(sourcevals[0], sourcevals[1], lerps.x), lerp(sourcevals[2], sourcevals[3], lerps.x), lerps.y);
	return 0.5f;
}

PBUFFER_OUTPUT PS(VS_OUTPUT input) : SV_TARGET
{
	PBUFFER_OUTPUT output;
	//텍스쳐에서 T좌표에 해당하는 컬러값(픽셀)반환
	float4 color = g_txColor.Sample(g_Sample, input.t);
	float3 LightUV = float3(input.L.xyz / input.L.w);
	//float4 mask = g_txMask.Sample(g_SampleClamp, LightUV);
	float mask = g_txMask.SampleCmpLevelZero(g_samComShadowMap, LightUV.xy, LightUV.z).r;
	mask = max(0.5f, mask);

	//mask의 r값이 존재하면 지정한 컬러로 출력 ->검은색 반투명 그림자
	//if (mask.r > 0.0f)
	//{
	//	output.color0 = color * float4(0.5f, 0.5f, 0.5f, 1);
	//}
	//else 
	//{
	//	output.color0 = color;
	//}
	output.color0 = color * float4(mask, mask, mask, 1);
	float3 vNormal = input.n * 0.5f + 0.5f;

	//알파블렌딩 OFF
	output.color1 = float4(vNormal, input.c.a);
	return output;
}

//PBUFFER_OUTPUT PS(VS_OUTPUT input) : SV_TARGET
//{
//	//텍스처에서 t좌표에 해당하는 컬러값(픽셀) 반환
//	float4 color = g_txColor.Sample(g_Sample, input.t);
//	float4 mask = g_txMask.Sample(g_Sample, input.t);
//	float4 final = color;
//	// 소스알파(1) = 마스크이미지의 검정색부분은 불투명된다.
//	// 소스알파(0) = 마스크이미지의 흰색부분은   투명된다.
//	final = final * input.c;
//	//final.a = 1.0f;	
//	return final;
//}

float4 PSAlphaBlend(VS_OUTPUT input) : SV_TARGET
{
	float4 color = g_txColor.Sample(g_Sample, input.t);
	float4 final = color * input.c;
	final.a = color.a;
	return final;
}

