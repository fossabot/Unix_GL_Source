#version 330 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexcoord;

out VertexData {

  vec3 normal;
  vec2 texcoord;
  vec3 light_intensity;

} vertex_data_out;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 CameraPosition;
uniform vec3 CameraDirection;
uniform float DeltaTime;
uniform float Time;


struct LightInfo {
  vec4 Position;
  vec3 La;
  vec3 Ld;
  vec3 Ls;
};

struct MaterialInfo {
  vec3 Ka;
  vec3 Kd;
  vec3 Ks;
  float Shininess;
};

void getEyeSpace(mat3 normalMatrix, out vec3 norm, out vec4 position)
{
  norm = normalize(normalMatrix * VertexNormal);
  position = View * Model * vec4(VertexPosition, 1.0);
}

vec3 phongModel(LightInfo Light, MaterialInfo Material, vec4 position, vec3 norm)
{
  vec3 s = normalize(vec3(Light.Position - position));
  vec3 v = normalize(-position.xyz);
  vec3 r = reflect(-s, norm);
  vec3 ambient = Light.La * Material.Ka;
  float sDotn = max(dot(s, norm), 0.0);
  vec3 diffuse = Light.Ld * Material.Kd * sDotn;
  vec3 specular = vec3(0.0);
  if(sDotn > 0.0)
    specular = Light.Ls * Material.Ks * pow(max(dot(r,v), 0.0), Material.Shininess);

  return ambient + diffuse + specular;
}


void main() {

  vec3 LightIntensity;
  LightInfo Light;
  Light.Position = vec4(5.0f, 2.0f, 5.0f, 1.0f);
  Light.La = vec3(1.0f, 1.0f, 1.0f);
  Light.Ld = vec3(0.8f, 0.8f, 0.8f);
  Light.Ls = vec3(0.4f, 0.4f, 0.4f);

  MaterialInfo Material;
  Material.Ka = vec3(0.8, 0.8, 0.8);
  Material.Kd = vec3(1.0, 1.0, 1.0);
  Material.Ks = vec3(0.5, 0.5, 0.5);
  Material.Shininess = 0.1f;


	mat3 normalMatrix = transpose(inverse(mat3(View * Model)));

  vec3 eyeNorm;
  vec4 eyePosition;

  getEyeSpace(normalMatrix, eyeNorm, eyePosition);
  LightIntensity = phongModel(Light, Material, eyePosition, eyeNorm);

  gl_Position = Projection * View * Model * vec4(VertexPosition, 1.0);

  vertex_data_out.normal = VertexNormal;
  vertex_data_out.texcoord = VertexTexcoord;
  vertex_data_out.light_intensity = LightIntensity;
}
