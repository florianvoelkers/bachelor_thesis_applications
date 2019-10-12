// internal code
#include "Application.hpp"
#include "Keycode.hpp"

// temporary includes
#include "EC/Component.hpp"
#include "EC/Entity.hpp"
#include "EC/Renderable.hpp"
#include "EC/Transform.hpp"
#include "EC/Movement.hpp"
#include "EC/ColorComponent.hpp"
#include "EC/Predator.hpp"
#include "EC/AvoidPredator.hpp"

// external libraries
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

Application* Application::s_Instance = nullptr;

Application::Application()
{
	s_Instance = this;

	m_Window = std::make_unique<Window>(WindowProperties());
	m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));
	m_Renderer = std::make_unique<Renderer>(*m_Window);
	m_ImGui = std::make_unique<ImGuiLayer>();

	m_Root = std::make_unique<Entity>("Root", 0);
	m_Shader = std::make_shared<Shader>("resources/shader/Standard.vert", "resources/shader/Standard.frag");
	m_Model = std::make_shared<Model>("resources/models/fish.obj");
	//m_Model = std::make_shared<Model>(BasicMeshes::CUBE);
}

void Application::Run()
{
	std::shared_ptr<Model> mirroredFish = std::make_shared<Model>("resources/models/mirroredFish.obj");

	std::shared_ptr<Entity> predator = std::make_shared<Entity>("Predator", 1);
	float randomY = glm::linearRand(-40.0f, 40.0f);
	predator->AddComponent<Transform>(predator.get(), glm::vec3(rightBound, randomY, 0.0f), glm::quat(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(1.0f));
	predator->GetComponent<Transform>().Rotate(glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
	predator->GetComponent<Transform>().Rotate(glm::vec3(1.0f, 0.0f, 0.0f), 180.0f);
	predator->AddComponent<Renderable>(predator.get(), mirroredFish, m_Shader);
	predator->AddComponent<Movement>(predator.get(), -7.0f, -5.0f);
	predator->AddComponent<ColorComponent>(predator.get(), Color(0.972f, 0.0f, 0.0f, 1.0f), false);
	predator->AddComponent<Predator>(predator.get());
	m_Root->AddChild(predator);

	m_Objects++;
	predatorPosition = predator->GetComponent<Transform>().GetPosition();

	double lastTime = glfwGetTime();

	// for counting frames, but GLFW limits the fps to 60 because of VSYNC to avoid screen tearing
	unsigned int numberOfFrames = 0;
	double lastSecond = lastTime;

	while (m_Running)
	{
		double current = glfwGetTime();
		double elapsed = current - lastTime;
		lastTime = current;
		numberOfFrames++;

		if (current - lastSecond >= 1.0)
		{
			m_ImGui->SetLogData(numberOfFrames, m_Objects);
			numberOfFrames = 0;
			lastSecond += 1.0f;
		}

		m_Root->OnUpdate((float)elapsed);
		m_Renderer->Draw(*m_Root);
		m_ImGui->OnUpdate((float)elapsed);
		m_Window->OnUpdate();
	}
}

void Application::Quit()
{
	m_Running = false;
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClose));
	dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNCTION(Application::OnKeyPressed));

	m_ImGui->OnEvent(e);
	m_Root->OnEvent(e);
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	Quit();
	return true; // no other events of this type should be handled
}

bool Application::OnKeyPressed(KeyPressedEvent& e)
{
	if (e.GetKeyCode() == (int)Keycode::Escape)
	{
		Quit();
	}

	if (e.GetKeyCode() == (int)Keycode::Space)
		AddEntities(500);

	return false; // other events of this type should be handled
}

void Application::AddEntities(unsigned int amount)
{
	float randomY;
	std::string entityName = "";

	for (unsigned int i = 0; i < amount; i++)
	{
		randomY = glm::linearRand(-41.0f, 41.0f);
		entityName = "Entity";
		entityName.append(std::to_string(i + 2));

		std::shared_ptr<Entity> child = std::make_shared<Entity>(entityName, i + 2);
		child->AddComponent<Transform>(child.get(), glm::vec3(leftBound, randomY, 0.0f), glm::quat(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(0.2f));
		child->GetComponent<Transform>().Rotate(glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
		child->GetComponent<Transform>().Rotate(glm::vec3(1.0f, 0.0f, 0.0f), 180.0f);
		child->AddComponent<Renderable>(child.get(), m_Model, m_Shader);
		child->AddComponent<Movement>(child.get(), 7.0f, 13.0f);
		//child->AddComponent<ColorComponent>(child.get(), Color(0.048f, 0.659f, 0.482f, 1.0f), false);
		child->AddComponent<ColorComponent>(child.get(), Color(glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f), 1.0f), true);
		child->AddComponent<AvoidPredator>(child.get(), 4.0f, 2.5f);
		m_Root->AddChild(child);
		m_Objects++;
	}
}
