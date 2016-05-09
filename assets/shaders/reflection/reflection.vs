#version 330 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexcoord;

out vec3 Position;
out vec3 Normal;
out vec2 Texcoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 CameraPosition;
uniform vec3 CameraDirection;
uniform float DeltaTime;
uniform float Time;



void main()
{
  gl_Position = Projection * View * Model * vec4(VertexPosition, 1.0f);
  Normal = mat3(transpose(inverse(Model))) * VertexNormal;
  Position = vec3(Model * vec4(VertexPosition, 1.0f));
  Texcoord = VertexTexcoord;
}
