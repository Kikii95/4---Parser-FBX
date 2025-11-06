#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoor;
layout (location = 2) in vec3 aNormal;

out VERTEX_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec3 LightPos;
    vec3 ViewPos;
} v;

uniform mat4 _projection;
uniform mat4 _view;
uniform mat4 _model;
uniform vec3 _lightPos;

void main()
{
    gl_Position = _projection * _view * _model * vec4(aPos, 1.0);
    v.TexCoords = vec2(aTexCoor.x, 1-aTexCoor.y);
    v.FragPos = vec3(_view * _model * vec4(aPos, 1.0));
    v.Normal = vec3(_view * transpose(inverse(_model)) * vec4(aNormal, 1.0));
    v.LightPos = vec3(_view * vec4(_lightPos, 1));
    v.ViewPos = vec3(_view * vec4(0, 0, 0, 1));
}