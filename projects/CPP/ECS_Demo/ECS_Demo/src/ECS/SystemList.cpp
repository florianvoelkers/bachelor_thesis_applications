#include "SystemList.hpp"

bool SystemList::RemoveSystem(System& system)
{
	for (__int32 i = 0; i < systems.size(); i++)
	{
		if (&system == systems[i])
		{
			systems.erase(systems.begin() + i);
			return true;
		}
	}
	return false;
}
