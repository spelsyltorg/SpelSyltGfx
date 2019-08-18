#version 460 core

layout(location = 0) in vec4 vertexPosXYandUV;
out vec2 uv;

uniform mat3 model;

void main()
{
	gl_Position = vec4(model * vec3(vertexPosXYandUV.xy,0.0), 1.0);
	uv = vertexPosXYandUV.zw;
}