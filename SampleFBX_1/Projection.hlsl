//Projection Shadow

cbuffer cb0 : register(b0)
{
	// 1개의 레지스터(x,y,z,w)
	matrix   g_matWorld : packoffset(c0);
	matrix   g_matView	: packoffset(c4);
	matrix   g_matProj	: packoffset(c8);
	float4   Color0		: packoffset(c12);
	float    TimerX		: packoffset(c13.x); // Timer.x, Timer.y, Timer.z, Timer.w	
};

VS_OUTPUT VS( VS_INPUT v)
{
	float4 p : SV_POSITION;
	return pOut;
}

//Composite partices into the scene

VS_OUTPUT VSColor(VS_INPUT v)
{
	VS_OUTPUT output;
	output.p = mul(p, g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);

	return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	return Color0;
}
