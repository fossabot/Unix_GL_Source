#version 330 core

in VertexData {

  vec2 texcoord;

} vertex_data_in;

uniform sampler2D screenTexture;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 CameraPosition;
uniform vec3 CameraDirection;
uniform float DeltaTime;
uniform float Time;

out vec4 FragColor;


void main() {

  vec2 Resolution = vec2(1366, 768);
  float scale = 4.0;

  if (mod(floor(vertex_data_in.texcoord.y * Resolution.y / scale), 2.0) == 0.0)
      FragColor = vec4(0.0, 0.0, 0.0, 1.0);
  else
      FragColor = texture(screenTexture, vertex_data_in.texcoord);
}
