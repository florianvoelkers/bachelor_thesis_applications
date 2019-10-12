#pragma once

#include "Component.hpp"

#include <vector>

class System
{
public:
	System() {}

	virtual void Update(float deltaTime, BaseComponent** components) {}

	const std::vector<__int32>& GetComponentTypes() { return componentTypes; }

protected:
	void AddComponentType(__int32 componentType)
	{
		componentTypes.push_back(componentType);
	}

private:
	std::vector<__int32> componentTypes;
};