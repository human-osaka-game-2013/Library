#ifndef	_GRAPHIC_H_
#define _GRAPHIC_H_

#include "lib_head.h"
//	
LPDIRECT3DDEVICE9	Getd3Device ();

//	使用する全ての画像を読み込み
bool AllLoadTexture ();

// テクスチャの番号とテクスチャ全体の縦横の大きさ
struct TEXTUREINFO
{
	// テクスチャの格納ポインタ
	LPDIRECT3DTEXTURE9	pTexture;

	int		width, height;
};

TEXTUREINFO* GetTextInfo();

// 画像の頂点座標などの構造体
struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;

	DWORD	color;

	FLOAT	tu, tv;
};
struct VERTEXS
{
	FLOAT	x, y, z, rhw;

	DWORD	color;

	FLOAT	tu, tv;
};

#endif