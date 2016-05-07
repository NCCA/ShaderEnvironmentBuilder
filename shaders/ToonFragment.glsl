#version 330 core

/// @brief[in] the vertex normal
in vec3 fragmentNormal;
/// @brief our output fragment colour
out vec4 fragColour;

// @brief light structure
struct Lights
{
    vec4 position;
    vec3 direction;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float spotCosCutoff;
    float spotCosInnerCutoff;
    float spotExponent;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};

uniform Lights light;
in vec3 lightDir;
// out the blinn half vector
in vec3 halfVector;
in vec3 eyeDirection;
in vec3 vPosition;

/// the colour of to use instead of material colour
uniform vec4 Colour;

void main ()
{
	float intensity;
	vec4 color;
	intensity = dot(lightDir,fragmentNormal);

	if (intensity > 0.95)
		color = Colour;
	else if (intensity > 0.5)
		color = Colour/1.5;
	else if (intensity > 0.25)
		color = Colour/3;
	else
		color = Colour/6;
	fragColour = color;
}