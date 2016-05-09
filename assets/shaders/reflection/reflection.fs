#version 330 core

in vec3 Normal;
in vec3 Position;
out vec4 color;

uniform samplerCube skyboxTexture;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 CameraPosition;
uniform vec3 CameraDirection;
uniform float DeltaTime;
uniform float Time;

void main()
{
    vec3 I = normalize(Position - CameraPosition);
    vec3 R = reflect(I, normalize(Normal));
    vec4 textureReflection = texture(skyboxTexture, R);
    color = vec4(1.0 - textureReflection.x, 1.0 - textureReflection.y, 1.0 - textureReflection.z, 1.0);
}
