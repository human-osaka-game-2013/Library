#include <stdio.h>
#include "SceneManage.h"

//---------------------------------------------------
//	�v���g�^�C�v�錾
//---------------------------------------------------


//	�V�[���N���X�̃��[�`���̐���
void CSceneManager::SceneRoutingManage ()
{
	int _SceneIDTemp = NONE;

	if ( true == GetChangeSceneFlag() )
	{
		m_sceneObj -> Init ();
		UpdateChangeFlag ( false );	//	�V�[���ύX���I���A���������ʂ�������
	}

	if( _SceneIDTemp = m_sceneObj -> Control () )	//	true���Ԃ��Ă�����V�[���ύX
	{
		if( _SceneIDTemp != GetCurrentScene() )	//	�n���ꂽ�V�[���ƃ}�l�[�W���[���̍��̃V�[�����Ⴄ�̂�
			UpdateChangeFlag(true);	//	�ύX�t���O�𗧂Ă�
	}

}