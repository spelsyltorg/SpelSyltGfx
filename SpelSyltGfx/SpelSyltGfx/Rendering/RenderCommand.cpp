#include "RenderCommand.h"

SSGFX::CRenderCommand::CRenderCommand(EPrimitiveType Type, size_t VertexCount) :
	PrimitiveType(Type),
	VertexCount(VertexCount)
{
}

void SSGFX::CRenderCommand::Execute()
{
	glDrawArrays(PrimitiveType, 0, VertexCount);
}
