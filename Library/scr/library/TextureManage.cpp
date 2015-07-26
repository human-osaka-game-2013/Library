#include "graphic.h"
#include "Texture.h"

TEXTUREINFO TextureInfo [TEXTURE_MAX];

TEXTUREINFO* GetTextInfo () { return TextureInfo; }

// テクスチャの読み込み
// 第1引数：("画像の名前.拡張子"), 第2引数：テクスチャの番号, 透過色RGB 
bool LoadTexture ( LPCSTR lpFileName, int TextuerNumber, int iColorRed, int iColorGreen, int iColorBlue )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	// テクスチャを既に読み込んでいる場合はここで解放する
	if ( FAILED (D3DXCreateTextureFromFileExA (
					pD3Device,
					lpFileName,
					D3DX_DEFAULT_NONPOW2,
					D3DX_DEFAULT_NONPOW2,
					D3DX_DEFAULT,
					0,
					D3DFMT_UNKNOWN,
					D3DPOOL_MANAGED,
					D3DX_FILTER_NONE,
					D3DX_FILTER_NONE,
					D3DCOLOR_ARGB ( 0, iColorRed, iColorGreen, iColorBlue ),
					NULL, NULL,
					&TextureInfo [TextuerNumber].pTexture))) {
						MessageBoxA(0,"テクスチャが読み込めませんでした(＞＜;)",NULL,MB_OK);
						return false;
	}

	// テクスチャ情報取得
	D3DSURFACE_DESC desc;

	TextureInfo [TextuerNumber].pTexture -> GetLevelDesc ( 0, &desc );
	TextureInfo [TextuerNumber].width = desc.Width;
	TextureInfo [TextuerNumber].height = desc.Height;

	

	return true;
}

//	使用する全ての画像を読み込み
bool AllLoadTexture ()
{
	LoadTexture ( "resource/texture/Logo.png", TEX_TEAM_LOGO, 0, 0, 255 );
	LoadTexture ( "resource/texture/stage1.png", TEX_BACKGROUND, 0, 0, 255 );

	return true;
}

// テクスチャの解放
// 第1引数：テクスチャの番号
void ReleaseTexture ( int TextuerNumber )
{
	SAFE_RELEASE ( TextureInfo[TextuerNumber].pTexture );
}

// 使用している全てのテクスチャの解放
void ReleaseAllTexture ()
{
	for ( int i = 0; i < TEXTURE_MAX; i++ )
	{
		ReleaseTexture (i);
	}
}