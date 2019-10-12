#pragma once

#include <vector>
#include <tuple>

struct BaseComponent;
typedef void* EntityHandle;
typedef __int32 (*ComponentCreateFunction)(std::vector<__int8>& memory, EntityHandle entity, BaseComponent* baseComponent);
typedef void (*ComponentFreeFunction)(BaseComponent* baseComponent);
#define NULL_ENTITY_HANDLE nullptr

struct BaseComponent
{
public:
	static __int32 RegisterComponentType(ComponentCreateFunction createFunction, ComponentFreeFunction freeFunction, size_t size);
	EntityHandle entity = NULL_ENTITY_HANDLE;

	inline static ComponentCreateFunction GetTypeCreateFunction(__int32 id)
	{
		return std::get<0>((*componentTypes)[id]);
	}

	inline static ComponentFreeFunction GetTypeFreeFunction(__int32 id)
	{
		return std::get<1>((*componentTypes)[id]);
	}

	inline static size_t GetTypeSize(__int32 id)
	{
		return std::get<2>((*componentTypes)[id]);
	}

private:
	static std::vector<std::tuple<ComponentCreateFunction, ComponentFreeFunction, size_t>>* componentTypes;
};
