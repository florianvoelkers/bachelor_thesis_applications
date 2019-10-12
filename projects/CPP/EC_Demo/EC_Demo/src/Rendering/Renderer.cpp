// internal code
#include "Renderer.hpp"

// temporary
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer(const Window& window) : m_Window(window)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float fov = 45.0f;
	// calculate projection matrix
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)m_Window.GetWidth() / (float)m_Window.GetHeight(), 0.1f, 100.0f);

	// camera
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 100.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Renderer::Draw(Entity& root)
{
	glClearColor(0.275f, 0.275f, 0.275f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	root.Draw(viewMatrix, projectionMatrix);
}
