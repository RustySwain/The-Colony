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
};

struct Output
{
	float4 pos : SV_POSITION;
	float4 worldPos : WORLDPOS;
	float4 normal : NORMAL;
	float4 uv : UV;
	float4 color : COLOR;
};

float4 addJointInfluence(Input _in)
{
	float4 pos = _in.pos;
	_in.pos.w = 1;
	pos.w = 1;

	pos += mul(jointOffsets[_in.jointIndex[0]], _in.pos) * _in.jointWeight[0];
	pos += mul(jointOffsets[_in.jointIndex[1]], _in.pos) * _in.jointWeight[1];
	pos += mul(jointOffsets[_in.jointIndex[2]], _in.pos) * _in.jointWeight[2];
	pos += mul(jointOffsets[_in.jointIndex[3]], _in.pos) * _in.jointWeight[3];
	return pos;
}

Output main(Input _in)
{
	Output ret;
	float4 pos;
	if (_in.flags[0] == 1)
	{
		pos = float4(addJointInfluence(_in).xyz, 1.0f);
	}
	else
	{
		pos = float4(_in.pos.xyz, 1.0f);
	}
	pos = mul(worldMat, pos);
	ret.worldPos = pos;
	pos = mul(view, pos);
	pos = mul(proj, pos);
	ret.pos = pos;
	ret.normal = normalize(float4(mul((float3x3)worldMat, _in.normal.xyz), 0));
	ret.uv = _in.uv;
	ret.color = _in.color;
	return ret;
}