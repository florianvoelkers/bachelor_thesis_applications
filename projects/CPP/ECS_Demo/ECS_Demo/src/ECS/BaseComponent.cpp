#include "BaseComponent.hpp"

std::vector<std::tuple<ComponentCreateFunction, ComponentFreeFunction, size_t>>* BaseComponent::componentTypes;

__int32 BaseComponent::RegisterComponentType(ComponentCreateFunction createFunction, ComponentFreeFunction freeFunction, size_t size)
{
	if (componentTypes == nullptr)
		componentTypes = new std::vector<std::tuple<ComponentCreateFunction, ComponentFreeFunction, size_t>>();

	__int32 componentID = componentTypes->size();
	componentTypes->push_back(std::tuple<ComponentCreateFunction, ComponentFreeFunction, size_t>(createFunction, freeFunction, size));
	
	return componentID;
}