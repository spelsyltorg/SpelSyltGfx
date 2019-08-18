#pragma once

#include "WindowEvent.h"
#include "Rendering/GfxInclude.h"

#include <string>
#include <vector>

struct GLFWwindow;

namespace SSGFX
{
	class CWindow
	{
	public:

		enum EWindowStyle : unsigned short
		{
			Windowed = 1,
			Fullscreen = 2,
		};

		CWindow(unsigned Width, unsigned Height, const std::string& Name);
		~CWindow();

		void SetClearColor(const SColor& Color);
		void Clear();
		void UpdateContent();

		bool IsOpen();

		GLFWwindow* GetHandle() const { return WindowHandle; }
		std::vector<SWindowEvent> FlushEvents();

	private:
		static void ResizeCallback(GLFWwindow* window, int width, int height);

		GLFWwindow* WindowHandle = nullptr;
		SColor ClearColor;

		std::vector<SWindowEvent> Events1;
		std::vector<SWindowEvent> Events2;

		std::vector<SWindowEvent>* ActiveEvents;
		std::vector<SWindowEvent>* WaitingEvents;
	};
}