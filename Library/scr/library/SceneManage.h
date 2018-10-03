
#ifndef _SCENEMANAGE_H_
#define _SCENEMANAGE_H_
#include "RenderManage.h"
#include "Scene.h"

class CSceneManager
{
public:
	enum M_SCENE
	{
		NONE,
		LOGO,
		TITLE,
		//SELECT,
		BATTLE,
		//RESULT,

		MAX
	};

private:
	CScene*	m_sceneObj;
	CRenderManager* m_RenderManage;
	int		iCurrentScene;		//	���̃V�[��
	bool	bChangeSceneFlag;	//	�V�[���ύX�t���O

public:	
	CSceneManager( int _scene );	//	�R���X�g���N�^

public:
	//	�Q�[�����C���֐�
	int GameMain ( HWND hWnd );
	
	//	�V�[���Ǘ�
	void Manage ();
	
	//	�V�[���N���X�̃��[�`���̐���
	void SceneRoutingManage ();
	
	//	�`��̊Ǘ�
	//	�����F3D���f������������true��
	HRESULT ViewManage ( bool b3dView = false );
	
	//	�����_�����O�Ǘ�(3D)
	void RenderManage ( HRESULT* );
	
	//	�`��Ǘ�(2D)
	void DrawManage ( HRESULT* );

	//	�V�[���I�u�W�F�N�g�̉��
	bool DeleteSceneObj();

public:
	//	CRnderManager�̃I�u�W�F�N�g�̃|�C���^���擾
	CRenderManager* GetRndManager();

	//	���̃V�[����Ԃ��擾
	int		GetCurrentScene();
	//	�V�[���ύX�t���O���擾
	bool	GetChangeSceneFlag();
	//	�V�[���ύX�t���O�̍X�V
	void	UpdateChangeFlag( bool bTemp );

};

#endif
