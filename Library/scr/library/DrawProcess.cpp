#include "graphic.h"

// 描画前処理
void BeginDraw ( HRESULT* hr )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	if ( !pD3Device )
	{

	}

	// ステージステートの設定
	pD3Device -> SetRenderState ( D3DRS_ALPHABLENDENABLE,	true );
	
	pD3Device -> SetTextureStageState ( 0, D3DTSS_COLORARG1,	D3DTA_TEXTURE	);
	pD3Device -> SetTextureStageState ( 0, D3DTSS_COLORARG2,	D3DTA_DIFFUSE	);

	pD3Device -> SetTextureStageState ( 0, D3DTSS_COLOROP,		D3DTOP_MODULATE	);

	pD3Device -> SetTextureStageState ( 0, D3DTSS_ALPHAARG1,	D3DTA_TEXTURE	);
	pD3Device -> SetTextureStageState ( 0, D3DTSS_ALPHAARG2,	D3DTA_DIFFUSE	);

	pD3Device -> SetTextureStageState ( 0, D3DTSS_ALPHAOP,		D3DTOP_MODULATE );


	// 描画方法の設定
	pD3Device ->  SetRenderState ( D3DRS_SRCBLEND,				D3DBLEND_SRCALPHA	);
	pD3Device ->  SetRenderState ( D3DRS_DESTBLEND,				D3DBLEND_INVSRCALPHA);
	pD3Device ->  SetRenderState ( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1		);
	
	
	pD3Device -> SetRenderState ( D3DRS_ZENABLE,			false );
	

	// 描画の開始
	pD3Device -> BeginScene();

	// 画面の描画
	pD3Device -> SetFVF ( D3DFVF_CUSTOMVERTEX );

}

// 描画後処理
void EndRender ()
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	// 描画の終了
	pD3Device -> EndScene();

	// 表示
	pD3Device -> Present ( NULL, NULL, NULL, NULL );
}