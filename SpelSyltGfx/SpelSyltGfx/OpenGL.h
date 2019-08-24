#pragma once

#ifdef _WIN32

#include <windows.h>

#define GLFW_INCLUDE_NONE
#include <SpelSyltGfx/glfw3.h>
#include <SpelSyltGfx/glad.h>
#include <gl/GLU.h>

#ifdef _X86_
#pragma comment(lib, "glfw3_32.lib")
#else
#pragma comment(lib, "glfw3_64.lib")
#endif //_X86_
#pragma comment(lib, "Opengl32.lib")
#endif //_WIN32