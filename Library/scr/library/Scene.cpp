
#include "Scene.h"
//	�R���X�g���N�^
CScene::CScene( int _id ) : m_sceneID( _id )
{

}

//	�f�X�g���N�^
CScene::~CScene()
{

}

//	�����̃V�[��ID���擾
int CScene::GetSceneID()
{
	return m_sceneID;
}

//	�V�[��ID���X�V
void CScene::SetSceneID( int _id )
{
	m_sceneID = _id;
}