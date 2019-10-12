#pragma once

#include "ECS/ECS.hpp"
#include "Rendering/Model.hpp"
#include "Rendering/Shader.hpp"

#include <memory>

struct RenderableComponent : public Component<RenderableComponent>
{
	std::shared_ptr<Model> model;
	std::shared_ptr<Shader> shader;
};
