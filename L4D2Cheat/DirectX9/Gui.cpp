#include "Gui.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

t_Wndproc o_Wndproc;

HWND window;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	DWORD procId;
	GetWindowThreadProcessId(hwnd, &procId);
	if (procId == GetCurrentProcessId() && hwnd != GetConsoleWindow())
	{
		window = hwnd;
		return false;
	}
	return true;
}

LRESULT WINAPI Wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	if (!ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		return true;
	}

	return CallWindowProc(o_Wndproc, hWnd, uMsg, wParam, lParam);
}