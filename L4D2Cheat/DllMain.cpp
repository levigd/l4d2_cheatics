#include "DllMain.h"
/*
Переписать с ООП.
Раскидать все по файлам, чтобы тут почти ничего не было.
Сделать имгуи меню.
Сделать аим и мб бхоп, если он тут нужен вообще...
*/

int FrustumTransform(const VMatrix& worldToSurface, const СVector& point, СVector& screen)
{
	// UNDONE: Clean this up some, handle off-screen vertices
	float w;

	screen.x = worldToSurface[0][0] * point[0] + worldToSurface[0][1] * point[1] + worldToSurface[0][2] * point[2] + worldToSurface[0][3];
	screen.y = worldToSurface[1][0] * point[0] + worldToSurface[1][1] * point[1] + worldToSurface[1][2] * point[2] + worldToSurface[1][3];
	//	z		 = worldToSurface[2][0] * point[0] + worldToSurface[2][1] * point[1] + worldToSurface[2][2] * point[2] + worldToSurface[2][3];
	w = worldToSurface[3][0] * point[0] + worldToSurface[3][1] * point[1] + worldToSurface[3][2] * point[2] + worldToSurface[3][3];

	// Just so we have something valid here
	screen.z = 0.0f;

	bool behind;
	if (w < 0.001f)
	{
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;

		int x;
		int y;
		engineclient->GetScreenSize(x, y);
		screen.x = (x / static_cast<float>((2))) + (0.5f * screen.x * x + 0.5f);
		screen.y = (y / static_cast<float>((2))) - (0.5f * screen.y * y + 0.5f);
	}

	return behind;
}

bool isinitialized = false;

typedef HRESULT(__stdcall* t_EndScene)(IDirect3DDevice9* this_);
t_EndScene o_EndScene;

typedef ClientClass* (__thiscall* t_GetClientClass)(CEntity* this_);

HRESULT __stdcall HookEndScene(IDirect3DDevice9* this_)
{
	if (!isinitialized)
	{
		EnumWindows(EnumWindowsProc, 0);
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX9_Init(this_);

		isinitialized = true;
	}

	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX9_NewFrame();
	ImGui::NewFrame();

	ImGui::GetBackgroundDrawList()->AddText(ImVec2(500, 250), ImColor(255, 0, 0), "test");
	
	for (int i = 2; i < entityList->GetHighestEntityIndex(); ++i)
	{
		CEntity* entity = (CEntity*)entityList->GetClientEntity(i);
		if (entity)
		{
			DWORD* addr = (DWORD*)((char*)entity + 0x8);
			DWORD* vTable = *(DWORD**)(addr);
			DWORD* GetClientClassInTable = (DWORD*)((char*)vTable + 0x4);
			t_GetClientClass GetClientClass = (t_GetClientClass)(*(DWORD**)GetClientClassInTable);
			ClientClass* clientClass = GetClientClass(entity);
			//printf("%s\n", clientClass->m_pNetworkName);
			if (!strcmp(clientClass->m_pNetworkName, "Infected") || !strcmp(clientClass->m_pNetworkName, "Boomer") || !strcmp(clientClass->m_pNetworkName, "Hunter")) //Infected | Boomer | Hunter | SurvivorBot | CFirstAidKit | CWeaponSpawn | CBaseEntity | CPistol |
			{
				CInfected* zombie = (CInfected*)entity;
				СVector zombiePos = СVector(zombie->position.x, zombie->position.y, zombie->position.z);
				СVector zombieHeadPos = СVector(zombiePos.x, zombiePos.y, zombiePos.z + 65);
				СVector screenPos;//Ноги в 2д
				СVector screenPos2; //голова в 2д

				const VMatrix& matrix = engineclient->WorldToScreenMatrix();
				
				if (!FrustumTransform(matrix, zombiePos, screenPos))
				{
					FrustumTransform(matrix, zombieHeadPos, screenPos2);
					float height = screenPos2.y - screenPos.y;
					float width = height / 3;
					ImGui::GetBackgroundDrawList()->AddRect(ImVec2(screenPos.x - width, screenPos.y), ImVec2(screenPos.x + width, screenPos.y + height), ImColor(255, 0, 0));
				}
			}
		}
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return o_EndScene(this_);
}

DWORD WINAPI MyThread(HINSTANCE hInstDll)
{
	FILE* fConsole = nullptr;
	BOOL consoleAllocated = AllocConsole();

	if (consoleAllocated)
	{
		fConsole = freopen("CONOUT$", "w", stdout);
	}

	CMemory mem;

	EnumWindows(EnumWindowsProc, 0);

	int* vTable = GetDirectDeviceVTable();
	if (vTable)
	{
		o_EndScene = (t_EndScene)mem.TramplineHook((void*)vTable[42], HookEndScene, 7);
	}

	printf("LocalPlayerAddr -> %p <-\n", entityList->GetClientEntity(1));

	while (!GetAsyncKeyState(VK_DELETE))
	{


		Sleep(1);
	}

	if (vTable)
	{
		mem.TramplineUnHook((void*)vTable[42], o_EndScene, 7);
	}

	if (consoleAllocated)
	{
		if (fConsole)
		{
			fclose(fConsole);
		}
		FreeConsole();
	}

	FreeLibraryAndExitThread(hInstDll, 1);

	return 1;
}

DWORD WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		HANDLE handle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MyThread, hInstDll, 0, 0);

		if (handle)
		{
			CloseHandle(handle);
		}

		break;
	}

	return 1;
}