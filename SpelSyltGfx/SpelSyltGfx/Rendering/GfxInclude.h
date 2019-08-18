#pragma once
#include "OpenGL.h"

namespace SSGFX
{
	enum ETexFormat : GLenum
	{
		RED = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		RGBA = GL_RGBA,

		DEPTH = GL_DEPTH_COMPONENT
	};

	enum EPrimitiveType : GLenum
	{
		Triangles = GL_TRIANGLES,
		TriangleStrip = GL_TRIANGLE_STRIP,
		TriangleFan = GL_TRIANGLE_FAN,

		Points = GL_POINTS,

		Lines = GL_LINES,
		LineStrip = GL_LINE_STRIP,
		LineLoop = GL_LINE_LOOP,
	};

	struct SColor
	{
		float r = 0.f;
		float g = 0.f;
		float b = 0.f;
		float a = 0.f;
	};

	static void SetScreenAsRenderTarget();
}