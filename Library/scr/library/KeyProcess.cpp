#include "device.h"
#include "Key.h"

//-------------------------------------------------------
//	外部変数
//-------------------------------------------------------
LPDIRECTINPUTDEVICE8	pKeyDevice		= NULL; //キーデバイス -> 外部キー入力

// キーの状態を種類別に格納する変数
int Key[KEYMAX];

// キーの種類別に押されているかのフラグ
bool PreKey[KEYMAX] = {false};

//	キーデバイスの取得
LPDIRECTINPUTDEVICE8	GetKeyDevice () { return pKeyDevice; }

//-----------------------------------------------------------------------------
// キーボード用オブジェクト作成
//-----------------------------------------------------------------------------
HRESULT InitKeyDevice ( HWND hWnd )
{
	LPDIRECTINPUT8 pDinput = GetInputDevice ();
	
	HRESULT hr;
	
	//｢DirectInputデバイス｣オブジェクトの作成(キーボード)
	if(FAILED (hr = pDinput->CreateDevice (	GUID_SysKeyboard,
											&pKeyDevice,
											NULL ) ) )
	{
		return hr;
	}
	//デバイスをキーボードに設定
	if(FAILED (hr = pKeyDevice->SetDataFormat (&c_dfDIKeyboard) ) )
	{
		return hr;
	}
	//協調レベルの設定		*当該アプリケーション(ゲーム)と、windowsOS自体のキーボードデバイスの占有率設定
	if(FAILED (hr = pKeyDevice->SetCooperativeLevel( hWnd,
													 DISCL_NONEXCLUSIVE | DISCL_BACKGROUND ) ) )	// * 非排他でバック・グラウンド
	{
		return hr;
	}
	//デバイスを｢取得｣する
	pKeyDevice->Acquire();	// * 作成したデバイスへのアクセス権取得
	
	return S_OK;
}

//==================================================================
//	キー状態チェック
// 第1引数( キーの定数 )、第2引数( キーの種類 )
//=================================================================
//	第1引数( キーの定数 )、第2引数( キーの種類 )
void KeyCheck ( int DIK, int st )
{
	HRESULT hr = pKeyDevice->Acquire();		//デバイスへのアクセス権の再取得
	
	if( (hr==DI_OK) || (hr==S_FALSE) )	
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof (diks), &diks);

		if ( diks[DIK] & 0x80 )
		{
			if ( !PreKey[st] )
			{
				Key[st] = PUSH;
			}
			else
			{
				Key[st] = ON;
			}
			PreKey[st] = true;
		}

		else
		{
			if ( !PreKey[st] )
			{
				Key[st] = OFF;
			}
			else
			{
				Key[st] = RELEASE;
			}
			PreKey[st] = false;
		}
	}
}

//	キー別状態判定
//	第1引数( キーの種類 )、第2引数( キーの状態 )
bool StCheck(int st, int Keyst) 
{
	return ( Key[st] == Keyst );
}

//	全てのキーの状態チェック
void AllKeyCheck ()
{
	KeyCheck ( DIK_RETURN, ENTER );
	KeyCheck ( DIK_A, LEFT );
	KeyCheck ( DIK_D, RIGHT );
	KeyCheck ( DIK_W, UP );
	KeyCheck ( DIK_S, DOWN );
}
