#include "FreeDX.h"

//VOID FreeDx()
// 作成したDirectXオブジェクトの開放
//
void FreeDx(bool flag)
{		
	//	キーデバイスの解放
	if( pKeyDevice ) 
	{
		pKeyDevice->Unacquire();
	}
	//	マウスデバイスの解放
	if( pMouseDevice ) 
	{
		pMouseDevice->Unacquire();
	}
	
	SAFE_RELEASE( pKeyDevice );
	SAFE_RELEASE( pMouseDevice );
	SAFE_RELEASE( pDinput );

	if(flag)
	{
		SAFE_RELEASE( pDirect3D );
		SAFE_RELEASE( pD3Device );
	}
}