struct VS_INPUT
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;    
	float2 t : TEXCOORD0; 
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION; 
	float3 n : NORMAL;
	float4 c : COLOR0;   
	float2 t : TEXCOORD0;
	float3 r  : TEXCOORD1;
};

// �������(����:�������� ����(float4)�� �Ҵ�Ǿ�� �Ѵ�.)
cbuffer cb0 : register(b0)
{
	// 1���� ��������(x,y,z,w)
	matrix   g_matWorld : packoffset(c0);
	matrix   g_matView : packoffset(c4);
	matrix   g_matProj : packoffset(c8);
	float4   Color0 : packoffset(c12);
	float    TimerX : packoffset(c13.x); 
};
cbuffer cb1 : register(b1)
{
	float4   vLightDir : packoffset(c0);
	float4   vLightPos : packoffset(c1);
};
VS_OUTPUT VS(VS_INPUT v)
{
	VS_OUTPUT pOut = (VS_OUTPUT)0;
	float4 vLocal = float4(v.p.xyz, 1.0f);
	float4 vWorld = mul(vLocal, g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	pOut.p = vProj;
	float3 vNormal = mul(v.n, (float3x3)g_matWorld);
	pOut.n = normalize(vNormal);
	pOut.t = v.t;
	float fDot = max(0.5f, dot(pOut.n, -vLightDir.xyz));
	pOut.c = v.c * float4(fDot, fDot, fDot, 1);

	pOut.r = normalize(vLocal.xyz);
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
Texture2D		g_txColor	: register(t0);
Texture2D		g_txMask	: register(t1);
TextureCube	    g_txCubeMap : register(t3);
SamplerState	g_Sample	: register(s0);

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	//�ؽ�ó���� t��ǥ�� �ش��ϴ� �÷���(�ȼ�) ��ȯ
	float4 color = g_txColor.Sample(g_Sample, input.t);
	float4 mask = g_txMask.Sample(g_Sample, input.t);
	float4 final = color;
	final = final * input.c; // *Color0;
	//�����׽��� (���� ������ ���� �������� �� ����Ѵ�.)
	//���� : ������ �����ϱ� ����� ������Ʈ ������ �� ���ĵ� ���¿� �����ϰ� ������ �ȴ�.
	if(final.a < 0.5f)
	{
		discard;
	}

	return final;
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
	float4 vColor = input.c;
	vColor.a = 0.5f * input.c.a;
	return vColor;
}