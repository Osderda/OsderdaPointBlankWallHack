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

void UnHookFunction(void* original, BYTE* byte_original, int tamaño) {
	DWORD protect;
	VirtualProtect(original, tamaño, PAGE_EXECUTE_READWRITE, &protect);
	memcpy(original, byte_original, tamaño);
	VirtualProtect(original, tamaño, protect, &protect);
}

void HookFunction(void* original, void* nuevo, int tamaño, BYTE* byte_guardados) {
	DWORD protect;
	VirtualProtect(original, tamaño, PAGE_EXECUTE_READWRITE, &protect);
	memcpy(byte_guardados, original, tamaño);
	DWORD diferencia = ((DWORD)nuevo - (DWORD)original) - tamaño;
	memset(original, 0x90, tamaño);
	*(BYTE*)original = 0xE9;
	*(DWORD*)((DWORD)original + 1) = diferencia;
	VirtualProtect(original, tamaño, protect, &protect);

}