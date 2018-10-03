#include "device.h"
#include "Mouse.h"

struct	MOUSE_VOL
{
	long	lMVolX, lMVolY, lMVolZ;
};

//-------------------------------------------------------
//	�O���ϐ�
//-------------------------------------------------------
LPDIRECTINPUTDEVICE8	pMouseDevice	= NULL; //�}�E�X�f�o�C�X -> �O���}�E�X����

//	�}�E�X�̏�Ԃ���ޕʂɊi�[����ϐ�
int		Mouse[MOUSEMAX];
//	�}�E�X�̎�ޕʂɉ�����Ă��邩�̃t���O
bool	PreMouse[MOUSEMAX] = {false};

//	�}�E�X���W���i�[����\����
POINT	poCurrentCursor;	//	���݂̃}�E�X���W
POINT	poBeforeCursor;		//	�O�̃}�E�X���W
MOUSE_VOL	moveMouseVol;	//	�}�E�X�̈ړ���

//	�}�E�X�f�o�C�X�̎擾
LPDIRECTINPUTDEVICE8	GetMouseDevice () { return pMouseDevice; }

//	�}�E�X���W�̎擾XY
long GetCursorPosX () { return poCurrentCursor.x; }
long GetCursorPosY () { return poCurrentCursor.y; }

long GetCursorMoveVolX () { return moveMouseVol.lMVolX; }
long GetCursorMoveVolY () { return moveMouseVol.lMVolY; }

//-----------------------------------------------------------------------------
// �}�E�X�p�I�u�W�F�N�g�쐬
//-----------------------------------------------------------------------------
HRESULT InitMouseDevice ( HWND hWnd, bool bForeGroundMode )
{
	LPDIRECTINPUT8 pDinput = GetInputDevice ();

	HRESULT hr;
	LPDIENUMDEVICESCALLBACK lpCallback	= NULL;
	LPVOID	pvRef	= NULL;		
	HGLOBAL	hGlobal	= NULL;	//	�O���[�o���n���h��	
	
	//�DirectInput�f�o�C�X��I�u�W�F�N�g�̍쐬(�}�E�X)
	if(FAILED (hr = pDinput->CreateDevice ( GUID_SysMouseEm,
											&pMouseDevice,
											NULL ) ) )
	{
		return hr;
	}

	//�f�o�C�X���}�E�X�ɐݒ�
	if(FAILED (hr = pMouseDevice->SetDataFormat (&c_dfDIMouse) ) )
	{
		return hr;
	}

	if ( bForeGroundMode )	// �t�H�A�O���E���h�Ń}�E�X���g���Ȃ�
	{
		//	�}�E�X�̓���̐ݒ�
		if(FAILED (hr = pMouseDevice->SetCooperativeLevel( hWnd,
														   DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
		{
			return hr;
		}
	}
	else
	{
		//	�}�E�X�̓���̐ݒ�
		if(FAILED (hr = pMouseDevice->SetCooperativeLevel( hWnd,
														   DISCL_EXCLUSIVE | DISCL_BACKGROUND ) ) )
		{
			/*return hr;*/
		}
	}

	//	�C�x���g�ʒm���g���ă}�E�X�̓�������o������@�ƁA
	//	�}�E�X����̃o�b�t�@�����O���͂�ǂݎ��
	hGlobal = CreateEvent(NULL, FALSE, FALSE, NULL);

	if( hGlobal == NULL )
	{
		return FALSE;
	}
	//	�f�o�C�X��Ԃ��ω������Ƃ��ɐݒ肳���C�x���g���w�肷��
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

	//	�f�o�C�X�̓�����`����v���p�e�B��ݒ肷��
	if (FAILED ( hr = pMouseDevice->SetProperty( DIPROP_BUFFERSIZE,
												 &dipdw.diph ) ) )
	{
		return hr;
	}

	//�f�o�C�X��擾�����
	pMouseDevice->Acquire();	// * �쐬�����f�o�C�X�ւ̃A�N�Z�X���擾
	
	return S_OK;
}

//	�}�E�X��ԃ`�F�b�N
//	����1�F�{�^���̎��
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

//	�}�E�X�̑S�Ẵ{�^�����`�F�b�N
void AllButtonCheck ()
{
	MouseCheck ( MOUSE_L );
	MouseCheck ( MOUSE_R );
	MouseCheck ( MOUSE_C );
}

//	�}�E�X�{�^���ʏ�Ԕ���
//	��1����( �{�^���̎�� )�A��2����( �{�^���̏�� )
bool MouseStCheck ( int st, int MouseSt )
{
	return	 Mouse[st] == MouseSt ? true : false ;
}

//	�}�E�X���W�̎擾�Ɩ��t���[���Ԃ̈ړ��ʂ��X�V�B
//	����1�F�E�C���h�E�n���h��
void CursorSet(HWND hWnd)
{
	GetCursorPos( &poCurrentCursor );

	ScreenToClient( hWnd, &poCurrentCursor );

	moveMouseVol.lMVolX = poCurrentCursor.x - poBeforeCursor.x;
	moveMouseVol.lMVolY = poCurrentCursor.y - poBeforeCursor.y;

	poBeforeCursor = poCurrentCursor;	
}