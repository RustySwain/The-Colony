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

float4 applySpecular(float4 _camPos, float _specularPower, float4 _surfacePos, float4 _lightDir, float4 _surfaceNorm, float4 _lightColor, float _specularHardness)
{
	_lightDir = -_lightDir;
	float3 viewDir = normalize(_camPos.xyz - _surfacePos.xyz);
	float NdotL = dot(normalize(_surfaceNorm.xyz), normalize(_lightDir.xyz));
	float intensity = saturate(NdotL);
	float3 H = normalize(normalize(_lightDir.xyz) + viewDir.xyz);
	float NdotH = dot(normalize(_surfaceNorm.xyz), H);
	intensity = pow(saturate(NdotH), _specularPower);
	return intensity * _lightColor * _specularHardness;
}

float calcAttenuation(float4 _position, float4 _worldPos, float _radius)
{
	float attenuation = 1 - saturate(length(_position.xyz - _worldPos.xyz) / _radius);
	attenuation = attenuation * attenuation;
	return attenuation;
}

float4 directionalLight(float4 _direction, float4 _surfaceNormal, float4 _lightColor)
{
	float ratio = saturate(dot(normalize(-_direction.xyz), _surfaceNormal.xyz) * _lightColor.w);
	float4 dirOut = ratio * _lightColor;
	return dirOut;
}

float4 pointLight(float4 _position, float4 _worldPos, float4 _surfaceNormal, float4 _lightColor)
{
	float4 lightDir = float4(normalize(_position.xyz - _worldPos.xyz), 1);
	float ratio = saturate(dot(lightDir.xyz, _surfaceNormal.xyz) * _lightColor.w);
	float4 pointOut = ratio * _lightColor;
	return pointOut;
}

float4 spotLight(float4 _position, float4 _worldPos, float4 _direction, float _coneRatio, float4 _surfaceNormal, float _attenuation, float4 _lightColor)
{
	float4 lightDir = float4(normalize(_position.xyz - _worldPos.xyz), 1);
	float surfaceRatio = saturate(dot(lightDir.xyz, normalize(_direction.xyz)));
	float spotFactor = saturate((surfaceRatio - _coneRatio) * _attenuation);
	float ratio = saturate(dot(normalize(_direction.xyz), _surfaceNormal.xyz) * _lightColor.w);
	float4 spotOut = spotFactor * ratio * _lightColor;
	return spotOut;
}

float4 main(Input _in) : SV_TARGET
{
	float4 textureColor = diffuse.Sample(sam, _in.uv.xy);
	float alpha = textureColor.w;

	float4 normal = normals.Sample(sam, _in.uv.xy);
	if (length(normal) > 0.5f)
	{
		_in.normal = float4(normalize(_in.normal.xyz * normal.xyz), 1);
	}

	float specularRatio = specular.Sample(sam, _in.uv.xy).x;

	float4 lightColor = float4(0, 0, 0, 0);
	bool end = false;
	for (int i = 0; !end && i < MAX_LIGHTS; i++)
	{
		switch (lights[i].position.w)
		{
		case 0: // end of array
		{
			end = true;
			break;
		}
		case 1: // ambient
		{
			lightColor += float4(lights[i].color.xyz * lights[i].color.w, 1);
			break;
		}
		case 2: // directional
		{
			lightColor += directionalLight(lights[i].direction, _in.normal, lights[i].color);
			lightColor += specularRatio * applySpecular(camPos, 1024, _in.worldPos, float4(normalize(lights[i].direction.xyz), 1), _in.normal, lights[i].color, lights[i].color.w);
			break;
		}
		case 3: // point
		{
			float attenuation = calcAttenuation(lights[i].position, _in.worldPos, lights[i].direction.w);
			float4 lightDir = float4(lights[i].position.xyz - _in.worldPos.xyz, 1);
			lightColor += attenuation * pointLight(lights[i].position, _in.worldPos, _in.normal, lights[i].color);
			lightColor += specularRatio * attenuation * applySpecular(camPos, 1024, _in.worldPos, lightDir, _in.normal, lights[i].color, lights[i].color.w);
			break;
		}
		case 4: // spot
		{
			lightColor += spotLight(lights[i].position, _in.worldPos, lights[i].direction, lights[i].extra.y, _in.normal, lights[i].extra.x, lights[i].color);
			lightColor += specularRatio * applySpecular(camPos, 1024, _in.worldPos, float4(normalize(lights[i].direction.xyz), 1), _in.normal, lights[i].color, lights[i].color.w);
			break;
		}
		}
	}

	float4 returnColor = lightColor * textureColor;
	float4 emiss = emissive.Sample(sam, _in.uv.xy);
	return float4(returnColor.xyz, alpha) * _in.color + emiss;
}