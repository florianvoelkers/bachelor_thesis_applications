#pragma once

// standard library
#include <memory>

// internal code
#include "Window.hpp"
#include "Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Rendering/Renderer.hpp"
#include "ImGuiLayer.hpp"

class Application
{
public:
	Application();

	void Run();
	void Quit();
	void OnEvent(Event& e);

	inline static Application& Get() { return *s_Instance; }

	inline void UpdatePredatorPosition(glm::vec3& position) { predatorPosition = position; }
	inline glm::vec3& GetPredatorPosition() { return predatorPosition; }

	float leftBound = -73.0f;
	float rightBound = 73.0f;

private:
	static Application* s_Instance;

	bool m_Running = true;
	unsigned int m_Objects = 0;
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<Model> m_Model;

	std::unique_ptr<Window> m_Window;
	std::unique_ptr<Renderer> m_Renderer;
	std::unique_ptr<ImGuiLayer> m_ImGui;
	std::unique_ptr<Entity> m_Root;

	glm::vec3 predatorPosition;

	bool OnWindowClose(WindowCloseEvent& e);
	bool OnKeyPressed(KeyPressedEvent& e);

	void AddEntities(unsigned int amount);
};
