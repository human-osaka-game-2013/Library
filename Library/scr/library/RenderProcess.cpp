#include "graphic.h"

// 3D�`��O����
void BeginRender ( HRESULT* hr )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	if ( !pD3Device )
	{

	}

	pD3Device->LightEnable(0, TRUE);

	// ��ʂ̏���
	pD3Device -> Clear (0, NULL,
						D3DCLEAR_TARGET ,
						D3DCOLOR_XRGB ( 0x20, 0x50, 0x50 ),
						1.0, 0 );

	// �`��̊J�n
	pD3Device -> BeginScene();

	
}