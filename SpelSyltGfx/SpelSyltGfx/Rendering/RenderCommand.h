#pragma once
#include "GfxInclude.h"

namespace SSGFX
{
	class CRenderCommand
	{
	public:

		CRenderCommand(EPrimitiveType Type, size_t VertexCount);

		void Execute();

	private:

		const EPrimitiveType PrimitiveType;
		const size_t VertexCount;
	};
}