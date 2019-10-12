#include "ECS.hpp"

#include <algorithm>

ECS::~ECS()
{
	for (auto it = components.begin(); it != components.end(); ++it) 
	{
		size_t typeSize = BaseComponent::GetTypeSize(it->first);
		ComponentFreeFunction freeFunction = BaseComponent::GetTypeFreeFunction(it->first);
		for (__int32 i = 0; i < it->second.size(); i += typeSize)
			freeFunction((BaseComponent*)&it->second[i]);
	}

	for (__int32 i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}
}

EntityHandle ECS::MakeEntity(BaseComponent** entityComponents, const __int32* componentIDs, size_t numComponents)
{
	std::pair<__int32, std::vector<std::pair<__int32, __int32>>>* newEntity = new std::pair<__int32, std::vector<std::pair<__int32, __int32>>>();
	EntityHandle handle = (EntityHandle)newEntity;
	for (__int32 i = 0; i < numComponents; i++)
		AddComponentInternal(handle, newEntity->second, componentIDs[i], entityComponents[i]);

	newEntity->first = entities.size();
	entities.push_back(newEntity);

	return handle;
}

void ECS::RemoveEntity(EntityHandle handle)
{
	std::vector<std::pair<__int32, __int32>>& entity = HandleToEntity(handle);

	for (__int32 i = 0; i < entity.size(); i++)
		DeleteComponent(entity[i].first, entity[i].second);

	__int32 destinationIndex = HandleToEntityIndex(handle);
	__int32 sourceIndex = entities.size() - 1;
	delete entities[destinationIndex];
	entities[destinationIndex] = entities[sourceIndex];
	entities[destinationIndex]->first = destinationIndex;
	entities.pop_back();
}

void ECS::UpdateSystems(SystemList& systems, float deltaTime)
{
	std::vector<BaseComponent*> componentParam;
	std::vector<std::vector<__int8>*> componentArrays;
	for (__int32 i = 0; i < systems.Size(); i++)
	{
		const std::vector<__int32>& componentTypes = systems[i]->GetComponentTypes();
		if (componentTypes.size() == 1)
		{
			size_t typeSize = BaseComponent::GetTypeSize(componentTypes[0]);
			std::vector<__int8>& array = components[componentTypes[0]];
			for (__int32 j = 0; j < array.size(); j += typeSize)
			{
				BaseComponent* component = (BaseComponent*) & array[j];
				systems[i]->Update(deltaTime, &component);
			}
		}
		else
		{
			UpdateSystemWithMultipleComponents(i, systems, deltaTime, componentTypes, componentParam, componentArrays);
		}
	}
}

void ECS::DeleteComponent(__int32 componentID, __int32 index)
{
	std::vector<__int8>& array = components[componentID];
	ComponentFreeFunction freeFunction = BaseComponent::GetTypeFreeFunction(componentID);
	size_t typeSize = BaseComponent::GetTypeSize(componentID);
	__int32 sourceIndex = array.size() - typeSize;

	BaseComponent* destinationComponent = (BaseComponent*) & array[index];
	BaseComponent* sourceComponent = (BaseComponent*) & array[sourceIndex];
	freeFunction(destinationComponent);

	if (index == sourceIndex)
	{
		array.resize(sourceIndex);
		return;
	}

	std::memcpy(destinationComponent, sourceComponent, typeSize);

	std::vector<std::pair<__int32, __int32>>& sourceComponents = HandleToEntity(sourceComponent->entity);
	for (__int32 i = 0; i < sourceComponents.size(); i++)
	{
		if (componentID == sourceComponents[i].first && sourceIndex == sourceComponents[i].second)
		{
			sourceComponents[i].second = index;
			break;
		}
	}

	array.resize(sourceIndex);
}

bool ECS::RemoveComponentInternal(EntityHandle handle, __int32 componentID)
{
	std::vector<std::pair<__int32, __int32>>& entityComponents = HandleToEntity(handle);
	for (__int32 i = 0; i < entityComponents.size(); i++)
	{
		if (componentID == entityComponents[i].first)
		{
			DeleteComponent(entityComponents[i].first, entityComponents[i].second);
			__int32 sourceIndex = entityComponents.size() - 1;
			__int32 destinationIndex = i;
			entityComponents[destinationIndex] = entityComponents[sourceIndex];
			entityComponents.pop_back();
			return true;
		}
	}
	return false;
}

void ECS::AddComponentInternal(EntityHandle handle, std::vector<std::pair<__int32, __int32>>& entity, __int32 componentID, BaseComponent* component)
{
	ComponentCreateFunction createFunction = BaseComponent::GetTypeCreateFunction(componentID);
	std::pair<__int32, __int32> newPair;
	newPair.first = componentID;
	newPair.second = createFunction(components[componentID], handle, component);
	entity.push_back(newPair);
}

BaseComponent* ECS::GetComponentInternal(std::vector<std::pair<__int32, __int32>>& entityComponents, std::vector<__int8>& array, __int32 componentID)
{
	for (__int32 i = 0; i < entityComponents.size(); i++)
		if (componentID == entityComponents[i].first)
			return (BaseComponent*) & array[entityComponents[i].second];

	return nullptr;
}

void ECS::UpdateSystemWithMultipleComponents(__int32 index, SystemList& systems, float deltaTime, 
	const std::vector<__int32>& componentTypes, std::vector<BaseComponent*>& componentParam, std::vector<std::vector<__int8>*>& componentArrays)
{
	componentParam.resize(std::max(componentParam.size(), componentTypes.size()));
	componentArrays.resize(std::max(componentArrays.size(), componentTypes.size()));
	for (__int32 i = 0; i < componentTypes.size(); i++)
		componentArrays[i] = &components[componentTypes[i]];

	__int32 minSizeIndex = FindLeastCommonComponent(componentTypes);

	size_t typeSize = BaseComponent::GetTypeSize(componentTypes[minSizeIndex]);
	std::vector<__int8>& array = *componentArrays[minSizeIndex];
	for (__int32 i = 0; i < array.size(); i += typeSize)
	{
		componentParam[minSizeIndex] = (BaseComponent*) & array[i];
		std::vector<std::pair<__int32, __int32>>& entityComponents = HandleToEntity(componentParam[minSizeIndex]->entity);

		bool isValid = true;
		for (__int32 j = 0; j < componentTypes.size(); j++)
		{
			if (j == minSizeIndex)
				continue;

			componentParam[j] = GetComponentInternal(entityComponents, *componentArrays[j], componentTypes[j]);
			if (componentParam[j] == nullptr)
			{
				isValid = false;
				break;
			}
		}

		if (isValid)
			systems[index]->Update(deltaTime, &componentParam[0]);
	}
}

__int32 ECS::FindLeastCommonComponent(const std::vector<__int32>& componentTypes)
{
	__int32 minSize = components[componentTypes[0]].size()/BaseComponent::GetTypeSize(componentTypes[0]);
	__int32 minIndex = 0;
	for (__int32 i = 0; i < componentTypes.size(); i++)
	{
		size_t typeSize = BaseComponent::GetTypeSize(componentTypes[i]);
		__int32 size = components[componentTypes[i]].size() / typeSize;
		if (size < minSize)
		{
			minSize = size;
			minIndex = i;
		}
	}

	return minIndex;
}

