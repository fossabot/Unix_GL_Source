#version 330 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexcoord;

out vec3 Normal;
out vec3 Position;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
    gl_Position = Projection * View * Model * vec4(VertexPosition, 1.0f);
    Normal = mat3(transpose(inverse(Model))) * VertexNormal;
    Position = vec3(Model * vec4(VertexPosition, 1.0f));
}
