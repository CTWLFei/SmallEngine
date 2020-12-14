#version 330

const int MAX_POINT_LIGHTS = 5;
const int MAX_SPOT_LIGHTS = 5;
const float PI = 3.1415926;

in vec2 outTexCoord;
in vec3 mvVertexNormal;
in vec3 mvVertexPos;

out vec4 fragColor;

struct Attenuation
{
    float constant;
    float linear;
    float exponent;
};

struct PointLight
{
    vec3 colour;
    // Light position is assumed to be in view coordinates
    vec3 position;
    float intensity;
    Attenuation att;
};

struct SpotLight
{
    PointLight pl;
    vec3 conedir;
    float cutoff;
};

struct DirectionalLight
{
    vec3 colour;
    vec3 direction;
    float intensity;
};

struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    int hasTexture;
    float reflectance;
};

uniform sampler2D texture_sampler;
uniform samplerCube texture_skybox;
uniform vec3 ambientLight;
uniform float specularPower;
uniform Material material;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform DirectionalLight directionalLight;

vec4 ambientC;
vec4 diffuseC;
vec4 speculrC;

float chiGGX(float v)
{
	return v > 0 ? 1 : 0;
}

vec3 halfAngle(vec3 v1, vec3 v2)
{
	return (v1 + v2) / length(v1 + v2);
}

float GGXDistribution(vec3 normal, vec3 half, float alpha)
{
	float NoH = dot(n,h);
    float alpha2 = alpha * alpha;
    float NoH2 = NoH * NoH;
    float den = NoH2 * alpha2 + (1 - NoH2);
    return (chiGGX(NoH) * alpha2) / ( PI * den * den );
}

float GGX_PartialGeometryTerm(vec3 v, vec3 n, vec3 h, float alpha)
{
	float VoH2 = clamp(dot(v,h), 0.0, 1.0);
	float chi = chiGGX( VoH2 / clamp(dot(v,n)) , 0.0, 1.0 );
	VoH2 = VoH2 * VoH2;
	float tan2 = ( 1 - VoH2 ) / VoH2;
	return (chi * 2) / ( 1 + sqrt( 1 + alpha * alpha * tan2 ) );
}

vec3 Fresnel_Schlick(float cosT, vec3 F0)
{
	float factor = pow(1 - cosT, 5);
	vec3 inverseF0 = vec3((1 - F0.x) * factor, (1 - F0.y) * factor, (1 - F0.z) * factor);
	
	return F0 + inverseF0;
}

vec3 GGX_Specular(samplerCube skybox, vec3 normal, vec3 viewVector, float roughness, vec3 F0, vec3& kS)
{
	vec3 reflectionVector = reflect(-viewVector, normal);
}

void main()
{
	vec3 F0 = abs((1.0 - ior) / (1.0 + ior));
	F0 = F0 * F0;
	F0 = mix(F0, materialColour.rgb, metallic);
}