#define MAX_LIGHTS 100

Texture2D diffuse;
Texture2D normals;
Texture2D specular;
Texture2D emissive;
SamplerState sam;

struct GenericLight
{
	float4 color;
	float4 direction;
	float4 position;
	float4 extra;
};

cbuffer Lights : register(b0)
{
	GenericLight lights[MAX_LIGHTS];
}

cbuffer Camera : register(b1)
{
	float4 camPos;
}

struct Input
{
	float4 pos : SV_POSITION;
	float4 worldPos : WORLDPOS;
	float4 normal : NORMAL;
	float4 uv : UV;
	float4 color : COLOR;
};

float4 main(Input _in) : SV_TARGET
{
	return diffuse.Sample(sam, _in.uv.xy);
}