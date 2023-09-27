#version 310 es
precision mediump float;

uniform vec3 uLightDir;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;

uniform bool uHasNormalMap;

in vec2 UV;
in mat3 TBN;

out vec4 FragColor;

void main()
{
    float ambientintensity = 0.2;
    vec3 Lightdir = normalize(uLightDir);

    //Transform to localspace
    vec3 normal;
    if(uHasNormalMap)
    {
        vec3 normal = texture(texture_normal, UV).xyz * 2.0 - 1.0;
    }
    else
    {
        normal = vec3(0.,0.,1.0);
    }

    normal = normalize(normal * TBN);
    vec3 lightcolor = vec3(1.) * max(0.,dot(-Lightdir, normal));
    vec3 ambientcolor = vec3(1.) * ambientintensity;
    vec3  color1 = texture(texture_diffuse, UV).xyz * (lightcolor + ambientcolor);
  //  vec3  color2 = texture(texture_specularN, UV).xyz * (lightcolor + ambientcolor);
    FragColor = vec4(color1, 1.);
}