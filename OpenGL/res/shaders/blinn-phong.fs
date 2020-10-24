#version 330 core

const int Ambient =      1;
const int Diffuse =      2;
const int Specular =     4;
const int DiffuseTex =   8;
const int SpecularTex = 16;

const int DirectionalLight = 0;
const int PointLight = 1;
const int SpotLight = 2;

struct Material
{
    int type;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    sampler2D ambientTex;
    sampler2D diffuseTex;
    sampler2D specularTex;   
    
    float shininess;
}; 

struct Light
{
    int type;

    vec3 position;
    vec3 direction;
    float innerCutoff;
    float outerCutoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;

in vec2 texCoord;
in vec3 fragPosition;  
in vec3 normal;

uniform vec3 viewPosition;
uniform Material material;
uniform int numLights;
uniform Light lights[16];
uniform float gamma = 2.2;

vec4 getAmbient()
{
    if ((material.type & DiffuseTex) == DiffuseTex)
    {
        return texture2D(material.diffuseTex, texCoord);
    }
    return vec4(material.ambient, 1.0);
}

vec4 getDiffuse()
{
    if ((material.type & DiffuseTex) == DiffuseTex)
    {
        return texture2D(material.diffuseTex, texCoord);
    }
    return vec4(material.diffuse, 1.0);
}

vec4 getSpecular()
{
    if ((material.type & SpecularTex) == SpecularTex)
    {
        return texture2D(material.specularTex, texCoord);
    }
    return vec4(material.specular, 1.0);
}

vec3 calculateDirectionalLight(Light light, vec3 mambient, vec3 mdiffuse, vec3 mspecular)
{
    //ambient
    vec3 ambient = light.ambient * mambient;
  	
    //diffuse
    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(-light.direction);  
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * mdiffuse;  
    
    //specular
    vec3 viewDirection = normalize(viewPosition - fragPosition);
    vec3 halfwayDirection = normalize(lightDirection + viewDirection);
    float spec = pow(max(dot(norm, halfwayDirection), 0.0), material.shininess * 128.0);
    spec *= diff;
    vec3 specular = light.specular * spec * mspecular;

    return ambient + diffuse + specular;
}

vec3 calculatePointLight(Light light, vec3 mambient, vec3 mdiffuse, vec3 mspecular)
{
    //ambient
    vec3 ambient = light.ambient * mambient;
  	
    //diffuse
    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(light.position - fragPosition);  
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * mdiffuse;  
    
    //specular
    vec3 viewDirection = normalize(viewPosition - fragPosition);
    vec3 halfwayDirection = normalize(lightDirection + viewDirection);
    float spec = pow(max(dot(norm, halfwayDirection), 0.0), material.shininess * 128.0);
    spec *= diff;
    vec3 specular = light.specular * spec * mspecular;

    //attenuation
    float distance = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        
    return attenuation * (ambient + diffuse + specular);
}

vec3 calculateSpotLight(Light light, vec3 mambient, vec3 mdiffuse, vec3 mspecular)
{
    //ambient
    vec3 ambient = light.ambient * mambient;
  	
    //diffuse
    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(light.position - fragPosition);  
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * mdiffuse;  
    
    //specular
    vec3 viewDirection = normalize(viewPosition - fragPosition);
    vec3 halfwayDirection = normalize(lightDirection + viewDirection);
    float spec = pow(max(dot(norm, halfwayDirection), 0.0), material.shininess * 128.0);
    spec *= diff;
    vec3 specular = light.specular * spec * mspecular;

    //attenuation
    float distance = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    //spotlight (soft edges)
    float theta = dot(lightDirection, normalize(-light.direction)); 
    float epsilon = (light.innerCutoff - light.outerCutoff);
    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
        
    return attenuation * (ambient + intensity * (diffuse + specular));
}

void main()
{
    vec3 result = vec3(0.0);
    vec4 ambient = getAmbient();
    vec4 diffuse = getDiffuse();
    vec4 specular = getSpecular();

    for (int i=0;i<numLights;++i)
    {
        if  (lights[i].type == DirectionalLight)
            result += calculateDirectionalLight(lights[i], ambient.rgb, diffuse.rgb, specular.rgb);
        if  (lights[i].type == PointLight)
            result += calculatePointLight(lights[i], ambient.rgb, diffuse.rgb, specular.rgb);
        if  (lights[i].type == SpotLight)
            result += calculateSpotLight(lights[i], ambient.rgb, diffuse.rgb, specular.rgb);
    }

    FragColor = vec4(result, 1.0) * vec4(diffuse.a);
    FragColor.rgb = pow(FragColor.rgb, vec3(1.0/gamma));
}