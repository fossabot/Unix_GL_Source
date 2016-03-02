#version 330 core

layout(triangles) in;
layout(line_strip, max_vertices = 12) out;

in VERTEX_DATA {

  vec3 position;
  vec3 normal;
  vec2 texcoord;
  vec3 light_intensity;

} vertex_data_in[];

out GEOMETRY_DATA {

  vec2 texcoord;
  vec3 light_intensity;

} geometry_data_out;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 CameraPosition;
uniform vec3 CameraDirection;
uniform float DeltaTime;
uniform float Time;




void generateNormal(int index) {

  gl_Position = gl_in[index].gl_Position;
  geometry_data_out.texcoord = vertex_data_in[index].texcoord;
  geometry_data_out.light_intensity = vertex_data_in[index].light_intensity;
  EmitVertex();

  float length = 0.2f;

  gl_Position = gl_in[index].gl_Position + vec4(vertex_data_in[index].normal, 0.5f) * length;
  EmitVertex();

  EndPrimitive();
}

void pushVertex(int indexa, int indexb) {

  gl_Position = Projection * View * Model * vec4(vertex_data_in[indexa].position, 1.0);
  geometry_data_out.texcoord = vertex_data_in[indexa].texcoord;
  geometry_data_out.light_intensity = vertex_data_in[indexa].light_intensity;
  EmitVertex();

  gl_Position = Projection * View * Model * vec4(vertex_data_in[indexb].position, 1.0);
  geometry_data_out.texcoord = vertex_data_in[indexb].texcoord;
  geometry_data_out.light_intensity = vertex_data_in[indexb].light_intensity;
  EmitVertex();

  EndPrimitive();

}

void main() {

  generateNormal(0);
  generateNormal(1);
  generateNormal(2);

  pushVertex(0,1);
  pushVertex(1,2);
  pushVertex(2,0);

}
