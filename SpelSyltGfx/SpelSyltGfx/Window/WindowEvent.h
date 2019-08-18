#pragma once
namespace SSGFX
{
	enum class EEventType
	{
		QUIT,
		RESIZE
	};

	struct SWindowEvent
	{
		EEventType type;
		int x;
		int y;
	};
}