#include "Rendering/Bitmap.h"
#include <utility>

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
	Data[Index] = InSet ? 0xFF : 0x00;
}

//----------------------------------------------------------------

void SSGFX::SBitmap::PaintBMP(unsigned int InXStartOffset, unsigned int InYOffset, const SBitmap& InBitmapToPaint)
{
	const unsigned int MinX = InXStartOffset;
	const unsigned int MinY = InYOffset;
	const unsigned int MaxX = InBitmapToPaint.GetWidth() + MinX;
	const unsigned int MaxY = InBitmapToPaint.GetHeight() + MinY;

	for (unsigned int Y = MinY; Y < MaxY; ++Y)
	{
		for (unsigned int X = MinX; X < MaxX; ++X)
		{
			const unsigned int Index = X + Y * Width;
			const unsigned int IndexInPaintBMP = (X - MinX) + (Y - MinY) * InBitmapToPaint.GetWidth();

			Data[Index] |= InBitmapToPaint.Data[IndexInPaintBMP];
		}
	}
}

//----------------------------------------------------------------