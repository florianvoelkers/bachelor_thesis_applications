#pragma once

// standard library
#include <iostream>
#include <functional>

// external libraries
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// internal code
#include "Events/Event.hpp"

struct WindowProperties
{
	std::string m_Title;
	unsigned int m_Width;
	unsigned int m_Height;

	WindowProperties(const std::string& title = "Demo EC", unsigned int width = 1840, unsigned int height = 1035)
		: m_Title(title), m_Width(width), m_Height(height) {}
};

// Creates and sets up an OpenGl window using the GLFW library.
// It also handles forwarding window, key and mouse events by setting callbacks to GLFW event functions.
// The callback method for those events is set in Application.cpp.
class Window
{
public:
	using EventCallbackFunction = std::function<void(Event&)>;

	Window(const WindowProperties& properties);
	~Window();

	void OnUpdate();

	inline void SetEventCallback(const EventCallbackFunction& callback) { m_WindowData.m_EventCallback = callback; }
	inline unsigned int GetWidth() const { return m_WindowData.m_Width; }
	inline unsigned int GetHeight() const { return m_WindowData.m_Height; }

private:
	GLFWwindow* m_Window;

	struct WindowData
	{
		std::string m_Title;
		unsigned int m_Width;
		unsigned int m_Height;

		EventCallbackFunction m_EventCallback;
	};

	WindowData m_WindowData;

	void Init(const WindowProperties& properties);
};
