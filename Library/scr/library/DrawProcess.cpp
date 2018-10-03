#include "graphic.h"

// �`��O����
void BeginDraw ( HRESULT* hr )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	if ( !pD3Device )
	{

	}

	// �X�e�[�W�X�e�[�g�̐ݒ�
	pD3Device -> SetRenderState ( D3DRS_ALPHABLENDENABLE,	true );
	
	pD3Device -> SetTextureStageState ( 0, D3DTSS_COLORARG1,	D3DTA_TEXTURE	);
	pD3Device -> SetTextureStageState ( 0, D3DTSS_COLORARG2,	D3DTA_DIFFUSE	);

	pD3Device -> SetTextureStageState ( 0, D3DTSS_COLOROP,		D3DTOP_MODULATE	);

	pD3Device -> SetTextureStageState ( 0, D3DTSS_ALPHAARG1,	D3DTA_TEXTURE	);
	pD3Device -> SetTextureStageState ( 0, D3DTSS_ALPHAARG2,	D3DTA_DIFFUSE	);

	pD3Device -> SetTextureStageState ( 0, D3DTSS_ALPHAOP,		D3DTOP_MODULATE );


	// �`����@�̐ݒ�
	pD3Device ->  SetRenderState ( D3DRS_SRCBLEND,				D3DBLEND_SRCALPHA	);
	pD3Device ->  SetRenderState ( D3DRS_DESTBLEND,				D3DBLEND_INVSRCALPHA);
	pD3Device ->  SetRenderState ( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1		);
	
	
	pD3Device -> SetRenderState ( D3DRS_ZENABLE,			false );
	

	// �`��̊J�n
	pD3Device -> BeginScene();

	// ��ʂ̕`��
	pD3Device -> SetFVF ( D3DFVF_CUSTOMVERTEX );

}

// �`��㏈��
void EndRender ()
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	// �`��̏I��
	pD3Device -> EndScene();

	// �\��
	pD3Device -> Present ( NULL, NULL, NULL, NULL );
}