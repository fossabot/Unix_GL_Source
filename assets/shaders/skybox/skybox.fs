#version 330 core

in vec3 Texcoord;
out vec4 FragColor;

uniform samplerCube skyboxTexture;

void main()
{
  vec4 textureReflection = texture(skyboxTexture, Texcoord);
  FragColor = textureReflection;
}
