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
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float constantAttenuation;
  float spotCosCutoff;
  float quadraticAttenuation;
  float linearAttenuation;
};

// array of lights
uniform Lights light;
// @param material passed from our program
uniform Materials material;
uniform float time;
uniform float repeat;
