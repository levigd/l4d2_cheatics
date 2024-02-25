#pragma once

#include <Windows.h>

typedef void* (__cdecl* CreateInterfaceFn)(const char* pName, int* pReturnCode);

void* GetInterface(const char* interfaceName, const char* moduleName);

class CMemory
{
public:
	void Hook(void* address, void* hook);
	DWORD TramplineHook(void* address, void* hook, int size = 5);
	void TramplineUnHook(void* address, void* gateway, int size = 5);
};

template <int index, typename Type, typename... Arguments>
Type callVirtual(void* instance, Arguments... arguments)
{
	typedef Type(__thiscall* tFunction)(void* instance, Arguments... arguments);
	tFunction func = (*(tFunction**)instance)[index];
	return func(instance, arguments...);
}