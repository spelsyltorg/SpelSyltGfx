#include "Window.h"

#include <assert.h>
#include "SpelSyltGfx/OpenGL.h"

#include <functional>

#include <iostream>
#define LOG(a) std::cout << (a) << std::endl



SSGFX::CWindow::CWindow(unsigned Width, unsigned Height, const std::string & Name)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	WindowHandle = glfwCreateWindow(Width, Height, Name.c_str(), NULL, NULL);
	if (!WindowHandle)
	{
		glfwTerminate();
		LOG("Failed to create window.");
	}
	glfwMakeContextCurrent(WindowHandle);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG("Failed to load GLAD.");
	}

	glfwSetWindowUserPointer(WindowHandle, this);

	SetEventCallbacks();

	glViewport(0, 0, Width, Height);

	ActiveEvents = &Events1;
	WaitingEvents = &Events2;
}

SSGFX::CWindow::~CWindow()
{
	glfwTerminate();
}

void SSGFX::CWindow::SetClearColor(const SRGBColor& Color)
{
	ClearColor = Color.DecomposeToRenderColor();
}

void SSGFX::CWindow::Clear()
{
	glClearColor(ClearColor.Red, ClearColor.Green, ClearColor.Blue, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SSGFX::CWindow::UpdateContent()
{
	glfwSwapBuffers(WindowHandle);
}

bool SSGFX::CWindow::IsOpen()
{
	if (glfwWindowShouldClose(WindowHandle)) {
		ActiveEvents->emplace_back(SWindowEvent{ EEventType::QUIT });
		return false;
	}
	glfwPollEvents();
	return true;
}

std::vector<SSGFX::SWindowEvent> SSGFX::CWindow::FlushEvents()
{
	auto events = *WaitingEvents;
	WaitingEvents->clear();

	std::swap(ActiveEvents, WaitingEvents);

	return std::move(events);
}

void SSGFX::CWindow::SetEventCallbacks()
{
	glfwSetFramebufferSizeCallback(WindowHandle, ResizeCallback);
	glfwSetKeyCallback(WindowHandle, InputKeyCallback);
	glfwSetCursorPosCallback(WindowHandle, MousePositionCallback);
	glfwSetMouseButtonCallback(WindowHandle, InputMouseCallback);
	glfwSetScrollCallback(WindowHandle, ScrollWheelCallback);
}

void SSGFX::CWindow::ResizeCallback(GLFWwindow * window, int width, int height)
{
	LOG("Resizing to " + std::to_string(width) + "x" + std::to_string(height));

	CWindow* w = static_cast<CWindow*>(glfwGetWindowUserPointer(window));

	SWindowEvent e;
	e.type = EEventType::RESIZE;
	e.x = width;
	e.y = height;
	w->ActiveEvents->emplace_back(e);
}

void SSGFX::CWindow::InputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	CWindow* w = static_cast<CWindow*>(glfwGetWindowUserPointer(window));

	bool releasedOrPressed = false;
	SWindowEvent e;
	if (action == GLFW_PRESS) {
		e.type = EEventType::KEY_DOWN;
		releasedOrPressed = true;
	}
	else if (action == GLFW_RELEASE) {
		e.type = EEventType::KEY_RELEASED;
		releasedOrPressed = true;
	}
	e.value = key;

	if (releasedOrPressed) {
		w->ActiveEvents->emplace_back(e);
	}
}

void SSGFX::CWindow::MousePositionCallback(GLFWwindow * window, double x, double y)
{
	CWindow* w = static_cast<CWindow*>(glfwGetWindowUserPointer(window));

	SWindowEvent e;

	e.type = EEventType::MOUSE_POS;
	e.x = x;
	e.y = y;

	w->ActiveEvents->emplace_back(e);

}

void SSGFX::CWindow::InputMouseCallback(GLFWwindow * window, int button, int action, int mods)
{
	InputKeyCallback(window, button, 0, action, mods);
}

void SSGFX::CWindow::ScrollWheelCallback(GLFWwindow * window, double x, double y)
{
	CWindow* w = static_cast<CWindow*>(glfwGetWindowUserPointer(window));

	SWindowEvent e;

	e.type = EEventType::MOUSE_SCROLL;
	e.x = x;
	e.y = y;

	w->ActiveEvents->emplace_back(e);
}
