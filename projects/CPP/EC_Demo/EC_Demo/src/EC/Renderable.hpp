#pragma once

// internal code
#include "Component.hpp"
#include "Rendering/Model.hpp"
#include "Rendering/Shader.hpp"
#include "Transform.hpp"
#include "EC/ColorComponent.hpp"

// external libraries
#include <glm/glm.hpp>

// Gives functionality and data for drawing any model with the given shader.
class Renderable : public Component
{
	CLASS_DECLARATION(Renderable)

public:
	Renderable(Entity* entity, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, bool enabled = true)
		: m_Model(model), m_Shader(shader), Component(entity, enabled) {}

	virtual void Draw(const glm::mat4& view, const glm::mat4& projection) override
	{
		glm::mat4 modelMatrix = GetEntity().GetComponent<Transform>().GetTransformationMatrix();

		m_Shader->Use();
		m_Shader->SetMat4("model", modelMatrix);
		m_Shader->SetMat4("view", view);
		m_Shader->SetMat4("projection", projection);
		m_Shader->SetVec4("color", GetEntity().GetComponent<ColorComponent>().GetColor().ToVector4f());
		m_Model->Draw(*m_Shader);
	}

	inline void SetModel(std::shared_ptr<Model> model) { m_Model = model; }
	inline void SetShader(std::shared_ptr<Shader> shader) { m_Shader = shader; }

	inline Model& GetModel() { return *m_Model; }
	inline Shader& GetShader() { return *m_Shader; }

private:
	std::shared_ptr<Model> m_Model;
	std::shared_ptr<Shader> m_Shader;
};
