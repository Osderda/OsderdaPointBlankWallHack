#pragma once


typedef HRESULT(WINAPI* _EndScene)(LPDIRECT3DDEVICE9 pDevice);

_EndScene Original_EndScene;

BYTE EndScene_byte[5];

void UnHookFunction(void* original, BYTE* byte_original, int tama�o) {
	DWORD protect;
	VirtualProtect(original, tama�o, PAGE_EXECUTE_READWRITE, &protect);
	memcpy(original, byte_original, tama�o);
	VirtualProtect(original, tama�o, protect, &protect);
}

void HookFunction(void* original, void* nuevo, int tama�o, BYTE* byte_guardados) {
	DWORD protect;
	VirtualProtect(original, tama�o, PAGE_EXECUTE_READWRITE, &protect);
	memcpy(byte_guardados, original, tama�o);
	DWORD diferencia = ((DWORD)nuevo - (DWORD)original) - tama�o;
	memset(original, 0x90, tama�o);
	*(BYTE*)original = 0xE9;
	*(DWORD*)((DWORD)original + 1) = diferencia;
	VirtualProtect(original, tama�o, protect, &protect);

}

VOID CreateDevice(DWORD* dwVTable)
{
	LPDIRECT3D9 D3D9;
	LPDIRECT3DDEVICE9 pD3DDevice;
	D3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (D3D9 == NULL)
		return;
	D3DPRESENT_PARAMETERS pPresentParms;
	ZeroMemory(&pPresentParms, sizeof(pPresentParms));
	pPresentParms.Windowed = TRUE;
	pPresentParms.BackBufferFormat = D3DFMT_UNKNOWN;
	pPresentParms.SwapEffect = D3DSWAPEFFECT_DISCARD;
	if (FAILED(D3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDesktopWindow(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pPresentParms, &pD3DDevice)))
		return;
	DWORD* dwTable = (DWORD*)pD3DDevice;
	dwTable = (DWORD*)dwTable[0];
	dwVTable[0] = dwTable[16];
	dwVTable[1] = dwTable[17];
}