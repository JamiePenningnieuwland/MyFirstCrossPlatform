#version 310 es
precision mediump float;

uniform vec3 uLightDir;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;

uniform bool uHasNormalMap;

in vec2 UV;
//in mat3 TBN;
in vec3 normal;
in vec3 tangent;
in vec3 biTangent;

out vec4 FragColor;

void main()
{
    float ambientintensity = 0.2;
    vec3 Lightdir = normalize(uLightDir);

    //Transform to localspace
    vec3 finalNormal = vec3(0.);
    if(uHasNormalMap)
    {
        finalNormal = texture(texture_normal, UV).xyz * 2.0 - 1.0;
    }
    else
    {
        finalNormal = vec3(0.,0.,1.0);
    }
    mat3 TBN = mat3(tangent, biTangent, normal);
    finalNormal = normalize(finalNormal * inverse(TBN));
    vec3 lightcolor = vec3(1.) * max(0.,dot(-Lightdir,finalNormal));
    vec3 ambientcolor = vec3(1.) * ambientintensity;
    vec3  color1 = texture(texture_diffuse, UV).xyz * (lightcolor + ambientcolor);
  //  vec3  color2 = texture(texture_specularN, UV).xyz * (lightcolor + ambientcolor);
    FragColor = vec4(color1, 1.);
}