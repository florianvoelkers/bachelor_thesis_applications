#pragma once

#include "BaseComponent.hpp"

template<typename T>
struct Component : public BaseComponent
{
	static const ComponentCreateFunction CREATE_FUNCTION;
	static const ComponentFreeFunction FREE_FUNCTION;	
	static const size_t SIZE;
	static const __int32 ID;
};

template<typename Comp>
__int32 ComponentCreate(std::vector<__int8>& memory, EntityHandle entity, BaseComponent* baseComponent)
{
	__int32 index = memory.size();
	memory.resize(index + Comp::SIZE);
	Comp* component = new(&memory[index])Comp(*(Comp*)baseComponent);
	component->entity = entity;
	return index;
}

template<typename Comp>
void ComponentFree(BaseComponent* baseComponent)
{
	Comp* component = (Comp*)baseComponent;
	component->~Comp();
}

template<typename T>
const __int32 Component<T>::ID(BaseComponent::RegisterComponentType(ComponentCreate<T>, ComponentFree<T>, sizeof(T)));

template<typename T>
const size_t Component<T>::SIZE(sizeof(T));

template<typename T>
const ComponentCreateFunction Component<T>::CREATE_FUNCTION(ComponentCreate<T>);

template<typename T>
const ComponentFreeFunction Component<T>::FREE_FUNCTION(ComponentFree<T>);

