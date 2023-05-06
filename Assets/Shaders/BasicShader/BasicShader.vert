#version 460

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 v_TexCoords;

layout(row_major, std140, binding = 0) uniform UniformData
{
    mat4 u_Projection;
};

uniform mat4 u_World;

void main()
{   
    gl_Position = vec4(a_Position, 1.0f) * u_World * u_Projection;
    v_TexCoords = a_TexCoords;
}