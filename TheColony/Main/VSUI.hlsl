cbuffer model : register(b0)
{
	matrix worldMat;
}

cbuffer viewProj : register(b1)
{
	matrix view;
	matrix proj;
}

cbuffer JointsBuffer : register(b2)
{
	matrix jointOffsets[100];
}

struct Input
{
	float4 pos : POSITION;
	float4 normal : NORMAL;
	float4 uv : UV;
	float4 color : COLOR;
	float4 jointIndex : JOINT_INDEX;
	float4 jointWeight : JOINT_WEIGHT;
	float4 flags : FLAGS;
	matrix instance : INSTANCE;
};

struct Output
{
	float4 pos : SV_POSITION;
	float4 worldPos : WORLDPOS;
	float4 normal : NORMAL;
	float4 uv : UV;
	float4 color : COLOR;
};

Output main(Input _in)
{
	Output ret;
	float4 pos = _in.pos;
	pos = mul(worldMat, pos);
	pos = mul(_in.instance, pos);
	ret.worldPos = pos;
	ret.pos = pos;
	ret.normal = normalize(float4(mul((float3x3)worldMat, _in.normal.xyz), 0));
	ret.uv = _in.uv;
	ret.color = _in.color;
	return ret;
}