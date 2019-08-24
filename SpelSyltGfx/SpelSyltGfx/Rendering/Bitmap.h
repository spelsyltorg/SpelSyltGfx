#pragma once

namespace SSGFX
{
	struct SBitmap
	{
	public:
		SBitmap();
		SBitmap(const SBitmap& InOther) = delete;
		SBitmap(SBitmap&& InOther) = delete;
		~SBitmap();
		void SetSize(unsigned int InW, unsigned int InH);
		void SetData(unsigned char* InData, unsigned int InDataSize);
		void Paint(unsigned int InX, unsigned int InY, bool InSet);
		void PaintBMP(unsigned int InXStartOffset, unsigned int InYOffset, const SBitmap& InBitmapToPaint);

		unsigned int GetWidth() const { return Width; };
		unsigned int GetHeight() const { return Height; };
		const unsigned char* GetData() const { return Data;  };

	private:
		unsigned int Width;
		unsigned int Height;
		unsigned int DataByteSize;
		unsigned char* Data;
	};
}