#version 330 core

layout (location = 0) in vec3 VertexPosition;
out vec3 Texcoord;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;


void main()
{
    vec4 mvp = Projection * View * vec4(VertexPosition, 1.0);
    gl_Position = mvp.xyzw;
    Texcoord = VertexPosition;
}
