#pragma once
#include <SpelSyltGfx/OpenGL.h>

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

	static void SetScreenAsRenderTarget();
}