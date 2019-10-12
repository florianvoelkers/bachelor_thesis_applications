#pragma once

#include "ECS/ECS.hpp"
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

struct TransformComponent : public Component<TransformComponent>
{
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;
};
