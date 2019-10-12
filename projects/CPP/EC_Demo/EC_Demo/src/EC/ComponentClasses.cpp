#include "Component.hpp"

// include all components here
#include "Renderable.hpp"
#include "Transform.hpp"
#include "Movement.hpp"
#include "ColorComponent.hpp"
#include "Predator.hpp"
#include "AvoidPredator.hpp"

const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));

// All class definitions for components
// CLASS_DEFINITION(parent class, sub class)
CLASS_DEFINITION(Component, Transform)
CLASS_DEFINITION(Component, Renderable)
CLASS_DEFINITION(Component, Movement)
CLASS_DEFINITION(Component, ColorComponent)
CLASS_DEFINITION(Component, Predator)
CLASS_DEFINITION(Component, AvoidPredator)