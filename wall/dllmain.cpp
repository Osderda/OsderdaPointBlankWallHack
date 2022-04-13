#include "stdafx.h"
#include <fstream>
#include "Hook.h"
#include "Menu.h"
#include "detours.h"
#include "X0r.h"
#include <process.h>
#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <iostream>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "D3DX9.LIB")





#include <thread>

LRESULT CALLBACK MsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }
DWORD* TESTE()
{
	WNDCLASSEX QQQQ = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassEx(&QQQQ);
	HWND hWnd = CreateWindow("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, GetDesktopWindow(), NULL, QQQQ.hInstance, NULL);
	LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	LPDIRECT3DDEVICE9 pd3dDevice;
	pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice);
	DWORD* pVTable = (DWORD*)pd3dDevice;
	pVTable = (DWORD*)pVTable[0];
	DestroyWindow(hWnd);
	return pVTable;
}


typedef HRESULT(WINAPI* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene = NULL;

HRESULT WINAPI hkEndScene(LPDIRECT3DDEVICE9 pDevice) 
{
	

	return oEndScene(pDevice);
}

#define TESTETHREAD(tttt) _beginthreadex(0, 0, tttt, 0, 0, 0);

unsigned __stdcall THREAAAAA(LPVOID Param) // d3dx9
{
	DWORD* zTESTE = TESTE();
	DWORD hTESTE = 0;
	while (!hTESTE) hTESTE = (DWORD)GetModuleHandle(/*d3d9.dll*/XorStr<0x5f, 9, 0x268c5c5e>("\x3b\x53\x5\x5b\x4d\x0\x9\xa" + 0x268c5c5e).s);
	if (zTESTE)
	{
		ODrawIndexedPrimitive = (TDrawIndexedPrimitive)DetourFunction((PBYTE)zTESTE[82], (PBYTE)DrawIndexedPrimitive); // wallhack
	}
	return false;
	//return true;
}

void allocate_console() // console
{
	AllocConsole();
	FILE* file_stream;
	freopen_s(&file_stream, "CONIN$", "r", stdin);
	freopen_s(&file_stream, "CONOUT$", "w", stdout);
	freopen_s(&file_stream, "CONOUT$", "w", stderr);

	SetConsoleTitleA("[ + Game ( LunaUI ) Hacking + ]");
}

void ConsoleMain() // print
{
	allocate_console();
	std::printf("< Luna Valerie > | Hack Load | <");
	
}

BOOL APIENTRY DllMain(HMODULE hModule, // attack dll
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		std::thread(ConsoleMain).detach();
		TESTETHREAD(THREAAAAA);
	}
	return true;
}
