#include "FreeDX.h"

//VOID FreeDx()
// �쐬����DirectX�I�u�W�F�N�g�̊J��
//
void FreeDx(bool flag)
{		
	//	�L�[�f�o�C�X�̉��
	if( pKeyDevice ) 
	{
		pKeyDevice->Unacquire();
	}
	//	�}�E�X�f�o�C�X�̉��
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