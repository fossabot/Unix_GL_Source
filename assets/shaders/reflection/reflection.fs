#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 Texcoord;


uniform samplerCube skyboxTexture;
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

const float motherOfPearlBrightness = 0.6;

out vec4 FragColor;

void main()
{
  /*
  vec3 Normal = normalize(normal);
  vec3 viewDirection = normalize(direction);
  vec3 reflection = normalize(reflect(viewDirection, Normal));
  float viewDotNormal = max(dot(Normal, viewDirection), 0.0);
  float viewDotNormalInverse = 1.0 - viewDotNormal;
  FragColor = textureCube(skyboxTexture, reflection) * viewDotNormal;
  FragColor += motherOfPearlBrightness * textureCube(skyboxTexture, reflection + vec3(0.1, 0.0, 0.0) * viewDotNormalInverse) * (1.0 - viewDotNormal);
  FragColor += motherOfPearlBrightness * textureCube(skyboxTexture, reflection + vec3(0.0, 0.1, 0.0) * viewDotNormalInverse) * (1.0 - viewDotNormal);
  FragColor += motherOfPearlBrightness * textureCube(skyboxTexture, reflection + vec3(0.0, 0.0, 0.1) * viewDotNormalInverse) * (1.0 - viewDotNormal);
  */
  //FragColor = texture(skyboxTexture, texcoord);
  vec3 I = normalize(Position - CameraPosition);
  vec3 R = reflect(I, normalize(Normal));
  FragColor = texture(skyboxTexture, R);
}
