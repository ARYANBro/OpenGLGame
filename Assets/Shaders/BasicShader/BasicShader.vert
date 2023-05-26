#version 460

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 v_TexCoords;

layout(std140, binding = 0) uniform UniformData
{
    mat4 u_Projection;
    mat4 u_View;
};

uniform mat4 u_Model;

void main()
{   
    vec4 pos = u_Projection * u_View * u_Model * vec4(a_Position, 1.0f);
    gl_Position = pos;
    v_TexCoords = a_TexCoords;
}