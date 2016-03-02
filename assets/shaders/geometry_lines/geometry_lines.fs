#version 330 core

in GEOMETRY_DATA {

	vec2 texcoord;
	vec3 light_intensity;

} geometry_data_in;

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

void main()
{
	if(cos(Time / 400) > 0.89)
		FragColor = vec4(cos(Time) * geometry_data_in.light_intensity, 1.0);
	else
		FragColor = texture(texture_0, geometry_data_in.texcoord);
}
