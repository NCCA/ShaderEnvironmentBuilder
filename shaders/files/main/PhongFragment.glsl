/// @brief our output fragment colour
layout (location =0) out vec4 fragColour;
/// @brief[in] the vertex normal
in vec3 fragmentNormal;
in vec3 uv;
in vec3 lightDir;
// out the blinn half vector
in vec3 halfVector;
in vec3 eyeDirection;
in vec3 vPosition;

/// @brief a function to compute point light values
/// @param[in] _light the number of the current light
vec4 pointLight()
{
  vec3 N = normalize(fragmentNormal);
  vec3 halfV;
  float ndothv;
  float attenuation;
  vec3 E = normalize(eyeDirection);
  vec3 L = normalize(lightDir);
  float lambertTerm = dot(N,L);
  vec4 diffuse=vec4(0);
  vec4 ambient=vec4(0);
  vec4 specular=vec4(0);
  if (lambertTerm > 0.0)
  {
  float d;            // distance from surface to light position
  vec3 VP;            // direction from surface to light position

  // Compute vector from surface to light position
  VP = vec3 (light.position) - vPosition;

  // Compute distance between surface and light position
    d = length (VP);


    diffuse+=material.diffuse*light.diffuse*lambertTerm;
    ambient+=material.ambient*light.ambient;
    halfV = normalize(halfVector);
    ndothv = max(dot(N, halfV), 0.0);
    specular+=material.specular*light.specular*pow(ndothv, material.shininess);
  }
return ambient + diffuse + specular;
}


void main ()
{
// A very plain monochrome noise
//float n = snoise(uv * 6.0);
//fragColour=pointLight()*vec4(0.5 + 0.5 * vec3(n, n, n), 1.0);

  // Perturb the texcoords with three components of noise
    vec3 uvw = uv + 0.1*vec3(snoise(uv + vec3(0.0, 0.0, time)),
      snoise(uv + vec3(43.0, 17.0, time)),
    snoise(uv + vec3(-17.0, -43.0, time)));
    // Six components of noise in a fractal sum
    float n = snoise(uvw - vec3(0.0, 0.0, time));
    n += 0.5 * snoise(uvw * 2.0 - vec3(0.0, 0.0, time*1.4));
    n += 0.25 * snoise(uvw * 4.0 - vec3(0.0, 0.0, time*2.0));
    n += 0.125 * snoise(uvw * 8.0 - vec3(0.0, 0.0, time*2.8));
    n += 0.0625 * snoise(uvw * 16.0 - vec3(0.0, 0.0, time*4.0));
    n += 0.03125 * snoise(uvw * 32.0 - vec3(0.0, 0.0, time*5.6));
    n = n * 0.7;
    // A "hot" colormap - cheesy but effective
    fragColour = pointLight()*vec4(vec3(1.0, 0.5, 0.0) + vec3(n, n, n), 1.0);


}

