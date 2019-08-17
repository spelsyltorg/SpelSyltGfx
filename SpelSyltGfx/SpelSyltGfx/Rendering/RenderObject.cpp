#include "RenderObject.h"
#include "OpenGL.h"

SSGFX::CRenderObject::CRenderObject()
{
	glGenVertexArrays(1, &ID);
}

SSGFX::CRenderObject::~CRenderObject()
{
}

void SSGFX::CRenderObject::Bind()
{
	glBindVertexArray(ID);
}
