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

	glfwSetFramebufferSizeCallback(WindowHandle, ResizeCallback);

	glViewport(0, 0, Width, Height);

	ActiveEvents = &Events1;
	WaitingEvents = &Events2;
}

SSGFX::CWindow::~CWindow()
{
	glfwTerminate();
}

void SSGFX::CWindow::SetClearColor(const SColor& Color)
{
	ClearColor = Color;
}

void SSGFX::CWindow::Clear()
{
	glClearColor(ClearColor.r, ClearColor.g, ClearColor.b, ClearColor.a);
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
