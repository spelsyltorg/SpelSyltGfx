#pragma once

//Base colors
#define COLOR_RED					0xFF0000FF
#define COLOR_GREEN					0x00FF00FF
#define COLOR_BLUE					0x0000FFFF

//Combination colors
#define COLOR_YELLOW				0xFFFF00FF
#define COLOR_MAGENTA				0xFF00FFFF
#define COLOR_CYAN					0x00FFFFFF

//Grayscale colors
#define COLOR_BLACK					0x000000FF
#define COLOR_WHITE					0xFFFFFFFF

//Special colors
#define COLOR_TRANSPARENT			0x00000000
#define COLOR_UGLY_GREEN_YELLOW		0x7A9703FF

//Offsets used for masking the bits of the composed color
#define R_OFFSET 24
#define G_OFFSET 16
#define B_OFFSET 8
#define A_OFFSET 0

//Helper defines to get channel values
#define CHANNEL_VALUE(ComposedColor, ChannelBitOffset) static_cast<SSGFX::FChannel>(ComposedColor >> ChannelBitOffset)
#define R_CHANNEL(ComposedColor) CHANNEL_VALUE(ComposedColor, R_OFFSET)
#define G_CHANNEL(ComposedColor) CHANNEL_VALUE(ComposedColor, G_OFFSET)
#define B_CHANNEL(ComposedColor) CHANNEL_VALUE(ComposedColor, B_OFFSET)
#define A_CHANNEL(ComposedColor) CHANNEL_VALUE(ComposedColor, A_OFFSET)

namespace SSGFX
{
	using FChannel = unsigned char;
	using FComposedColor = unsigned int;

	//----------------------------------------------------------------
	// Render Colors
	//----------------------------------------------------------------

	struct SRGBARenderColor
	{
		float Red;
		float Green;
		float Blue;
		float Alpha;
	};

	struct SRGBRenderColor
	{
		float Red;
		float Green;
		float Blue;
	};

	//----------------------------------------------------------------
	// Compose helpers
	//----------------------------------------------------------------

	FComposedColor ComposeColor(FChannel InR, FChannel InG, FChannel InB, FChannel InA);
	FComposedColor ComposeColor(FChannel InR, FChannel InG, FChannel InB);

	//----------------------------------------------------------------
	// RGBA Color
	//----------------------------------------------------------------

	struct SRGBAColor
	{
	public:
		SRGBAColor();
		explicit SRGBAColor(const SRGBAColor& InOther);
		SRGBAColor(const FComposedColor InComposedColor);
		SRGBAColor(const FChannel InRed, const FChannel InGreen, const FChannel InBlue, const FChannel InAlpha);

		SRGBARenderColor DecomposeToRenderColor() const;

		SRGBAColor& operator=(const SRGBAColor& InRHS);
		SRGBAColor& operator=(const FComposedColor InRHS);

		bool operator==(const SRGBAColor& InRHS) const;
		bool operator==(const FComposedColor InRHS) const;

		FChannel R() const	{ return R_CHANNEL(ComposedColor); };
		FChannel G() const	{ return G_CHANNEL(ComposedColor); };
		FChannel B() const	{ return B_CHANNEL(ComposedColor); };
		FChannel A() const	{ return A_CHANNEL(ComposedColor); };
	private:
		FComposedColor ComposedColor;
	};

	//----------------------------------------------------------------
	// RGB Color
	//----------------------------------------------------------------

	struct SRGBColor
	{
	public:
		SRGBColor();
		explicit SRGBColor(const SRGBColor& InOther);
		SRGBColor(FComposedColor InComposedColor);
		SRGBColor(FChannel InRed, FChannel InGreen, FChannel InBlue);

		SRGBRenderColor DecomposeToRenderColor() const;

		SRGBColor& operator=(const SRGBColor& InRHS);
		SRGBColor& operator=(const FComposedColor& InRHS);

		bool operator==(const SRGBColor& InRHS) const;
		bool operator==(const FComposedColor& InRHS) const;

		FChannel R() const { return R_CHANNEL(ComposedColor); };
		FChannel G() const { return G_CHANNEL(ComposedColor); };
		FChannel B() const { return B_CHANNEL(ComposedColor); };
	private:
		FComposedColor ComposedColor;
	};
}