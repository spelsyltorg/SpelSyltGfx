#include "RenderObject.h"
#include "OpenGL.h"

SSGFX::CRenderObject::CRenderObject()
{
	glGenVertexArrays(1, &ID);
	Bind();
}

SSGFX::CRenderObject::~CRenderObject()
{
}

void SSGFX::CRenderObject::SetPrimitiveType(EPrimitiveType Type)
{
	PrimitiveType = Type;
}

void SSGFX::CRenderObject::SetVertexCount(size_t Count)
{
	VertexCount = Count;
}

void SSGFX::CRenderObject::Bind()
{
	glBindVertexArray(ID);
}

void SSGFX::CRenderObject::Render()
{
	if (HasAlpha)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);


	//glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_POLYGON_SMOOTH);
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDrawArrays(PrimitiveType, 0, VertexCount);
}
