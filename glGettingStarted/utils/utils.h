#pragma once

#include "glad/glad.h" 
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak()

#define glCall(x) glClearError();\
	x;\
	ASSERT(glLogCall(#x, __FILE__, __LINE__))

static void glClearError() {
	while (glGetError());
}

static bool glLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[Opengl Error] (" << error << "):" << function << " " << file << ": " << line << std::endl;
		return false;
	}
	return true;
}

#define LOG std::cout
#define END std::endl