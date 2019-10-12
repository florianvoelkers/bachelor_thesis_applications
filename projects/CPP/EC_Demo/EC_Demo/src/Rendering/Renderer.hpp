#pragma once

// internal code
#include "Window.hpp"
#include "Shader.hpp"
#include "Model.hpp"
#include "EC/Entity.hpp"

#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer(const Window& window);
	
	void Draw(Entity& root);
private:
	const Window& m_Window;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};
