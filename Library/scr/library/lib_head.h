#ifndef _LIB_HEAD_INCLUDE_

#define _LIB_HEAD_INCLUDE_
#define DIRECTINPUT_VERSION 0x0800

//プリプロ関連ヘッダーファイル
#include <stdio.h>
#include <windows.h>	//window基礎ファイル
#include <d3dx9.h>	
#include <dinput.h>
#include <dinputd.h>
#include <mmsystem.h>	//wav再生
#include <XAudio2.h>	//mp3,wma再生
#include <time.h>
#include <XInput.h>
#include <cstdlib>

//ライブラリ読込
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9d.lib" )
#pragma comment ( lib, "dinput8.lib" )
#pragma comment ( lib, "dxguid.lib" )
#pragma comment	(lib, "dsound.lib")	//wav再生
#pragma comment	(lib, "winmm.lib")
#pragma comment(lib, "Xinput.lib")

#define	CLASS_DELETE(p)	{ if(p) { delete (p); (p) = NULL;} }	//	クラスポインタの削除
#define SAFE_RELEASE(p) { if(p) { (p) -> Release(); (p) = NULL; } }
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = NULL; } }
#define NULL_DELETE(p) { if(p) { delete (p); (p) = NULL; } }
#define NULL_ARRAY_DELETE(p) { if(p) { delete[] (p); (p) = NULL; } }

#define D3DFVF ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK, __FILE__, __LINE__ )
#define new DBG_NEW
#endif
#endif

#endif