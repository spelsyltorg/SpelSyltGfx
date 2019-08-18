#version 460 core

uniform float Red;

out vec4 fragColor;

uniform sampler2D tex;
in vec2 uv;

void main()
{
	fragColor = texture2D(tex, uv);
}