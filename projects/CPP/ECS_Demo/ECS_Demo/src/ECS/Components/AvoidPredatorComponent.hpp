#pragma once

#include "ECS/ECS.hpp"

struct AvoidPredatorComponent : public Component<AvoidPredatorComponent>
{
	bool avoiding = false;
	bool avoidingUp = false;
};

