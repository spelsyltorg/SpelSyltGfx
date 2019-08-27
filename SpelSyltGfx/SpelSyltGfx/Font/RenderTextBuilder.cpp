#include "Font/RenderTextBuilder.h"
#include "Font/Font.h"

#define MAX(a, b) a < b ? b : a
#define MIN(a, b) a < b ? a : b

//----------------------------------------------------------------

SSGFX::CRenderTextBuilder::CRenderTextBuilder()
	: Font(nullptr)
	, String("")
	, VertexBuffer()
{
}

//----------------------------------------------------------------

SSGFX::CRenderTextBuilder::CRenderTextBuilder(const CRenderTextBuilder& InOther)
	:Font(InOther.Font)
	, String(InOther.String)
	, VertexBuffer(InOther.VertexBuffer)
{
}

//----------------------------------------------------------------

SSGFX::CRenderTextBuilder::CRenderTextBuilder(const CFont& InFont)
	: Font(&InFont)
	, String("")
	, VertexBuffer()
{
}

//----------------------------------------------------------------

void SSGFX::CRenderTextBuilder::SetFont(const CFont& InFont)
{
	Font = &InFont;
}

//----------------------------------------------------------------

void SSGFX::CRenderTextBuilder::SetString(const std::string& InString)
{
	String = InString;
	Build();
}

//----------------------------------------------------------------

void SSGFX::CRenderTextBuilder::Build()
{
	unsigned int WidthPX = 0;
	unsigned int CurrentX = 0;
	unsigned int CurrentY = 0;
	int LowestYMin = 0;
	int HighestYMax = 0;

	for (char C : String)
	{
		const SGlyph& Glyph = Font->GetGlyph(C);

		if (C == '\n')
		{
			//Start a new line
		}

		WidthPX += Glyph.Advance; // MAX(Glyph.BMPRep.GetWidth(), Glyph.Advance);

		HighestYMax = MAX(HighestYMax, Glyph.YMax);
		LowestYMin = MIN(LowestYMin, Glyph.YMin);
	}

	BuiltBMP.SetSize(WidthPX, HighestYMax - LowestYMin);

	unsigned int X = 0;
	unsigned int Y = HighestYMax;

	int FirstBearing = 0;

	for (unsigned int i = 0; i < String.size(); ++i)
	{
		const SGlyph& Glyph = Font->GetGlyph(String[i]);

		if (i == 0)
		{
			FirstBearing = Glyph.BearingX;
		}

		BuiltBMP.PaintBMP(X + Glyph.BearingX - FirstBearing, Y - Glyph.BearingY, Glyph.BMPRep);

		//for (unsigned int y = 0; y < BuiltBMP.GetHeight(); ++y)
		//{
		//	BuiltBMP.Paint(X + 2, y, true);
		//	BuiltBMP.Paint(X + 1, y, true);
		//	BuiltBMP.Paint(X, y, true);
		//}

		X += Glyph.Advance;// +Glyph.BearingX;
	}

}

//----------------------------------------------------------------

const SSGFX::SBitmap& SSGFX::CRenderTextBuilder::GetBMP() const
{
	return BuiltBMP;
}

//----------------------------------------------------------------
