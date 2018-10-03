#include <Windows.h>
#include "joystick_XInput.h"

XINPUT_STATE CXInput::xCurrentkState;	//	XInputGetState����̏�������p
CXInput::STICK_STATE CXInput::StickState[XUSER_MAX_COUNT];	//	�擾�\�X�e�B�b�N���̔z��

/*
	private
*/
//	�R���X�g���N�^
CXInput::CXInput() 
{

}

//	�{�^���̃`�F�b�N
//	�g���K�[�ȊO�̏�ԍX�V�i�g���K�[��0�`255�ŉ��������o��̂Łj
//	@pragma	_user	���Ԗڂ̃X�e�B�b�N��
void CXInput::CheckButton( int _user )
{
	WORD wTemp = xCurrentkState.Gamepad.wButtons;

	for( int iType = 0; iType < STICK_TYPE_MAX; iType++ )
	{
		WORD wConst = 0;
		BYTE bTrigger = 0;
		eSTICK_STATE stTemp = StickState[_user].Button[iType];

		switch( iType )
		{
		case CROSS_UP:
			wConst = XINPUT_GAMEPAD_DPAD_UP;
			break;
		case CROSS_DOWN:
			wConst = XINPUT_GAMEPAD_DPAD_DOWN;
			break;
		case CROSS_LEFT:
			wConst = XINPUT_GAMEPAD_DPAD_LEFT;
			break;
		case CROSS_RIGHT:
			wConst = XINPUT_GAMEPAD_DPAD_RIGHT;
			break;
		
		case BUTTON_START:
			wConst = XINPUT_GAMEPAD_START;
			break;
		case BUTTON_BACK:
			wConst = XINPUT_GAMEPAD_BACK;
			break;
		
		case BUTTON_LEFT_THUMB:
			wConst = XINPUT_GAMEPAD_LEFT_THUMB;
			break;
		case BUTTON_RIGHT_THUMB:
			wConst = XINPUT_GAMEPAD_RIGHT_THUMB;			
			break;
		case BUTTON_LEFT_SHOULDER:
			wConst = XINPUT_GAMEPAD_LEFT_SHOULDER;			
			break;
		case BUTTON_RIGHT_SHOULDER:
			wConst = XINPUT_GAMEPAD_RIGHT_SHOULDER;				
			break;
		
		case BUTTON_A:
			wConst = XINPUT_GAMEPAD_A;				
			break;
		case BUTTON_B:
			wConst = XINPUT_GAMEPAD_B;				
			break;
		case BUTTON_X:
			wConst = XINPUT_GAMEPAD_X;				
			break;
		case BUTTON_Y:
			wConst = XINPUT_GAMEPAD_Y;				
			break;
		
		case L_TRIGGER:
			wConst = 0;
			bTrigger = xCurrentkState.Gamepad.bLeftTrigger;
			break;
		case R_TRIGGER:
			wConst = 0;
			bTrigger = xCurrentkState.Gamepad.bRightTrigger;
			break;
		}

		if( wTemp & wConst && iType < L_TRIGGER )
		{
			if( stTemp > ON )
				StickState[_user].Button[iType] = PUSH;
			else
				StickState[_user].Button[iType] = ON;
		}
		else if( iType >= L_TRIGGER && bTrigger > 0  )
		{
			if( stTemp )
				StickState[_user].Button[iType] = ON;
			else
				StickState[_user].Button[iType] = PUSH;
		}
		else
		{
			if( stTemp < RELEASE )
				StickState[_user].Button[iType] = RELEASE;
			else
				StickState[_user].Button[iType] = OFF;
		}
	}
}

//	�g���K�[�̃`�F�b�N
//	�E���g���K�[�̌X���x��������eSTICK_STATE�Ŕ��f
//	@pragma	_user	���Ԗڂ̃X�e�B�b�N��
void CXInput::CheckTrigger( int _user )
{

}

//	���E�X�e�B�b�N�̃`�F�b�N
//	�i�K�I�ɏ�Ԃ�ݒ肷�邩�͌�����
//	@pragma	_user	���Ԗڂ̃X�e�B�b�N��
void CXInput::CheckLRStick( int _user )
{

}

/*
	public
*/
//	�X�e�B�b�N���z��̏�����
void CXInput::Initialize()
{
	for( int iUser = 0; iUser < XUSER_MAX_COUNT; iUser++ )
	{
		for( int iType = 0; iType < STICK_TYPE_MAX; iType++ )
			StickState[iUser].Button[iType] = OFF;
	}

	//	XINPUT_STATE�^�̂�ZeroMemory��
	ZeroMemory( &xCurrentkState, sizeof(XINPUT_STATE) );
}

//	�S�X�e�B�b�N���̍X�V
void CXInput::UpdateStick()
{
	DWORD dwResult;	//	XInputGetState�֐��̌��ʗp

	for( int iStick = 0; iStick < XUSER_MAX_COUNT; iStick++ )
	{
		//	XINPUT_STATE�^�̂�ZeroMemory��
		//ZeroMemory( &xCurrentkState, sizeof(XINPUT_STATE) );

		//	���݂̃X�e�B�b�N��Ԃ��擾
		dwResult = XInputGetState( iStick, &xCurrentkState );

		if( dwResult == ERROR_SUCCESS )	// �X�e�B�b�N���Ȃ����Ă���
		{ 
			CheckButton( iStick );
			CheckTrigger( iStick );
			CheckLRStick( iStick );
		}
		else	// �Ȃ����ĂȂ�
		{
			
		}
	}
}

//	StickState�z�������X�e�B�b�N�̏�Ԃ��`�F�b�N
//	@pragma _user	�v���C���[�ԍ��i0�`3�j
//	@pragma	_type	�{�^���̎��
//	@pragma _state	�{�^���̏��
//	@return	true�F�X�e�B�b�N���w�肵���ʂ�̏�ԁAfalse�F�w�肵����Ԃƈ����
bool CXInput::CheckStickState( int _user, eSTICK_TYPE _type, eSTICK_STATE _state )
{
	bool bCheckF = false;

	if( StickState[_user].Button[_type] == _state )
		bCheckF = true;

	return bCheckF;
}
