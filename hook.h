#pragma once

typedef HRESULT(WINAPI* _EndScene)(LPDIRECT3DDEVICE9 pDevice);

_EndScene Original_EndScene;

BYTE EndScene_byte[5];


typedef HRESULT(WINAPI* _DrawIndexedPrimitive)(
	LPDIRECT3DDEVICE9 pDevice,
	D3DPRIMITIVETYPE Type,
	INT BaseVertexIndex,
	UINT MinIndex,
	UINT NumVertices,
	UINT StartIndex,
	UINT PrimitiveCount
	);

_DrawIndexedPrimitive Original_DrawIndexePrimitive;

BYTE DrawIndexePrimitive_bytes[5];

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