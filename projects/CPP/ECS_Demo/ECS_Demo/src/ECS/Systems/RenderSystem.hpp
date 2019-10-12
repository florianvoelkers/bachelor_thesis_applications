#pragma once

#include "ECS/ECS.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/ColorComponent.hpp"
#include "Rendering/Renderer.hpp"

// external libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/component_wise.hpp>

class RenderSystem : public System
{
public:
	RenderSystem(Renderer& renderer) : System(), m_Renderer(renderer)
	{
		AddComponentType(TransformComponent::ID);
		AddComponentType(RenderableComponent::ID);
		AddComponentType(ColorComponent::ID);
	}

	virtual void Update(float deltaTime, BaseComponent** components) override
	{
		TransformComponent* transform = (TransformComponent*)components[0];
		RenderableComponent* renderable = (RenderableComponent*)components[1];
		ColorComponent* color = (ColorComponent*)components[2];

		glm::mat4 translationMatrix = glm::mat4();
		translationMatrix = glm::translate(translationMatrix, transform->position);
		glm::mat4 rotationMatrix = glm::mat4();
		rotationMatrix = glm::toMat4(transform->rotation);
		glm::mat4 scaleMatrix = glm::mat4();
		scaleMatrix = glm::scale(scaleMatrix, transform->scale);
		glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;

		renderable->shader->Use();
		renderable->shader->SetMat4("model", transformationMatrix);
		renderable->shader->SetMat4("view", m_Renderer.GetViewMatrix());
		renderable->shader->SetMat4("projection", m_Renderer.GetProjectionMatrix());
		renderable->shader->SetVec4("color", color->color.ToVector4f());
		renderable->model->Draw(*renderable->shader);		
	}

private:
	Renderer& m_Renderer;
};
