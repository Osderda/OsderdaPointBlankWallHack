#include "stdafx.h"
#include "Hook.h"
#include "Draw.h"
#include "Menu.h"
#include <fstream>


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
	DWORD vTable[4] = { 0 };
	CreatDevice(vTable);
	Original_EndScene = (_EndScene)vTable[2];
	Original_DrawIndexePrimitive = (_DrawIndexedPrimitive)vTable[3];

	HookFunction((void*)Original_EndScene, (void*)My_EndScene, 5, EndScene_byte);

	HookFunction((void*)Original_DrawIndexePrimitive, (void*)My_DrawIndexedPrimitive, 5, DrawIndexePrimitive_bytes);
}

DWORD WINAPI mThread(PVOID tantodaz) {
	while (!GetModuleHandle("d3d9.dll")) {
		Sleep(100);
	}
	creatmenu();
	while (500) {
	}
	return 0;
}


void OpenConsole(std::string Title)
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	SetConsoleTitle(Title.c_str());
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		OpenConsole("Luna Valerie @ YouTube / d3dx9");
		CreateThread(0, 0, &mThread, nullptr, 0, 0);
	}
	return TRUE;
}

