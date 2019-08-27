#pragma once

#include "WindowEvent.h"
#include "SpelSyltGfx/Rendering/GfxInclude.h"
#include <SpelSyltGfx/Rendering/Color.h>

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

		void SetClearColor(const SRGBColor& Color);
		void Clear();
		void UpdateContent();

		bool IsOpen();

		GLFWwindow* GetHandle() const { return WindowHandle; }
		std::vector<SWindowEvent> FlushEvents();

	private:

		void SetEventCallbacks();

		static void ResizeCallback(GLFWwindow* window, int width, int height);
		static void InputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MousePositionCallback(GLFWwindow* window, double x, double y);
		static void InputMouseCallback(GLFWwindow* window, int button, int action, int mods);
		static void ScrollWheelCallback(GLFWwindow* window, double x, double y);

		GLFWwindow* WindowHandle = nullptr;
		SRGBRenderColor ClearColor;

		std::vector<SWindowEvent> Events1;
		std::vector<SWindowEvent> Events2;

		std::vector<SWindowEvent>* ActiveEvents;
		std::vector<SWindowEvent>* WaitingEvents;
	};
}