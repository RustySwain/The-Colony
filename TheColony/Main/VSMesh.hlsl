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

//Shadow Stuff
cbuffer MatrixBuffer : register(b3)
{
	matrix lightViewMatrix;
	matrix lightProjectionMatrix;
};

cbuffer LightPos : register(b4)
{
	float4 lightPosition;
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
	float4 lightViewPosition : TEXCOORD1;
	float4 lightPos : TEXCOORD2;
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
	pos *= 0.5f;
	pos.w = 1;

	return pos;
}

Output main(Input _in)
{
	Output ret;

	float4 worldPosition;
	float4 pos;
	float4 lPos;
	if (_in.flags[0] == 1)
	{
		pos = float4(addJointInfluence(_in).xyz, 1.0f);
	}
	else
	{
		pos = float4(_in.pos.xyz, 1.0f);
	}

	lPos = pos;

	pos = mul(worldMat, pos);
	pos = mul(_in.instance, pos);
	ret.worldPos = pos;
	pos = mul(view, pos);
	pos = mul(proj, pos);
	ret.pos = pos;
	ret.normal = normalize(float4(mul((float3x3)worldMat, _in.normal.xyz), 0));
	ret.normal = normalize(float4(mul((float3x3)_in.instance, ret.normal.xyz), 0));
	ret.uv = _in.uv;
	ret.color = _in.color;

	//Shadow Stuff
	//Putting vertex in light space
	ret.lightViewPosition = mul(worldMat, lPos/*float4(_in.pos.xyz, 1.0f)*/);
	ret.lightViewPosition = mul(_in.instance, lPos/*float4(_in.pos.xyz, 1.0f)*/);
	ret.lightViewPosition = mul(lightViewMatrix, ret.lightViewPosition);
	ret.lightViewPosition = mul(lightProjectionMatrix, ret.lightViewPosition);

	// Calculate the position of the vertex in the world.
	worldPosition = mul(worldMat, lPos /*float4(_in.pos.xyz, 1.0f)*/);
	worldPosition = mul(_in.instance, lPos/*float4(_in.pos.xyz, 1.0f)*/);

	// Determine the light position based on the position of the light and the position of the vertex in the world.
	ret.lightPos = lightPosition - worldPosition;

	// Normalize the light position vector.
	ret.lightPos = normalize(ret.lightPos);

	return ret;
}