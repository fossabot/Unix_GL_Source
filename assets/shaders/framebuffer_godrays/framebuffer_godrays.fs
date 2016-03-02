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

  int samples = 128;
  float intensity = 0.025, decay = 0.96875;
  vec2 texcoord = vec2(vertex_data_in.texcoord), direction = vec2(0.5) - texcoord;
  direction /= samples;
  vec3 color = texture(screenTexture, texcoord).rgb;
  for(int si = 0; si < samples; si++) {
    color += texture(screenTexture, texcoord).rgb * intensity;
    intensity *= decay;
    texcoord += direction;
  }
  FragColor = vec4(color, 1.0);

}
