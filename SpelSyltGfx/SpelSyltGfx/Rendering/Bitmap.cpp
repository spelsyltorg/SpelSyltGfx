#include "Rendering/Bitmap.h"
#include <utility>

#ifdef _DEBUG
#include <cassert>
#endif

//----------------------------------------------------------------

SSGFX::SBitmap::SBitmap()
	: Width(0)
	, Height(0)
	, DataByteSize(0)
	, Data(nullptr)
{
}

//----------------------------------------------------------------

SSGFX::SBitmap::~SBitmap()
{
	if (Data)
	{
		delete[DataByteSize] Data;
		Data = nullptr;
	}
}

//----------------------------------------------------------------

void SSGFX::SBitmap::SetSize(unsigned int InW, unsigned int InH)
{
	if (Data)
	{
		delete[DataByteSize] Data;
		Data = nullptr;
	}

	Width = InW;
	Height = InH;
	DataByteSize = (InW * InH);
	Data = new unsigned char[DataByteSize];

	for (auto i = 0u; i < DataByteSize; ++i)
	{
		Data[i] = 0x00;
	}

}

//----------------------------------------------------------------

void SSGFX::SBitmap::SetData(unsigned char* InData, unsigned int InDataSize)
{
	unsigned int SizeToTake = InDataSize;
	if (InDataSize > DataByteSize)
	{
		const unsigned int InDataByteOffset = InDataSize - DataByteSize;
		SizeToTake = InDataSize - InDataByteOffset;
	}

	memcpy_s(Data, DataByteSize, InData, SizeToTake);
}

//----------------------------------------------------------------

void SSGFX::SBitmap::Paint(unsigned int InX, unsigned int InY, bool InSet)
{
	const unsigned int Index = InX + InY * Width;

#ifdef _DEBUG
	assert(Index < DataByteSize && "Trying to write out of bounds!");
#endif

	Data[Index] = InSet ? 0xFF : 0x00;
}

//----------------------------------------------------------------

void SSGFX::SBitmap::PaintBMP(unsigned int InXStartOffset, unsigned int InYOffset, const SBitmap& InSourceBMP)
{
	const unsigned int SourceH = InSourceBMP.GetHeight();
	const unsigned int SourceW = InSourceBMP.GetWidth();

	for (unsigned int Y = 0; Y < SourceH; ++Y)
	{
		for (unsigned int X = 0; X < SourceW; ++X)
		{
			const unsigned int DestX = X + InXStartOffset;
			const unsigned int DestY = Y + InYOffset;

			if (DestX >= Width || DestY >= Height)
			{
				continue;
			}

			const unsigned int SourceIndex = X + Y * SourceW;
			const unsigned int DestIndex = DestX + DestY * Width;

#ifdef _DEBUG
			assert(DestIndex < DataByteSize && "Will write out of bounds");
			assert(SourceIndex < InSourceBMP.DataByteSize && "Will read out of bounds");
#endif

			Data[DestIndex] |= InSourceBMP.Data[SourceIndex];
		}
	}
}

//----------------------------------------------------------------