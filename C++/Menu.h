#pragma once

#define TeamRed Stride == 44
#define TeamBlue NumVertices == 734 || NumVertices == 1273 || NumVertices == 212 || NumVertices == 309 || NumVertices == 446 || NumVertices == 6328 || NumVertices == 772

HRESULT WINAPI My_EndScene(LPDIRECT3DDEVICE9 pDevice) {

	HRESULT ret;

	UnHookFunction((void*)Original_EndScene, EndScene_byte, 5);
	ret = Original_EndScene(pDevice);
	HookFunction((void*)Original_EndScene, (void*)My_EndScene, 5, EndScene_byte);
	return ret;
}

LPDIRECT3DTEXTURE9 Vermelho;

LPDIRECT3DTEXTURE9 Azuro;

bool GerarTexture = true;

HRESULT WINAPI My_DrawIndexedPrimitive(
	LPDIRECT3DDEVICE9 pDevice,
	D3DPRIMITIVETYPE Type,
	INT BaseVertexIndex,
	UINT MinIndex,
	UINT NumVertices,
	UINT StartIndex,
	UINT PrimitiveCount
	){
	HRESULT ret;
	LPDIRECT3DVERTEXBUFFER9 steam_data;
	UINT Stride, offset;
	
	if (pDevice->GetStreamSource(0, &steam_data, &offset, &Stride) == D3D_OK)
		steam_data->Release();

	if (GerarTexture) {
		GenerateTexture(pDevice, &Vermelho, D3DCOLOR_ARGB(255, 255, 0, 0));
		GenerateTexture(pDevice, &Azuro, D3DCOLOR_ARGB(255, 255, 0, 0));
		GerarTexture = false;
	}

	if (TeamRed)
	{
		pDevice->SetRenderState(D3DRS_ZENABLE, false);
		pDevice->SetTexture(0, Vermelho);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		pDevice->SetRenderState(D3DRS_DITHERENABLE, false);
	}
	UnHookFunction((void*)Original_DrawIndexePrimitive, DrawIndexePrimitive_bytes, 5);
	ret = Original_DrawIndexePrimitive(pDevice, Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
	HookFunction((void*)Original_DrawIndexePrimitive, (void*)My_DrawIndexedPrimitive, 5, DrawIndexePrimitive_bytes);
	return ret;
}