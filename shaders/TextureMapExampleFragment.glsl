#version 330 core

uniform sampler2D tex;

/// @brief[in] the vertex normal
in vec3 fragmentNormal;
/// @brief our output fragment colour
out vec4 fragColour;

in vec2 vertUV;

layout (location=0) out vec4 outColour;

/// @brief material structure
struct Materials
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};

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
// @param material passed from our program
uniform Materials material;

uniform Lights light;
in vec3 lightDir;
// out the blinn half vector
in vec3 halfVector;
in vec3 eyeDirection;
in vec3 vPosition;

/// the colour of to use instead of material colour
uniform vec4 Colour;

vec4 pointLight()
{
  vec3 N = normalize(fragmentNormal);
  vec3 halfV;
  float ndothv;
  float attenuation;
  vec3 E = normalize(eyeDirection);
  vec3 L = normalize(lightDir);
  float lambertTerm = dot(N,L);
  vec4 diffuse=vec4(0.25,0.4,0.43,1.0);
  vec4 ambient=vec4(0,0,0,1.0);
  vec4 specular=vec4(0);
  if (lambertTerm > 0.0)
  {
  float d;            // distance from surface to light position
  vec3 VP;            // direction from surface to light position

  // Compute vector from surface to light position
  VP = vec3 (light.position) - vPosition;

  // Compute distance between surface and light position
    d = length (VP);
    attenuation = 1.f / (light.constantAttenuation +
                       light.linearAttenuation * d +
                       light.quadraticAttenuation * d * d);

    diffuse+=Colour*light.diffuse*lambertTerm*attenuation;
    ambient+=material.ambient*light.ambient*attenuation;
    halfV = normalize(halfVector);
    ndothv = max(dot(N, halfV), 0.0);
    specular+=(material.specular*6.5)*light.specular*pow(ndothv, (material.shininess*120.0))* attenuation;
    outColour = (ambient) + diffuse + (specular*0.65)-(texture(tex,vertUV)*0.5);  
  }
return outColour;
}


void main ()
{

fragColour=pointLight();
}


