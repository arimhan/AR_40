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

// �������(����:�������� ����(float4)�� �Ҵ�Ǿ�� �Ѵ�.)
cbuffer cb0 : register(b0)
{
	// 1���� ��������(x,y,z,w)
	matrix   g_matWorld : packoffset(c0);
	matrix   g_matView	: packoffset(c4);
	matrix   g_matProj	: packoffset(c8);
	float4   Color0		: packoffset(c12);
	float    TimerX		: packoffset(c13.x); // Timer.x, Timer.y, Timer.z, Timer.w	
};
cbuffer cb1 : register(b1)	//������� ���� ���� ����� �Ѿ (packoffset�� ���� �����Ѱ� ���� �ȵ�)
{
	float4   vLightDir	: packoffset(c0);
	float4   vLightPos	: packoffset(c1);
	float4	 vEyeDir	: packoffset(c2);
	float4	 vEyePos	: packoffset(c3);
	matrix	 g_matLight	: packoffset(c4);	//L(WVPT)���
};
VS_OUTPUT VS(VS_INPUT v)
{
	VS_OUTPUT pOut = (VS_OUTPUT)0;
	float4 vLocal = float4(v.p.xyz, 1.0f);// float4(v.p.x, v.p.y, v.p.z, 1.0f);
	float4 vWorld = mul(vLocal, g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	pOut.p = vProj;

	pOut.l = mul(vWorld, g_matLight);

	//float4 vLight = mul(vLocal, g_matLight);	//Light���� �ٶ� Texture��ȯ��ǥ ->PS �� �ѱ��.

	float3 vNormal = mul(v.n, (float3x3)g_matWorld);
	pOut.n = normalize(vNormal);
	pOut.t = v.t * 2.0f;	//�ؽ��� ��
	float fDot = max(0.5f, dot(pOut.n, -vLightDir.xyz));
	pOut.c = v.c * float4(fDot, fDot, fDot, 1);// *Color0;
	
	float fNear = 0.1f;
	float fFar = 5000.0f;
	pOut.c.w = (pOut.p.w - fNear) / (fFar - fNear);

	pOut.r = normalize(vLocal.xyz);
	return pOut;
}

Texture2D		g_txColor		: register(t0);
Texture2D		g_txMask		: register(t1);
TextureCube	    g_txCubeMap		: register(t3);
SamplerState	g_Sample		: register(s0);
SamplerState	g_SampleClamp	: register(s1);	//SampleClamp �߰�

struct PBUFFER_OUTPUT
{
	float4 color0 : SV_TARGET0;
	float4 color1 : SV_TARGET1;
};


PBUFFER_OUTPUT PS(VS_OUTPUT input) : SV_TARGET
{
	PBUFFER_OUTPUT output;
	//�ؽ��Ŀ��� T��ǥ�� �ش��ϴ� �÷���(�ȼ�)��ȯ
	float4 color = g_txColor.Sample(g_Sample, input.t);
	float2 LightUV = float2(input.l.xy / input.l.w);
	float4 mask = g_txMask.Sample(g_SampleClamp, LightUV);

	//mask�� r���� �����ϸ� ������ �÷��� ��� ->������ ������ �׸���
	if (mask.r > 0.0f)
	{
		output.color0 = color * float4(0.5f, 0.5f, 0.5f, 1);
	}
	else 
	{
		output.color0 = color;
	}

	float3 vNormal = input.n * 0.5f + 0.5f;

	//���ĺ��� OFF
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

