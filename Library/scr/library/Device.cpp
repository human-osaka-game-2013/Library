#include "device.h"
#include "joystick_XInput.h"

//---------------------------------------------------
//	プロトタイプ宣言
//---------------------------------------------------

// キーボード用オブジェクト作成
HRESULT InitKeyDevice ( HWND );

// マウス用オブジェクト作成
HRESULT InitMouseDevice ( HWND, bool bForeGroundMode = true );

//---------------------------------------------------
// ポインタ変数宣言
//---------------------------------------------------
LPDIRECT3D9				pDirect3D;	//3Dオブジェクト
D3DPRESENT_PARAMETERS	d3dpp;
LPDIRECT3DDEVICE9	pD3Device;
LPDIRECTINPUT8			pDinput	= NULL; //インプット -> 入力処理

//	
LPDIRECT3DDEVICE9	Getd3Device () { return pD3Device; }
//
LPDIRECTINPUT8	GetInputDevice () { return pDinput; }

// Direct3Dの初期化
// 第1引数：ウインドハンドル
HRESULT InitD3d ( HWND hWnd )
{
	D3DDISPLAYMODE d3ddm;
	
	// DirectX オブジェクトの生成
	if( NULL == ( pDirect3D = Direct3DCreate9 ( D3D_SDK_VERSION ) ) )
	{
		MessageBoxA(0,"Direct3Dの作成に失敗しました","",MB_OK);
		return E_FAIL;
	}

	// Display Mode の設定
	pDirect3D -> GetAdapterDisplayMode ( D3DADAPTER_DEFAULT, &d3ddm );

	ZeroMemory(	&d3dpp, sizeof ( d3dpp ));

	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount  = 1;
	d3dpp.SwapEffect	   = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed		   = TRUE;

	if( FAILED( pDirect3D->CreateDevice( D3DADAPTER_DEFAULT,
										 D3DDEVTYPE_HAL,
										 hWnd,
										 D3DCREATE_HARDWARE_VERTEXPROCESSING,
										 &d3dpp,
										 &pD3Device ) ) )
	{
		MessageBoxA(0,"HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します",NULL,MB_OK);
		if( FAILED( pDirect3D->CreateDevice( D3DADAPTER_DEFAULT,
											 D3DDEVTYPE_REF,
											 hWnd,
											 D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											 &d3dpp,
											 &pD3Device ) ) )
		{
			MessageBoxA(0,"DIRECT3Dデバイスの作成に失敗しました",NULL,MB_OK);
				return E_FAIL;
		}    
	}

	return S_OK;
}

//ダイレクトインプットの初期化関数
HRESULT InitDinput(HWND hWnd)
{
	HRESULT hr;
	
	//｢DirectInput｣オブジェクトの作成
	if(FAILED (hr = DirectInput8Create ( GetModuleHandle(NULL),
										 DIRECTINPUT_VERSION,
										 IID_IDirectInput8,
										 (VOID**)&pDinput,
										 NULL ) ) )
	{
		return hr;
	}
	//	キーボードデバイスのオブジェクトの作成
	if (FAILED (hr = InitKeyDevice ( hWnd ) ) )
	{
		return hr;
	}
	
	//	マウスデバイスのオブジェクトの作成
	if (FAILED (hr = InitMouseDevice ( hWnd, false ) ) )
	{
		return hr;
	}	

	//	CXInputクラスの初期化
	CXInput::Initialize();

	return S_OK;
}