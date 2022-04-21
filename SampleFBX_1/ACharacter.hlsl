struct VS_INPUT
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD0;

	float4 i : INDEX;
	float4 w : WEIGHT;
	float3 tan : TANGENT;
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float3 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
	float3 r : TEXCOORD1;
	float3 l : TEXCOORD2;
	float3 e : TEXCOORD3;

	float4 shadow : TEXCOORD4;
};

// 상수버퍼(단위:레지스터 단위(float4)로 할당되어야 한다.)
cbuffer cb0 : register(b0)
{
	// 1개의 레지스터(x,y,z,w)
	matrix   g_matWorld : packoffset(c0);
	matrix   g_matView : packoffset(c4);
	matrix   g_matProj : packoffset(c8);
	matrix   g_matNormal : packoffset(c12);

	float4   Color0 : packoffset(c16);
	float    TimerX : packoffset(c17.x);
};
cbuffer cb1 : register(b1)
{
	float4   vLightDir	: packoffset(c0);
	float4   vLightPos	: packoffset(c1);

	float4	 vEyeDir	: packoffset(c2);
	float4	 vEyePos	: packoffset(c3);
	matrix	 g_matLight	: packoffset(c4);
};
cbuffer cb2 : register(b2)
{
	float4x4 g_matBoneWorld[255];	//65535 /4
};

VS_OUTPUT VS(VS_INPUT v)
{
	VS_OUTPUT pOut = (VS_OUTPUT)0;
	uint iIndex = v.c.w;

	float4 vLocal = float4(v.p.xyz, 1.0f);
	//float4 vWorld = mul(vLocal, g_matWorld);

	float4 vWorld = 0;
	float3 vNormal = 0;
	for (int iBone = 0; iBone < 4; iBone++)
	{
		uint iBoneIndex = v.i[iBone];
		vWorld += mul(vLocal, g_matBoneWorld[iBoneIndex]) * v.w[iBone];
		vNormal += mul(v.n, (float3x3)g_matBoneWorld[iBoneIndex]) * v.w[iBone];
	}

	vWorld = mul(vWorld, g_matWorld);
	vNormal = mul(vNormal, (float3x3)g_matNormal);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);

	pOut.p = vProj;
	pOut.n = normalize(vNormal);
	pOut.t = v.t * 5;	//Normal텍스쳐 갯수. 많을 수록 큰 사이즈의 이미지에 잘 붙으며, 적을수록 확대되어 붙음

	float3 T = normalize(mul(v.tan, (float3x3)g_matNormal));
	float3 B = normalize(cross(vNormal, T));	//외적
	
	float3x3 tanMat = { T.x, B.x , vNormal.x,
						T.y, B.y , vNormal.y,
						T.z, B.z , vNormal.z };	//행렬식으로 나타냄.

	pOut.l = normalize(mul(-vLightDir.xyz, tanMat));
	pOut.e = normalize(mul(vEyeDir.xyz, tanMat));
	pOut.r = reflect(vEyeDir.xyz, pOut.n);
	
	return pOut;
}

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

//-----------------------------------------------
Texture2D		g_txColor		: register(t0);
Texture2D		g_txMask		: register(t1);

TextureCube	    g_txCubeMap		: register(t3);
Texture2D		g_txNormalMap	: register(t4);
Texture2D		g_txShadowMap	: register(t5);

SamplerState	g_Sample		: register(s0);
SamplerState	g_SampleClamp	: register(s1);

//-----------------------------------------------

float Specular(float3 vNormal)
{
	// Specular Lighting
	float  fPower = 0.0f;

#ifndef HALF_VECTOR
	float3 R = reflect(vLightDir, vNormal);
	fPower = pow(saturate(dot(R, -vEyeDir)), 5.0f);

#else
	float3 vHalf = normalize(-vLightDir + -vEyeDir);
	fPower = pow(saturate(dot(vNormal, vHalf)), 5.0f);

#endif	
	float4 specular = float4(fPower, fPower, fPower, 1.0f);
	return fPower;
}



float Diffuse(float3 vNormal)
{
	float fIntensity = max(0, dot(vNormal, normalize(-vLightDir)));

	//float4 diffuse = fIntensity;
	return fIntensity;
}

//float4 PS(VS_OUTPUT input) : SV_TARGET
//{
//	//텍스처에서 t좌표에 해당하는 컬러값(픽셀) 반환
//	float4 color = g_txColor.Sample(g_Sample, input.t);
//	float4 normal = g_txNormalMap.Sample(g_Sample, input.t);
//	normal = normalize((normal - 0.5f) * 2.0f);
//
//	float fDot = saturate(dot(normal.xyz, input.l));
//
//	float4 final = color * float4(fDot, fDot, fDot, 1);
//
//	//float2 uv = float2(fDot, 0.5f);
//	//float4 mask = g_txMask.Sample(g_Sample, uv);
//	//소스알파(1) = 마스크 이미지의 검정색 부분은 불투명
//	//소스알파(0) = 마스크 이미지의 흰색 부분은 투명
//	//알파테스팅 (완전 투명과 완전 불투명일 때 사용한다.)
//	//장점 : 순서를 구분하기 어려운 오브젝트 렌더링 시 정렬된 상태와 유사하게 렌더링 된다.
//	if (final.a < 0.5f)
//	{
//		discard;
//	}
//	float4 vCube = g_txCubeMap.Sample(g_Sample, input.r);
//	final = lerp(final, vCube, 0.3f);
//	final.a = 1.0f;
//	return final;
//}

struct PBUFFER_OUTPUT
{
	float4 color0 : SV_TARGET0;
	float4 color1 : SV_TARGET1;
};

PBUFFER_OUTPUT PSMRT(VS_OUTPUT input) : SV_TARGET
{
	PBUFFER_OUTPUT output;
	//텍스처에서 t좌표에 해당하는 컬러값(픽셀) 반환

	float4 color = g_txColor.Sample(g_Sample, input.t);
	float4 shadow = g_txShadowMap.Sample(g_SampleClamp, input.shadow.xy / input.shadow.w);
	uint id = shadow * 255.0f;	//obj마다 고유의 컬러 id를 부여하고 최대값 255로 나누어 깊이에 따라 컬러값이 저장된다.

	//만일 id값이 shadow의 r(깊이)가 0보다 클 경우 == r값에 따라 RGBW값이 변경된다. (color * RGBW)
	if (id!= (uint)TimerX && shadow.r > 0.0f)
	{
		color = color * float4(0.5f, 0.5f, 0.5f, 1);
	}
	else //변하지 않으면 기존 컬러값 그대로 놔둔다
	{
		color = color;
	}

	float4 vNormal = g_txNormalMap.Sample(g_Sample, input.t);
	normal = normalize((normal - 0.5f) * 2.0f);
	float fDot = saturate(dot(normal.xyz, input.l));
	float4 final = color * float4(fDot, fDot, fDot, 1);
	// 0 ~ 1 -> 0.0f ~ 0.5f 
	float2 uv = float2(fDot, 0.5f);

	float4 vCube = g_txCubeMap.Sample(g_Sample, input.r);

	//값 보간하고 알파값 설정
	final = lerp(final, vCube, 0.5f);
	final.a = 1.0f;

	output.color0 = final;
	float3 vNormal = input.n * 0.5f + 0.5f;

	// 필수->알파블랜딩 =OFF;
	output.color1 = float4(vNormal, input.c.a);
	return output;
}


float4 PS(VS_OUTPUT input) : SV_TARGET
{
	float4 color = g_txColor.Sample(g_Sample, input.t);
	float4 normal = g_txNormalMap.Sample(g_Sample, input.t);
	normal = normalize((normal - 0.5f) * 2.0f);
	float fDot = saturate(dot(normal.xyz, input.l));

	float4 final = color * float4(fDot, fDot, fDot, 1);

	float2 uv = float2(fDot, 0.5f);
	final = final * Specular(normal);
	final.a = 1.0f;//color.a;
	float4 vCube = g_txCubeMap.Sample(g_Sample, input.r);
	final = lerp(final, vCube, 0.5f);
	final.a = 1.0f;

	return float4(fDot, fDot, fDot, 1);
}

float4 PSAlphaBlend(VS_OUTPUT input) : SV_TARGET
{
	float4 color = g_txColor.Sample(g_Sample, input.t);
	float4 final = color * input.c;
	final.a = color.a;

	return final;
}

float4 PSColor(VS_OUTPUT input) : SV_TARGET
{
	//float4 vColor = input.c;
	//vColor.a = 0.5f * input.c.a;
	float4 vColor = input.c;
	vColor.a = 0.5f * input.c.a;
	return vColor;
}