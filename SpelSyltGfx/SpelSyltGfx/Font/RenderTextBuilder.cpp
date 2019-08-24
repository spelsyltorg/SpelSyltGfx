#include "Font/RenderTextBuilder.h"
#include "Font/Font.h"

#define MAX(a, b) a < b ? b : a

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
	unsigned int HeightPX = 0;

	unsigned int CurrentX = 0;
	unsigned int CurrentY = 0;

	for (char C : String)
	{
		const SGlyph& Glyph = Font->GetGlyph(C);

		WidthPX += MAX(Glyph.BearingX + Glyph.BMPRep.GetWidth(), Glyph.Advance);

		if (HeightPX < Glyph.BMPRep.GetHeight())
		{
			HeightPX = Glyph.BMPRep.GetHeight();
		}
	}

	BuiltBMP.SetSize(WidthPX, HeightPX);

	unsigned int X = 0;
	unsigned int Y = 0;

	for (char C : String)
	{
		const SGlyph& Glyph = Font->GetGlyph(C);

		BuiltBMP.PaintBMP(X, Y, Glyph.BMPRep);

		X += Glyph.Advance;
	}

}

//----------------------------------------------------------------

const SSGFX::SBitmap& SSGFX::CRenderTextBuilder::GetBMP() const
{
	return BuiltBMP;
}

//----------------------------------------------------------------
