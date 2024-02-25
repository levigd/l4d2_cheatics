#include "Utils.h"

void* GetInterface(const char* interfaceName, const char* moduleName)
{
	HMODULE hModule = GetModuleHandleA(moduleName);

	if (hModule)
	{
		CreateInterfaceFn createInterface = (CreateInterfaceFn)GetProcAddress(hModule, "CreateInterface");
		return createInterface(interfaceName, 0);
	}

	return 0;
}

void CMemory::Hook(void* address, void* hook)
{
	DWORD vprava;
	VirtualProtect(address, 5, PAGE_EXECUTE_READWRITE, &vprava);
	DWORD jmp = ((DWORD)hook - (DWORD)address) - 5;
	*(BYTE*)address = 0xE9;
	*(DWORD*)((DWORD)address + 0x1) = jmp;
	VirtualProtect(address, 5, vprava, &vprava);
}

DWORD CMemory::TramplineHook(void* address, void* hook, int size)
{
	DWORD gateway = (DWORD)VirtualAlloc(0, size + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (gateway)
	{
		memcpy((LPVOID)gateway, address, size + 5);
		DWORD jmp = (DWORD)address - gateway - 5;
		*(BYTE*)(gateway + size) = 0xE9;
		*(DWORD*)(gateway + size + 1) = jmp;
		Hook(address, hook);
		return gateway;
	}
	return 0;
}

void CMemory::TramplineUnHook(void* address, void* gateway, int size)
{
	DWORD prava;
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &prava);
	memcpy(address, gateway, size);
	VirtualProtect(address, size, prava, &prava);
}