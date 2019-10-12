#pragma once

// internal code
#include "Events/Event.hpp"
#include "Events/MouseEvent.hpp"

#include <iostream>

// Creates an ImGui Overlay for the engine which can be customized
class ImGuiLayer
{
public:
	ImGuiLayer();
	void OnUpdate(float deltaTime);
	void OnEvent(Event& e);
	void SetLogData(unsigned int fps, unsigned int objects)
	{
		m_FPS = fps;
		m_Objects = objects;
	}
private:
	unsigned int m_FPS;
	unsigned int m_Objects;

	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
	bool OnMouseMovedEvent(MouseMovedEvent& event);

	void ShowFPSAndEntityCount(bool* p_open);
};
