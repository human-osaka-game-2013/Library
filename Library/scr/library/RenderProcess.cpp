#include "graphic.h"

// 3D描画前処理
void BeginRender ( HRESULT* hr )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	if ( !pD3Device )
	{

	}

	pD3Device->LightEnable(0, TRUE);

	// 画面の消去
	pD3Device -> Clear (0, NULL,
						D3DCLEAR_TARGET ,
						D3DCOLOR_XRGB ( 0x20, 0x50, 0x50 ),
						1.0, 0 );

	// 描画の開始
	pD3Device -> BeginScene();

	
}