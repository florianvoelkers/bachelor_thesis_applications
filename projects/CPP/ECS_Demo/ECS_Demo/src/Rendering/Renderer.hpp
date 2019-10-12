#pragma once

// internal code
#include "Window.hpp"
#include "Shader.hpp"
#include "Model.hpp"

#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer(const Window& window);
	
	void Clear();

	inline glm::mat4 GetViewMatrix() { return viewMatrix; }
	inline glm::mat4 GetProjectionMatrix() { return projectionMatrix; }
private:
	const Window& m_Window;
	
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};
