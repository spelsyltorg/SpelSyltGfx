#include "Rendering/Color.h"

//----------------------------------------------------------------

SSGFX::FComposedColor SSGFX::ComposeColor(FChannel InR, FChannel InG, FChannel InB, FChannel InA)
{
	FComposedColor ComposedR;
	FComposedColor ComposedG;
	FComposedColor ComposedB;
	FComposedColor ComposedA;

	ComposedR = InR;
	ComposedG = InG;
	ComposedB = InB;
	ComposedA = InA;

	FComposedColor FinalComposed = 0;
	FinalComposed |= ComposedR << R_OFFSET;
	FinalComposed |= ComposedG << G_OFFSET;
	FinalComposed |= ComposedB << B_OFFSET;
	FinalComposed |= ComposedA;

	return FinalComposed;
}

//----------------------------------------------------------------

SSGFX::FComposedColor SSGFX::ComposeColor(FChannel InR, FChannel InG, FChannel InB)
{
	FComposedColor ComposedR;
	FComposedColor ComposedG;
	FComposedColor ComposedB;

	ComposedR = InR;
	ComposedG = InG;
	ComposedB = InB;

	FComposedColor FinalComposed = 0;
	FinalComposed |= ComposedR << R_OFFSET;
	FinalComposed |= ComposedG << G_OFFSET;
	FinalComposed |= ComposedB << B_OFFSET;

	return FinalComposed;
}

//----------------------------------------------------------------

//----------------------------------------------------------------
// Begin RGBA Color
//----------------------------------------------------------------

//----------------------------------------------------------------

SSGFX::SRGBAColor::SRGBAColor()
	: ComposedColor(COLOR_TRANSPARENT)
{
}

//----------------------------------------------------------------

SSGFX::SRGBAColor::SRGBAColor(const SRGBAColor& InOther)
	: ComposedColor(InOther.ComposedColor)
{
}

//----------------------------------------------------------------

SSGFX::SRGBAColor::SRGBAColor(const FComposedColor InComposedColor)
	: ComposedColor(InComposedColor)
{
}

//----------------------------------------------------------------

SSGFX::SRGBAColor::SRGBAColor(const FChannel InRed, const FChannel InGreen, const FChannel InBlue, const FChannel InAlpha)
	: ComposedColor(SSGFX::ComposeColor(InRed, InGreen, InBlue, InAlpha))
{
}

//----------------------------------------------------------------

SSGFX::SRGBARenderColor SSGFX::SRGBAColor::DecomposeToRenderColor() const
{
	SRGBARenderColor RenderColor;
	RenderColor.Red = static_cast<float>(R()) / 255.f;
	RenderColor.Green = static_cast<float>(G()) / 255.f;
	RenderColor.Blue = static_cast<float>(B()) / 255.f;
	RenderColor.Alpha = static_cast<float>(A()) / 255.f;

	return RenderColor;
}

//----------------------------------------------------------------

SSGFX::SRGBAColor& SSGFX::SRGBAColor::operator=(const SRGBAColor& InRHS)
{
	ComposedColor = InRHS.ComposedColor;
	return *this;
}

//----------------------------------------------------------------

SSGFX::SRGBAColor& SSGFX::SRGBAColor::operator=(const FComposedColor InRHS)
{
	ComposedColor = InRHS;
	return *this;
}

//----------------------------------------------------------------

bool SSGFX::SRGBAColor::operator==(const SRGBAColor& InRHS) const
{
	return ComposedColor == InRHS.ComposedColor;
}

//----------------------------------------------------------------

bool SSGFX::SRGBAColor::operator==(const FComposedColor InRHS) const
{
	return ComposedColor == InRHS;
}

//----------------------------------------------------------------

//----------------------------------------------------------------
// End RGBA Color
//----------------------------------------------------------------

//----------------------------------------------------------------
// Begin RGB Color
//----------------------------------------------------------------

//----------------------------------------------------------------

SSGFX::SRGBColor::SRGBColor()
	: ComposedColor(COLOR_TRANSPARENT)
{
}

//----------------------------------------------------------------

SSGFX::SRGBColor::SRGBColor(const SRGBColor& InOther)
	: ComposedColor(InOther.ComposedColor)
{
}

//----------------------------------------------------------------

SSGFX::SRGBColor::SRGBColor(FComposedColor InComposedColor)
	: ComposedColor(InComposedColor << 8)
{
}

//----------------------------------------------------------------

SSGFX::SRGBColor::SRGBColor(FChannel InRed, FChannel InGreen, FChannel InBlue)
	: ComposedColor(ComposeColor(InRed, InGreen, InBlue))
{
}

//----------------------------------------------------------------

SSGFX::SRGBRenderColor SSGFX::SRGBColor::DecomposeToRenderColor() const
{
	SRGBRenderColor RenderColor;
	RenderColor.Red = static_cast<float>(R()) / 255.f;
	RenderColor.Green = static_cast<float>(G()) / 255.f;
	RenderColor.Blue = static_cast<float>(B()) / 255.f;

	return RenderColor;
}

//----------------------------------------------------------------

SSGFX::SRGBColor& SSGFX::SRGBColor::operator=(const SRGBColor& InRHS)
{
	ComposedColor = InRHS.ComposedColor;
	return *this;
}

//----------------------------------------------------------------

SSGFX::SRGBColor& SSGFX::SRGBColor::operator=(const FComposedColor& InRHS)
{
	ComposedColor = InRHS << 8;
	return *this;
}

//----------------------------------------------------------------

bool SSGFX::SRGBColor::operator==(const SRGBColor& InRHS) const
{
	return ComposedColor == InRHS.ComposedColor;
}

//----------------------------------------------------------------

bool SSGFX::SRGBColor::operator==(const FComposedColor& InRHS) const
{
	return ComposedColor == (InRHS << 8);
}

//----------------------------------------------------------------

//----------------------------------------------------------------
// End RGB Color
//----------------------------------------------------------------