#ifndef _SCENE_H_
#define _SCENE_H_
#include "../library/RenderManage.h"
#include "gameObject.h"
#include <list>

class CScene
{
public:
	
private:

protected:
	int m_sceneID;	//	�V�[��ID�ۑ��ϐ�(�R���X�g���N�^�̎��ɃV�[��ID������)
	int m_count;	//	�V�[�����ł̃J�E���g

public:
	//	�R���X�g���N�^
	CScene( int _id );
	//	�f�X�g���N�^
	~CScene();
public:
	virtual bool Init() = 0;		// �������̉��z�֐�
	virtual int	 Control()	= 0;	// �����̉��z�֐�	
									// GetSceneID()�ŃV�[��ID��Ԃ��āA�}�l�[�W���[�̕��ŃV�[���ύX�Ɏg�킹��
	virtual void Draw()	= 0;		// 2D�`��̉��z�֐�
	virtual void Render( CRenderManager* pRndMg )	= 0;	// 3D�`��̉��z�֐�

public:
	//	�V�[��ID���擾
	int GetSceneID();	

	//	�V�[��ID���X�V
	void SetSceneID( int _id );
};

#endif