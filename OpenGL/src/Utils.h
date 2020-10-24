#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <iostream>

extern unsigned int width;
extern unsigned int height;

inline void init()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize glfw." << std::endl;
	}
}

inline GLFWwindow* createWindow(unsigned int width, unsigned int height, const char* title, bool fullscreen = false)
{
	::width = width;
	::height = height;
	GLFWwindow* window;
	if (!fullscreen)
		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	else
		window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), nullptr);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	

	if (window == nullptr)
	{
		std::cerr << "Failed to create glfw window." << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cerr << "Failed to initialize glad." << std::endl;
	}

	return window;
}

inline std::vector<std::string> split(std::string str, std::string sep)
{
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	char* context = NULL;
	std::vector<std::string> arr;
	current = strtok_s(cstr, sep.c_str(), &context);
	while (current != NULL)
	{
		arr.push_back(current);
		current = strtok_s(NULL, sep.c_str(), &context);
	}
	return arr;
}

template <typename T>
T clamp(T val, T min, T max)
{
    if (val < min)
        return min;
    if (val > max)
        return max;
    return val;
}

template <typename T>
int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

template <typename T>
T map(T value, T inA, T inB, T outA, T outB)
{
	return outA + ((outB - outA) / (inB - inA)) * (value - inA);
}

template <typename T> T dist(T x1, T y1, T x2, T y2)
{
    T dx = x2 - x1;
    T dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}



