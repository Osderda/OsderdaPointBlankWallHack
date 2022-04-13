#include "stdafx.h"
#include "Hook.h"
#include "Draw.h"
#include "Menu.h"
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <random>
#include "windows.h"

/////
using namespace std;


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int BLACK = 0;
int BLUE = 1;
int GREEN = 2;
int CYAN = 3;
int RED = 4;
int MAGENTA = 5;
int BROWN = 6;
int LIGHTGRAY = 7;
int DARKGRAY = 8;
int LIGHTBLUE = 9;
int LIGHTGREEN = 10;
int LIGHTCYAN = 11;
int LIGHTRED = 12;
int LIGHTMAGENTA = 13;
int YELLOW = 14;
int WHITE = 15;

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif


void CreatDevice(DWORD* dVTable) {
	LPDIRECT3D9 mD3D = NULL;
	mD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (mD3D == NULL)
		return;

	D3DPRESENT_PARAMETERS pPresentParams;
	ZeroMemory(&pPresentParams, sizeof(pPresentParams));
	pPresentParams.Windowed = true;
	pPresentParams.BackBufferFormat = D3DFMT_UNKNOWN;
	pPresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;

	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (FAILED(mD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDesktopWindow(), D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&pPresentParams, &pDevice)))
		return;
	DWORD* vTable = (DWORD*)pDevice;
	vTable = (DWORD*)vTable[0];

	dVTable[0] = vTable[16]; // reset 
	dVTable[1] = vTable[17]; // present
	dVTable[2] = vTable[42]; // endscence
	dVTable[3] = vTable[82]; // DrawIndex
	

}
void creatmenu() {
	SetConsoleTextAttribute(hConsole, CYAN);
	Sleep(1000);
	cout << "[!] Osderda - realitycheats.com" << endl;
	Sleep(1000);
	cout << "[!] Point Blank Osderda WallHack" << endl;
	Sleep(2000);
	DWORD vTable[4] = { 0 };
	CreatDevice(vTable);
	Original_EndScene = (_EndScene)vTable[2];
	Original_DrawIndexePrimitive = (_DrawIndexedPrimitive)vTable[3];

	HookFunction((void*)Original_EndScene, (void*)My_EndScene, 5, EndScene_byte);

	HookFunction((void*)Original_DrawIndexePrimitive, (void*)My_DrawIndexedPrimitive, 5, DrawIndexePrimitive_bytes);

	SetConsoleTextAttribute(hConsole, GREEN);
	cout << ">Inject Successful!" << endl;
}

DWORD WINAPI mThread(PVOID tantodaz) {
	while (!GetModuleHandle("d3d9.dll")) {
		Sleep(100);
	}
	creatmenu();
	/*while (500) {
	}*/

	return 0;
}

void OpenConsole(std::string Title)
{
	AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
	//freopen("CONIN$", "r", stdin);
	//freopen("CONOUT$", "w", stdout);
	//freopen("CONOUT$", "w", stderr);
	string str = "0123456789ABCD-EFG+HIJKLMNO-PQR+STUVWXY-Zab+cdefghijklmnop-qrstuvwxyz";
	string newstr;
	int pos;
	while (newstr.size() != 25) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	std::string stemp = std::string(newstr.begin(), newstr.end());
	LPCTSTR sww = const_cast<char*>(stemp.c_str());
	//LPCWSTR sw = stemp.c_str();
	SetConsoleTitle(sww);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		OpenConsole("Osderda");
		Sleep(1000);
		CreateThread(0, 0, &mThread, 0, 0, 0);
	}
	return TRUE;
}

