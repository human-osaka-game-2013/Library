#include "device.h"
#include "Mouse.h"

struct	MOUSE_VOL
{
	long	lMVolX, lMVolY, lMVolZ;
};

//-------------------------------------------------------
//	外部変数
//-------------------------------------------------------
LPDIRECTINPUTDEVICE8	pMouseDevice	= NULL; //マウスデバイス -> 外部マウス入力

//	マウスの状態を種類別に格納する変数
int		Mouse[MOUSEMAX];
//	マウスの種類別に押されているかのフラグ
bool	PreMouse[MOUSEMAX] = {false};

//	マウス座標を格納する構造体
POINT	poCurrentCursor;	//	現在のマウス座標
POINT	poBeforeCursor;		//	前のマウス座標
MOUSE_VOL	moveMouseVol;	//	マウスの移動量

//	マウスデバイスの取得
LPDIRECTINPUTDEVICE8	GetMouseDevice () { return pMouseDevice; }

//	マウス座標の取得XY
long GetCursorPosX () { return poCurrentCursor.x; }
long GetCursorPosY () { return poCurrentCursor.y; }

long GetCursorMoveVolX () { return moveMouseVol.lMVolX; }
long GetCursorMoveVolY () { return moveMouseVol.lMVolY; }

//-----------------------------------------------------------------------------
// マウス用オブジェクト作成
//-----------------------------------------------------------------------------
HRESULT InitMouseDevice ( HWND hWnd, bool bForeGroundMode )
{
	LPDIRECTINPUT8 pDinput = GetInputDevice ();

	HRESULT hr;
	LPDIENUMDEVICESCALLBACK lpCallback	= NULL;
	LPVOID	pvRef	= NULL;		
	HGLOBAL	hGlobal	= NULL;	//	グローバルハンドル	
	
	//｢DirectInputデバイス｣オブジェクトの作成(マウス)
	if(FAILED (hr = pDinput->CreateDevice ( GUID_SysMouseEm,
											&pMouseDevice,
											NULL ) ) )
	{
		return hr;
	}

	//デバイスをマウスに設定
	if(FAILED (hr = pMouseDevice->SetDataFormat (&c_dfDIMouse) ) )
	{
		return hr;
	}

	if ( bForeGroundMode )	// フォアグラウンドでマウスを使うなら
	{
		//	マウスの動作の設定
		if(FAILED (hr = pMouseDevice->SetCooperativeLevel( hWnd,
														   DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
		{
			return hr;
		}
	}
	else
	{
		//	マウスの動作の設定
		if(FAILED (hr = pMouseDevice->SetCooperativeLevel( hWnd,
														   DISCL_EXCLUSIVE | DISCL_BACKGROUND ) ) )
		{
			/*return hr;*/
		}
	}

	//	イベント通知を使ってマウスの動作を検出する方法と、
	//	マウスからのバッファリング入力を読み取る
	hGlobal = CreateEvent(NULL, FALSE, FALSE, NULL);

	if( hGlobal == NULL )
	{
		return FALSE;
	}
	//	デバイス状態が変化したときに設定されるイベントを指定する
	if (FAILED ( hr = pMouseDevice->SetEventNotification ( hGlobal ) ) )
	{
		return hr;
	}

	DIPROPDWORD dipdw;
    // the header
    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    // the data
    dipdw.dwData            = DIPROPAXISMODE_REL;

	//	デバイスの動作を定義するプロパティを設定する
	if (FAILED ( hr = pMouseDevice->SetProperty( DIPROP_BUFFERSIZE,
												 &dipdw.diph ) ) )
	{
		return hr;
	}

	//デバイスを｢取得｣する
	pMouseDevice->Acquire();	// * 作成したデバイスへのアクセス権取得
	
	return S_OK;
}

//	マウス状態チェック
//	引数1：ボタンの種類
void MouseCheck ( int st )
{
	HRESULT	hr = pMouseDevice->Acquire();

	DIMOUSESTATE dims;

	hr = pMouseDevice->GetDeviceState(sizeof (dims), &dims);

	if ( hr== S_OK || (hr== S_FALSE) )
	{
		if ( dims.rgbButtons[st] & 0x80 )
		{
			if ( !PreMouse[st] )
			{
				Mouse[st] = PUSH;
			}
			else
			{
				Mouse[st] = ON;
			}
			PreMouse[st] = true;
		}

		else
		{
			if ( !PreMouse[st] )
			{
				Mouse[st] = OFF;
			}
			else
			{
				Mouse[st] = RELEASE;
			}
			PreMouse[st] = false;
		}
	}
}

//	マウスの全てのボタンをチェック
void AllButtonCheck ()
{
	MouseCheck ( MOUSE_L );
	MouseCheck ( MOUSE_R );
	MouseCheck ( MOUSE_C );
}

//	マウスボタン別状態判定
//	第1引数( ボタンの種類 )、第2引数( ボタンの状態 )
bool MouseStCheck ( int st, int MouseSt )
{
	return	 Mouse[st] == MouseSt ? true : false ;
}

//	マウス座標の取得と毎フレーム間の移動量を更新。
//	引数1：ウインドウハンドル
void CursorSet(HWND hWnd)
{
	GetCursorPos( &poCurrentCursor );

	ScreenToClient( hWnd, &poCurrentCursor );

	moveMouseVol.lMVolX = poCurrentCursor.x - poBeforeCursor.x;
	moveMouseVol.lMVolY = poCurrentCursor.y - poBeforeCursor.y;

	poBeforeCursor = poCurrentCursor;	
}