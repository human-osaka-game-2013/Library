#include "graphic.h"
#include "SceneManage.h"
#include "AllInput.h"

//---------------------------------------------------
//	�v���g�^�C�v�錾
//---------------------------------------------------

//	�Q�[�����C���֐�
int CSceneManager::GameMain ( HWND hWnd )
{
	Manage();

	SceneRoutingManage();

	ViewManage( true );	//	����̃Q�[���ł�3D���g�p����̂�true

	return 0;
}