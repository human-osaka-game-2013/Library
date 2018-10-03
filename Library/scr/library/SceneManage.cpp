#include "SceneManage.h"
#include "../scr/Logo.h"
#include "../scr/Title.h"
#include "../scr/Select.h"
#include "../scr/Battle.h"
#include "../scr/Result.h"

//	�R���X�g���N�^
CSceneManager::CSceneManager( int _iScene ) : m_sceneObj( NULL ), iCurrentScene( _iScene ), bChangeSceneFlag( false )
{
	m_RenderManage = new CRenderManager();
}

//	�V�[���Ǘ�
void CSceneManager::Manage ()
{
	static int	iBeforeScene = NONE;	//	�O�̃V�[���B�ŏ�����NONE�ŏ�����

	//	�V�[���ύX�t���O�������Ă���̂ŁACScene���p�����Ă���N���X����ID����������
	if ( GetChangeSceneFlag() == true )
		iCurrentScene = m_sceneObj->GetSceneID();	//	���݂̃V�[����؂�ւ���
	
	if ( iBeforeScene != iCurrentScene )
	{
		switch ( iCurrentScene )
		{
		case LOGO:
			CLASS_DELETE( m_sceneObj );
			m_sceneObj = new CLogo( iCurrentScene );
			
			break;

		case TITLE:
			CLASS_DELETE( m_sceneObj );
			m_sceneObj = new CTitle( iCurrentScene );

			break;

		//case SELECT:
		//	CLASS_DELETE( m_sceneObj );
		//	m_sceneObj = new CSelect( iCurrentScene );
		//	
		//	break;

		case BATTLE:
			CLASS_DELETE( m_sceneObj );
			m_sceneObj = new CBattle( iCurrentScene );
		
			break;

		//case RESULT:
		//	CLASS_DELETE( m_sceneObj );
		//	m_sceneObj = new CResult( iCurrentScene );
		//	
		//	break;
		}
		
		UpdateChangeFlag ( true );
	}
	iBeforeScene = iCurrentScene;
}

//	CRnderManager�̃I�u�W�F�N�g�̃|�C���^���擾
CRenderManager* CSceneManager::GetRndManager() { return m_RenderManage; }

//	���̃V�[����Ԃ��擾
int	CSceneManager::GetCurrentScene() { return iCurrentScene; }
//	�V�[���ύX�t���O���擾
bool CSceneManager::GetChangeSceneFlag() { return  bChangeSceneFlag; }
//	�V�[���ύX�t���O�̍X�V
void CSceneManager::UpdateChangeFlag( bool _bTemp ) { bChangeSceneFlag = _bTemp; }

//	�V�[���I�u�W�F�N�g�̉��
bool CSceneManager::DeleteSceneObj()
{
	CLASS_DELETE( m_sceneObj );
	CLASS_DELETE( m_RenderManage );
	if( m_sceneObj == NULL && m_RenderManage == NULL )
		return true;

	return false;
}