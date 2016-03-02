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


void main()
{
  float rt_w = 100;
  float rt_h = 100;
  float vx_offset = 50;

  float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
  float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );

  vec3 tc = vec3(1.0, 0.0, 0.0);
  if (vertex_data_in.texcoord.x < (vx_offset-0.01))
  {
    vec2 uv = vertex_data_in.texcoord.xy;
    tc = texture(screenTexture, uv).rgb * weight[0];
    for (int i=1; i<3; i++)
    {
      tc += texture(screenTexture, uv + vec2(offset[i])/rt_w, 0.0).rgb * weight[i];
      tc += texture(screenTexture, uv - vec2(offset[i])/rt_w, 0.0).rgb * weight[i];
    }
  } else if (vertex_data_in.texcoord.x>=(vx_offset+0.01)) {
    tc = texture(screenTexture, vertex_data_in.texcoord.xy).rgb;
  }
  FragColor = vec4(tc, 1.0);
}
