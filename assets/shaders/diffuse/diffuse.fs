#version 330 core


in VertexData {

  vec3 normal;
  vec2 texcoord;
  vec3 light_intensity;

} vertex_data_in;

uniform sampler2D texture_0;
uniform sampler2D texture_1;
uniform sampler2D texture_2;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 CameraPosition;
uniform vec3 CameraDirection;
uniform float DeltaTime;
uniform float Time;


out vec4 FragColor;


void main() {

  FragColor = vec4(vertex_data_in.light_intensity, 1.0) * texture(texture_0, vertex_data_in.texcoord);

}
