// internal code
#include "Application.hpp"
#include "Keycode.hpp"

// temporary includes
#include "Rendering/Shader.hpp"
#include "Rendering/Mesh.hpp"
#include "Color.hpp"

// ECS
#include "ECS/Components/MovementComponent.hpp"
#include "ECS/Components/ColorComponent.hpp"
#include "ECS/Components/ColorChangerComponent.hpp"
#include "ECS/Components/AvoidPredatorComponent.hpp"
#include "ECS/Components/PredatorComponent.hpp"
#include "ECS/Systems/MovementSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Systems/ColorChangeSystem.hpp"
#include "ECS/Systems/AvoidanceSystem.hpp"
#include "ECS/Systems/CopyPredatorTransformsSystem.hpp"

// external libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/component_wise.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/string_cast.hpp>

Application* Application::s_Instance = nullptr;

Application::Application()
{
	s_Instance = this;

	m_Window = std::make_unique<Window>(WindowProperties());
	m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));
	m_Renderer = std::make_unique<Renderer>(*m_Window);
	m_ImGui = std::make_unique<ImGuiLayer>();

	m_Shader = std::make_shared<Shader>("resources/shader/Standard.vert", "resources/shader/Standard.frag");
	//m_Model = std::make_shared<Model>(BasicMeshes::CUBE);
	m_Model = std::make_shared<Model>("resources/models/fish.obj");
}

void Application::Run()
{
	std::shared_ptr<Model> mirroredFish = std::make_shared<Model>("resources/models/mirroredFish.obj");

	float randomY = glm::linearRand(-40.0f, 40.0f);
	TransformComponent transformComponent;
	transformComponent.position = glm::vec3(rightBound, randomY, 0.0f);
	transformComponent.rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
	glm::quat rotateY = glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	transformComponent.rotation = glm::normalize(glm::quat(rotateY * transformComponent.rotation));
	glm::quat rotateX = glm::angleAxis(glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	transformComponent.rotation = glm::normalize(glm::quat(rotateX * transformComponent.rotation));
	transformComponent.scale = glm::vec3(1.0f);

	RenderableComponent renderableComponent;
	renderableComponent.model = mirroredFish;
	renderableComponent.shader = m_Shader;
	ColorComponent colorComponent;
	colorComponent.color = Color(0.972f, 0.0f, 0.0f, 1.0f);

	float randomMovementSpeed = glm::linearRand(-7.0f, -5.0f);
	MovementComponent movementComponent;
	movementComponent.movementSpeed = randomMovementSpeed;

	PredatorComponent predatorComponent;

	predatorPosition = transformComponent.position;

	ecs.MakeEntity(transformComponent, renderableComponent, colorComponent, movementComponent, predatorComponent);
	m_Objects++;

	RenderSystem renderSystem(*m_Renderer);
	m_RenderingPipeline.AddSystem(renderSystem);

	MovementSystem movementSystem;
	m_MainSystems.AddSystem(movementSystem);
	CopyPredatorTransformsSystem copyPredatorTransformsSystem;
	m_MainSystems.AddSystem(copyPredatorTransformsSystem);
	ColorChangeSystem colorChangeSystem;
	m_MainSystems.AddSystem(colorChangeSystem);
	AvoidanceSystem avoidanceSystem (4.0f, 2.5f);
	m_MainSystems.AddSystem(avoidanceSystem);

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

		ecs.UpdateSystems(m_MainSystems, (float)elapsed);

		m_Renderer->Clear();
		ecs.UpdateSystems(m_RenderingPipeline, (float)elapsed);

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
		TransformComponent transformComponent;
		transformComponent.position = glm::vec3(leftBound, randomY, 0.0f);
		transformComponent.rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
		glm::quat rotateY = glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		transformComponent.rotation = glm::normalize(glm::quat(rotateY * transformComponent.rotation));
		glm::quat rotateX = glm::angleAxis(glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		transformComponent.rotation = glm::normalize(glm::quat(rotateX * transformComponent.rotation));
		transformComponent.scale = glm::vec3(0.2f);

		RenderableComponent renderableComponent;
		renderableComponent.model = m_Model;
		renderableComponent.shader = m_Shader;
		Color randomStartColor = Color(glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f), 1.0f);
		ColorComponent colorComponent;
		//colorComponent.color = Color(0.048f, 0.659f, 0.482f);
		colorComponent.color = randomStartColor;
		ColorChangerComponent colorChangerComponent;

		float randomMovementSpeed = glm::linearRand(7.0f, 13.0f);
		MovementComponent movementComponent;
		movementComponent.movementSpeed = randomMovementSpeed;

		AvoidPredatorComponent avoidPredatorComponent;

		ecs.MakeEntity(movementComponent, transformComponent, renderableComponent, colorComponent, colorChangerComponent, avoidPredatorComponent);
		m_Objects++;
	}
}
