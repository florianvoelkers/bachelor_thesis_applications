#pragma once

// internal code
#include "Component.hpp"

// external libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/component_wise.hpp>

class Transform : public Component
{
	CLASS_DECLARATION(Transform)

public:
	Transform(Entity* entity, const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale, bool enabled = true)
		: m_Position(position), m_Rotation(rotation), m_Scale(scale), Component(entity, enabled) {}

	void Translate(const glm::vec3& translation)
	{
		m_Position += translation;
	}

	void Rotate(const glm::vec3& axis, float angle)
	{
		glm::quat rotation = glm::angleAxis(glm::radians(angle), axis);
		Rotate(rotation);
	}

	void Rotate(const glm::quat& rotation)
	{
		m_Rotation = glm::normalize(glm::quat(rotation * m_Rotation));
		UpdateVectors();
	}

	inline void SetPosition(const glm::vec3& position) { m_Position = position; }
	inline void SetRotation(const glm::quat& rotation) { m_Rotation = rotation; UpdateVectors(); }
	inline void SetScale(const glm::vec3& scale) { m_Scale = scale; }
	inline void SetForwardVector(const glm::vec3& forward) { m_Forward = forward; }
	inline void SetRightVector(const glm::vec3& right) { m_Right = right; }
	inline void SetUpVector(const glm::vec3& up) { m_Up = up; }

	glm::mat4 GetTransformationMatrix()
	{
		glm::mat4 translationMatrix = glm::mat4();
		translationMatrix = glm::translate(translationMatrix, m_Position);

		glm::mat4 rotationMatrix = glm::mat4();
		rotationMatrix = glm::toMat4(m_Rotation);

		glm::mat4 scaleMatrix = glm::mat4();
		scaleMatrix = glm::scale(scaleMatrix, m_Scale);

		glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
		return transformationMatrix;
	}

	inline glm::vec3 GetPosition() { return m_Position; }
	inline glm::quat GetRotation() { return m_Rotation; }
	inline glm::vec3 GetScale() { return m_Scale; }
	inline glm::vec3 GetForwardVector() { return m_Forward; }
	inline glm::vec3 GetRightVector() { return m_Right; }
	inline glm::vec3 GetUpVector() { return m_Up; }

	const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

private:
	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::vec3 m_Scale;

	glm::vec3 m_Forward;
	glm::vec3 m_Up;
	glm::vec3 m_Right;

	void UpdateVectors()
	{
		m_Forward.x = 2 * (m_Rotation.x * m_Rotation.z + m_Rotation.w * m_Rotation.y);
		m_Forward.y = 2 * (m_Rotation.y * m_Rotation.z - m_Rotation.w * m_Rotation.x);
		m_Forward.z = 1 - 2 * (m_Rotation.x * m_Rotation.x + m_Rotation.y * m_Rotation.y);

		m_Right = glm::normalize(glm::cross(m_Forward, WORLD_UP));
		m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
	}
};
