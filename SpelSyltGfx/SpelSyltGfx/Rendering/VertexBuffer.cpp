#include "VertexBuffer.h"

void SSGFX::CVertexBuffer::Create(float * Data, size_t DataSize, size_t InAttributeSize)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, DataSize, Data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	AttributeSize = InAttributeSize;
}

void SSGFX::CVertexBuffer::Bind(unsigned int Slot)
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glVertexAttribPointer(Slot, AttributeSize, GL_FLOAT, GL_FALSE, AttributeSize * sizeof(float), (void*)0);
	glEnableVertexAttribArray(Slot);
}

void SSGFX::CVertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
