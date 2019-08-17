#pragma once

#ifdef _WIN32

#include <windows.h>

#define GLFW_INCLUDE_NONE
#include <glfw3.h>
#include <glad.h>
#include <gl/GLU.h>

#ifdef _X86_
#pragma comment(lib, "glfw3_32.lib")
#else
#pragma comment(lib, "glfw3_64.lib")
#endif
#pragma comment(lib, "Opengl32.lib")
#endif