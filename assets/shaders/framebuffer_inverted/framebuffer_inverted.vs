#version 330 core

layout (location = 0) in vec2 VertexPosition;
layout (location = 1) in vec2 VertexTexcoord;

out VertexData {

  vec2 texcoord;

} vertex_data_out;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 CameraPosition;
uniform vec3 CameraDirection;
uniform float DeltaTime;
uniform float Time;



void main() {

  gl_Position = vec4(VertexPosition, 0.0, 1.0);
  vertex_data_out.texcoord = VertexTexcoord;

}
