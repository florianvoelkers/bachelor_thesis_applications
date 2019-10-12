#pragma once

#include "ECS/ECS.hpp"
#include "Color.hpp"

struct ColorComponent : public Component<ColorComponent>
{
	Color color;
};

