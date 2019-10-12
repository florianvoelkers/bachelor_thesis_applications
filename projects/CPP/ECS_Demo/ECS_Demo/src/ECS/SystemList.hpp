#pragma once

#include "System.hpp"

class SystemList
{
public:
	inline void AddSystem(System& system) { systems.push_back(&system); }
	inline size_t Size() { return systems.size(); }
	inline System* operator[](__int32 index) { return systems[index]; }

	bool RemoveSystem(System& system);
private:
	std::vector<System*> systems;
};
