#pragma once

#include "ECS/ECS.hpp"

struct MovementComponent : public Component<MovementComponent>
{
	float movementSpeed;
};
