#pragma once
#include <windows.h>
#include "X0r.h"
#include <memory>
#include <memory.h>
#include <memory>
#include <wingdi.h>
#include <vector>
#include "detours.h"


UINT Filtrados[800] = { 0 };
int Contador = 0;
UINT utltimoFiltrado;

void ItemsAdd(UINT AtualValor) {
	if (utltimoFiltrado == AtualValor)
		return;
	utltimoFiltrado = AtualValor;

	bool off_ = false;
	if (Contador == 0) {
		Filtrados[0] = AtualValor;
		Contador++;
		printf("LunaUI> + : %d \n", AtualValor);
	}
	if (Contador >= 200 || AtualValor == 0)
		return;
	for (int i = 0; i < (Contador - 1); i++)
	{
		if (Filtrados[i] == AtualValor) {
			off_ = true;
		}
	}
	if (!off_) {
		Filtrados[Contador] = AtualValor;
		Contador++;
		printf("LunaUI#8497 + : %d \n", AtualValor);
	}
}

UINT ItemsIndexados = 0;

int incme = 0;
void ItemsIncrement() {
	if (incme < Contador) {
		ItemsIndexados = Filtrados[incme];
		printf("LunaUI : %d \n", ItemsIndexados);
		incme++;
	}
}


void ItemsDecrement() {
	if (incme > 0) {
		ItemsIndexados = Filtrados[incme];
		printf("LunaUI> : %d \n", ItemsIndexados);
		incme--;
	}
}


IDirect3DVertexBuffer9* Stream_Data;
UINT OffsetInBytes;
UINT m_Stride;

LPDIRECT3DTEXTURE9    texYellow, texRed, texGreen, texBlue, texBlack, texWhite, texPink, texOrange, texLightBlue, texCyan, texPurple, texSteelBlue, texLightSteelBlue, texSalmon, texBrown, texTeal, texLime, texElectricLime, texGold, texOrangeRed, texGreenYellow, texAquaMarine, texSkyBlue, texSlateBlue, texCrimson, texDarkOliveGreen, texPaleGreen, texDarkGoldenRod, texFireBrick, texDarkBlue, texDarkerBlue, texDarkYellow, texLightYellow;


LPDIRECT3DTEXTURE9 TEXTURE;
HRESULT GenerateTexture(IDirect3DDevice9* pD3Ddev, IDirect3DTexture9** ppD3Dtex, DWORD colour32)
{
	if (FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
		return E_FAIL;

	WORD colour16 = ((WORD)((colour32 >> 28) & 0xF) << 12)
		| (WORD)(((colour32 >> 20) & 0xF) << 8)
		| (WORD)(((colour32 >> 12) & 0xF) << 4)
		| (WORD)(((colour32 >> 4) & 0xF) << 0);

	D3DLOCKED_RECT d3dlr;
	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
	WORD* pDst16 = (WORD*)d3dlr.pBits;

	for (int xy = 0; xy < 8 * 8; xy++)
		*pDst16++ = colour16;

	(*ppD3Dtex)->UnlockRect(0);

	return S_OK;
}

bool texGenerated = false;
typedef HRESULT(__stdcall* TDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE pType, UINT paramx, UINT nMinIndex, UINT nNumVertices, UINT nStartIndex, UINT nPrimitiveCount);
TDrawIndexedPrimitive ODrawIndexedPrimitive;

HRESULT __stdcall DrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE pType, UINT paramx, UINT nMinIndex, UINT nNumVertices, UINT nStartIndex, UINT nPrimitiveCount)
{

	if (pDevice->GetStreamSource(0, &Stream_Data, &OffsetInBytes, &m_Stride) == D3D_OK)
		Stream_Data->Release();
	DWORD dwOldZEnable = D3DZB_TRUE;

	DWORD newEnable = D3DFILL_SOLID;
	if (!texGenerated)
	{
		GenerateTexture(pDevice, &TEXTURE, D3DCOLOR_ARGB(255, 255, 0, 0));
		GenerateTexture(pDevice, &texGreen, D3DCOLOR_ARGB(255, 0, 255, 0));
		GenerateTexture(pDevice, &texRed, D3DCOLOR_ARGB(255, 255, 0, 0));
		GenerateTexture(pDevice, &texBlue, D3DCOLOR_ARGB(255, 0, 0, 255));
		GenerateTexture(pDevice, &texOrange, D3DCOLOR_ARGB(255, 255, 165, 0));
		GenerateTexture(pDevice, &texYellow, D3DCOLOR_ARGB(255, 255, 255, 0));
		GenerateTexture(pDevice, &texBlack, D3DCOLOR_ARGB(255, 0, 0, 0));
		GenerateTexture(pDevice, &texWhite, D3DCOLOR_ARGB(255, 255, 255, 255));
		GenerateTexture(pDevice, &texCyan, D3DCOLOR_ARGB(255, 0, 255, 255));
		texGenerated = true;
	}

	if (nNumVertices)
		ItemsAdd(nNumVertices);

	if (nNumVertices == ItemsIndexados) {
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	}

	if (GetAsyncKeyState(VK_NUMPAD1) & 1)
	{
		ItemsDecrement();
	}
	if (GetAsyncKeyState(VK_NUMPAD2) & 1)
	{
		ItemsIncrement();
	}

	return ODrawIndexedPrimitive(pDevice, pType, paramx, nMinIndex, nNumVertices, nStartIndex, nPrimitiveCount);
}
