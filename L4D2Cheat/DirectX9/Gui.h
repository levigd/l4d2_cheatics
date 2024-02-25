#pragma once

#pragma comment(lib, "d3d9.lib")

#include <d3d9.h>
#include <cstdio>

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_dx9.h"

extern HWND window;

typedef LRESULT(WINAPI* t_Wndproc)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern t_Wndproc o_Wndproc;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

LRESULT WINAPI Wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);