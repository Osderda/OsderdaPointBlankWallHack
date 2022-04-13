#pragma once

#include <fstream>


LPD3DXFONT pFont;


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
		printf("Systeam: %d \n", AtualValor);
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
		printf("Systeam: %d \n", AtualValor);
	}
}

UINT ItemsIndexados = 0;

int incme = 0;
void ItemsIncrement() {
	if (incme < Contador) {
		ItemsIndexados = Filtrados[incme];
		printf("========>ItemsIndexados: %d \n", ItemsIndexados);
		incme++;
	}
}


void ItemsDecrement() {
	if (incme > 0) {
		ItemsIndexados = Filtrados[incme];
		printf("========>ItemsIndexados: %d \n", ItemsIndexados);
		incme--;
	}
}

HRESULT GenerateTexture(IDirect3DDevice9* pD3Ddev, IDirect3DTexture9** ppD3Dtex, DWORD colour32) {
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