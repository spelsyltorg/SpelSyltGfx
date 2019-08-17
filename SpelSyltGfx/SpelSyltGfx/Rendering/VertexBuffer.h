#pragma once
#include "OpenGL.h"

namespace SSGFX
{
	class CVertexBuffer
	{
	public:
		void Create(float* Data, size_t DataSize, size_t InAttributeSize);
		void Bind(unsigned int Slot);
		void Unbind();

	private:
		unsigned int ID;
		size_t AttributeSize;
	};
}