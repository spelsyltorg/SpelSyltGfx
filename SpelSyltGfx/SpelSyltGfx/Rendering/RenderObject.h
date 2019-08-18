#pragma once
#include "GfxInclude.h"

namespace SSGFX
{
	class CRenderObject
	{
	public:
		CRenderObject();
		~CRenderObject();

		void SetPrimitiveType(EPrimitiveType Type);
		void SetVertexCount(size_t Count);

		void Bind();
		void Render();

	private:
		unsigned int ID;

		EPrimitiveType PrimitiveType;
		size_t VertexCount;
		bool HasAlpha = true;
	};
}