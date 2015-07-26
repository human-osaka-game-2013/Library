#include "SceneManage.h"
#include "../scr/Logo.h"
#include "../scr/Title.h"
#include "../scr/Select.h"
#include "../scr/Battle.h"
#include "../scr/Result.h"

//	コンストラクタ
CSceneManager::CSceneManager( int _iScene ) : m_sceneObj( NULL ), iCurrentScene( _iScene ), bChangeSceneFlag( false )
{
	m_RenderManage = new CRenderManager();
}

//	シーン管理
void CSceneManager::Manage ()
{
	static int	iBeforeScene = NONE;	//	前のシーン。最初だけNONEで初期化

	//	シーン変更フラグが立っているので、CSceneを継承しているクラスからIDを引き抜く
	if ( GetChangeSceneFlag() == true )
		iCurrentScene = m_sceneObj->GetSceneID();	//	現在のシーンを切り替える
	
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

//	CRnderManagerのオブジェクトのポインタを取得
CRenderManager* CSceneManager::GetRndManager() { return m_RenderManage; }

//	今のシーン状態を取得
int	CSceneManager::GetCurrentScene() { return iCurrentScene; }
//	シーン変更フラグを取得
bool CSceneManager::GetChangeSceneFlag() { return  bChangeSceneFlag; }
//	シーン変更フラグの更新
void CSceneManager::UpdateChangeFlag( bool _bTemp ) { bChangeSceneFlag = _bTemp; }

//	シーンオブジェクトの解放
bool CSceneManager::DeleteSceneObj()
{
	CLASS_DELETE( m_sceneObj );
	CLASS_DELETE( m_RenderManage );
	if( m_sceneObj == NULL && m_RenderManage == NULL )
		return true;

	return false;
}