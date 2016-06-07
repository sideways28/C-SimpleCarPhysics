#version 330  
smooth out vec4 fragColor;

int lightEnabled;
in vec3 fragPosition;
in vec3 outNormal;
smooth in vec2 texCoord;

uniform vec3 m_vCamPos;

#define NR_LIGHTS 1//Number of point lights

struct Light
{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light[NR_LIGHTS];

struct Material
{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    float opacity;
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;

    int texCount;
};
uniform Material material;

//Function Prototype
vec3 CalculatePointLight(Light currentLight, Material mat, vec3 normal, vec3 fragPos, vec3 camDir);

void main()
{
    vec3 result;
    vec3 camDir = normalize(m_vCamPos - fragPosition);
    vec3 norm = normalize(outNormal);

    for(int i = 0; i < NR_LIGHTS; i++)
    {
        result += CalculatePointLight(light[i], material, norm, fragPosition, camDir);
    }

    fragColor = vec4(result, material.opacity);
} 

vec3 CalculatePointLight(Light currentLight, Material mat, vec3 normal, vec3 fragPos, vec3 camDir)
{
    vec3 lightDir = normalize(currentLight.position - fragPos);
    
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(camDir, reflectDir), 0.0), mat.shininess);
    
    // Attenuation
    //float distance = length(light.position - fragPos);
    //float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec3 ambient;
    vec3 diffuse; 
    vec3 specular;
    
    if(material.texCount == 0)//For material with no textures and only color
    {
        ambient = currentLight.ambient * material.ambient;
        diffuse = currentLight.diffuse * (material.diffuse * diff); 
        specular = currentLight.specular * (material.specular * spec);
    }
    else
    {
        ambient = currentLight.ambient * vec3(texture(mat.texture_diffuse1, texCoord));
        diffuse = currentLight.diffuse * diff * vec3(texture(mat.texture_diffuse1, texCoord));
        specular = currentLight.specular * spec * vec3(texture(mat.texture_specular1, texCoord));
    }
    
    //ambient *= attenuation;
    //diffuse *= attenuation;
    //specular *= attenuation;
    
    return (ambient + diffuse + specular);
}