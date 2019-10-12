#pragma once

#include "Component.hpp"
#include "System.hpp"
#include "SystemList.hpp"
#include "Util.hpp"

#include <map>
#include <vector>

class ECS
{
public:
	ECS() {}
	~ECS();

	EntityHandle MakeEntity(BaseComponent** components, const __int32* componentIDs, size_t numComponents);
	void RemoveEntity(EntityHandle handle);

	template<class A>
	EntityHandle MakeEntity(A& c1)
	{
		BaseComponent* components[] = { &c1 };
		__int32 componentIDs[] = { A::ID };
		return MakeEntity(components, componentIDs, 1);
	}
	
	template<class A, class B>
	EntityHandle MakeEntity(A& c1, B& c2)
	{
		BaseComponent* components[] = { &c1, &c2 };
		__int32 componentIDs[] = { A::ID, B::ID };
		return MakeEntity(components, componentIDs, 2);
	}

	template<class A, class B, class C>
	EntityHandle MakeEntity(A& c1, B& c2, C& c3)
	{
		BaseComponent* components[] = { &c1, &c2, &c3 };
		__int32 componentIDs[] = { A::ID, B::ID, C::ID };
		return MakeEntity(components, componentIDs, 3);
	}

	template<class A, class B, class C, class D>
	EntityHandle MakeEntity(A& c1, B& c2, C& c3, D& c4)
	{
		BaseComponent* components[] = { &c1, &c2, &c3, &c4 };
		__int32 componentIDs[] = { A::ID, B::ID, C::ID, D::ID };
		return MakeEntity(components, componentIDs, 4);
	}

	template<class A, class B, class C, class D, class E>
	EntityHandle MakeEntity(A& c1, B& c2, C& c3, D& c4, E& c5)
	{
		BaseComponent* components[] = { &c1, &c2, &c3, &c4, &c5 };
		__int32 componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID };
		return MakeEntity(components, componentIDs, 5);
	}

	template<class A, class B, class C, class D, class E, class F>
	EntityHandle MakeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6)
	{
		BaseComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6 };
		__int32 componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID };
		return MakeEntity(components, componentIDs, 6);
	}

	template<class A, class B, class C, class D, class E, class F, class G>
	EntityHandle MakeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7)
	{
		BaseComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7 };
		__int32 componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID };
		return MakeEntity(components, componentIDs, 7);
	}

	template<class Comp>
	inline void AddComponent(EntityHandle entity, Comp* component)
	{
		AddComponentInternal(entity, HandleToEntity(entity), Comp::ID, component);
	}

	template<class Comp>
	bool RemoveComponent(EntityHandle entity)
	{
		return RemoveComponentInternal(entity, Comp::ID);
	}

	template<class Comp>
	Comp* GetComponent(EntityHandle entity)
	{
		return (Comp*)GetComponentInternal(HandleToEntity(entity), components[Comp::ID], Comp::ID);
	}

	BaseComponent* GetComponentByType(EntityHandle entity, __int32 componentID)
	{
		return GetComponentInternal(HandleToEntity(entity), components[componentID], componentID);
	}

	void UpdateSystems(SystemList& systems, float deltaTime);

private:
	std::map<__int32, std::vector<__int8>> components;
	std::vector<std::pair<__int32, std::vector<std::pair<__int32, __int32>>>*> entities;
	
	inline std::pair<__int32, std::vector<std::pair<__int32, __int32>>>* HandleToRawType(EntityHandle handle)
	{
		return (std::pair<__int32, std::vector<std::pair<__int32, __int32>>>*)handle;
	}

	inline __int32 HandleToEntityIndex(EntityHandle handle)
	{
		return HandleToRawType(handle)->first;
	}

	inline std::vector<std::pair<__int32, __int32>>& HandleToEntity(EntityHandle handle)
	{
		return HandleToRawType(handle)->second;
	}

	void DeleteComponent(__int32 componentID, __int32 index);
	bool RemoveComponentInternal(EntityHandle handle, __int32 componentID);
	void AddComponentInternal(EntityHandle handle, std::vector<std::pair<__int32, __int32>>& entity, __int32 componentID, BaseComponent* component);
	BaseComponent* GetComponentInternal(std::vector<std::pair<__int32, __int32>>& entityComponents, std::vector<__int8>& array, __int32 componentID);

	void UpdateSystemWithMultipleComponents(__int32 index, SystemList& systems, float deltaTime,
		const std::vector<__int32>& componentTypes, std::vector<BaseComponent*>& componentParam, std::vector<std::vector<__int8>*>& componentArrays);
	__int32 FindLeastCommonComponent(const std::vector<__int32>& componentTypes);

	NULL_COPY_AND_ASSIGN(ECS);
};