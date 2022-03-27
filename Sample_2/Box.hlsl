struct VS_INPUT
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD0;
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION;		//INPUT 3 + W -> OUTPUT 4
	float3 n : NORMAL;
	float4 c : COLOR0;			//INPUT 3 + W -> OUTPUT 4
	float2 t : TEXCOORD0;

	float3 r : TEXCOORD1;		//넘길 값 추가
};

//상수버퍼 (레지스터 단위 float4로 할당)
cbuffer cb0 : register(b0)
{
	//1개의 레지스터 (x, y, z, w)
	matrix	g_matWorld	:	packoffset(c0);
	matrix	g_matView	:	packoffset(c4);
	matrix	g_matProj	:	packoffset(c8);
	float4	Color0		:	packoffset(c12);
	float	TimerX		: packoffset(c13.x);
};

VS_OUTPUT VS(VS_INPUT v)
{
	//hlsl에서 mul은 기본 내적으로 계산. 그러므로 행렬 전치처리를 해야 외적결과가 나온다.
	VS_OUTPUT pOut = (VS_OUTPUT)0;
	float4 vLocal = float4(v.p.xyz, 1.0f);
	float4 vWorld = mul(vLocal, g_matWorld);	
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);

	pOut.p = vProj;
	//float3 vNormal = mul(v.n, g_matWorld);
	float3 vNormal = mul(v.n, (float3x3)g_matWorld);
	pOut.n = normalize(vNormal);
	pOut.t = v.t;
	float fDot = max(0.5f, dot(pOut.n, - Color0.xyz));
	pOut.c = float4(fDot, fDot, fDot, 1);

	pOut.r = normalize(vLocal.xyz);

	return pOut;
}

//Frustum 확인용 ObjList 추가
VS_OUTPUT VSColor(VS_INPUT v)
{
	VS_OUTPUT pOut = (VS_OUTPUT)0;
	float4 vLocal = float4(v.p.xyz, 1.0f);
	float4 vWorld = mul(vLocal, g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	pOut.p = vProj;
	pOut.c = v.c;
	pOut.r = normalize(vLocal.xyz);
	return pOut;
}

//Frustum 확인용 ObjList 추가
float4 PSColor(VS_OUTPUT input) : SV_TARGET
{
	float4 vColor = input.c;
	vColor.a = 0.5f;
	return vColor;
}

Texture2D		g_txColor	: register(t0);
Texture2D		g_txMask	: register(t1);
TextureCube		g_txCubeMap	: register(t3);	//3번으로 넘긴것 CubeMap
SamplerState	g_Sample	: register(s0);

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	//	텍스처에서 t좌표에 해당하는 컬러값(픽셀) 반환
	float4 color = g_txColor.Sample(g_Sample, input.t);
	float4 mask = g_txMask.Sample(g_Sample, input.t);
	float4 final = color;

	//소스알파(1) 마스크 이미지의 검정색 부분 -> 불투명
	//소스알파(0) 마스크 이미지의 흰색 부분 -> 투명
	//final.a = 1.0f; //-1.0f;
	final = final * input.c;

	final = g_txCubeMap.Sample(g_Sample, input.r);

	return final;
}

float4 PSAlphaBlend(VS_OUTPUT input) : SV_TARGET
{
	float4 color = g_txColor.Sample(g_Sample, input.t);
	float4 final = color * input.c;
	final.a = color.a;
	return final;
}