#include "graphic.h"

// 3D•`‰æ‘Oˆ—
void BeginRender ( HRESULT* hr )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	if ( !pD3Device )
	{

	}

	pD3Device->LightEnable(0, TRUE);

	// ‰æ–Ê‚ÌÁ‹Ž
	pD3Device -> Clear (0, NULL,
						D3DCLEAR_TARGET ,
						D3DCOLOR_XRGB ( 0x20, 0x50, 0x50 ),
						1.0, 0 );

	// •`‰æ‚ÌŠJŽn
	pD3Device -> BeginScene();

	
}