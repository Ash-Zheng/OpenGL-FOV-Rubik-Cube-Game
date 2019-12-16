#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 ourColor;
in vec3 Normal;
in vec3 FragPos; 

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform vec3 viewPos;
uniform Material material;
uniform Light light1,light2,light3,light4;

vec3 oneLight(Light light)
{
	// ambient
    vec3 ambient = light.ambient * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
        
	//vec3 result = diffuse;
    //vec3 result = ambient + diffuse + specular;
	vec3 result = ambient +diffuse +specular;
	return result;
}

void main()
{
	vec3 result=oneLight(light1);
	result+=oneLight(light2);
	result+=oneLight(light3);
	result+=oneLight(light4);
	
	//FragColor = vec4(result, 1.0);
	//FragColor = mix(texture(ourTexture1, TexCoord),vec4(result, 1.0),0.9);
	//FragColor = texture(ourTexture1, TexCoord)*vec4(result, 1.0);
	//FragColor = ;
	//FragColor = texture(ourTexture1, TexCoord);
	FragColor = mix(texture(ourTexture2, TexCoord),vec4(result, 1.0)*texture(ourTexture1, TexCoord),0.8);
}
