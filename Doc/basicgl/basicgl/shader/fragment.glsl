#version 330 core
out vec4 FragColor;

in VERTEX_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec3 LightPos;
    vec3 ViewPos;
} v;

uniform sampler2D _texture;
uniform vec4 _mainColor;
uniform vec4 _lightColor;
uniform float _ambientStrength;

void main()
{
    vec4 ambient = _ambientStrength * _lightColor;

    vec3 norm = normalize(v.Normal);
    vec3 lightDir = normalize(v.LightPos - v.FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * _lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(-v.FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = specularStrength * spec * _lightColor;

    vec4 lightFactor = (ambient + diffuse + specular);

    ivec2 decalSize = textureSize(_texture, 0);
    if (decalSize != ivec2(1, 1))
        FragColor = _mainColor * texture(_texture, v.TexCoords) * lightFactor;
    else
        FragColor = _mainColor * lightFactor;
}