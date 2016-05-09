#version 330 core

in vec3 Texcoord;
out vec4 FragColor;

uniform samplerCube skyboxTexture;

void main()
{
  vec4 textureReflection = texture(skyboxTexture, Texcoord);
  FragColor = vec4(1.0 - textureReflection.x, 1.0 - textureReflection.y, 1.0 - textureReflection.z, 1.0);
}
