#include "device.h"
#include "Key.h"

//-------------------------------------------------------
//	�O���ϐ�
//-------------------------------------------------------
LPDIRECTINPUTDEVICE8	pKeyDevice		= NULL; //�L�[�f�o�C�X -> �O���L�[����

// �L�[�̏�Ԃ���ޕʂɊi�[����ϐ�
int Key[KEYMAX];

// �L�[�̎�ޕʂɉ�����Ă��邩�̃t���O
bool PreKey[KEYMAX] = {false};

//	�L�[�f�o�C�X�̎擾
LPDIRECTINPUTDEVICE8	GetKeyDevice () { return pKeyDevice; }

//-----------------------------------------------------------------------------
// �L�[�{�[�h�p�I�u�W�F�N�g�쐬
//-----------------------------------------------------------------------------
HRESULT InitKeyDevice ( HWND hWnd )
{
	LPDIRECTINPUT8 pDinput = GetInputDevice ();
	
	HRESULT hr;
	
	//�DirectInput�f�o�C�X��I�u�W�F�N�g�̍쐬(�L�[�{�[�h)
	if(FAILED (hr = pDinput->CreateDevice (	GUID_SysKeyboard,
											&pKeyDevice,
											NULL ) ) )
	{
		return hr;
	}
	//�f�o�C�X���L�[�{�[�h�ɐݒ�
	if(FAILED (hr = pKeyDevice->SetDataFormat (&c_dfDIKeyboard) ) )
	{
		return hr;
	}
	//�������x���̐ݒ�		*���Y�A�v���P�[�V����(�Q�[��)�ƁAwindowsOS���̂̃L�[�{�[�h�f�o�C�X�̐�L���ݒ�
	if(FAILED (hr = pKeyDevice->SetCooperativeLevel( hWnd,
													 DISCL_NONEXCLUSIVE | DISCL_BACKGROUND ) ) )	// * ��r���Ńo�b�N�E�O���E���h
	{
		return hr;
	}
	//�f�o�C�X��擾�����
	pKeyDevice->Acquire();	// * �쐬�����f�o�C�X�ւ̃A�N�Z�X���擾
	
	return S_OK;
}

//==================================================================
//	�L�[��ԃ`�F�b�N
// ��1����( �L�[�̒萔 )�A��2����( �L�[�̎�� )
//=================================================================
//	��1����( �L�[�̒萔 )�A��2����( �L�[�̎�� )
void KeyCheck ( int DIK, int st )
{
	HRESULT hr = pKeyDevice->Acquire();		//�f�o�C�X�ւ̃A�N�Z�X���̍Ď擾
	
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

//	�L�[�ʏ�Ԕ���
//	��1����( �L�[�̎�� )�A��2����( �L�[�̏�� )
bool StCheck(int st, int Keyst) 
{
	return ( Key[st] == Keyst );
}

//	�S�ẴL�[�̏�ԃ`�F�b�N
void AllKeyCheck ()
{
	KeyCheck ( DIK_RETURN, ENTER );
	KeyCheck ( DIK_A, LEFT );
	KeyCheck ( DIK_D, RIGHT );
	KeyCheck ( DIK_W, UP );
	KeyCheck ( DIK_S, DOWN );
}
