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

    FragColor = texture(screenTexture, vertex_data_in.texcoord);

}
