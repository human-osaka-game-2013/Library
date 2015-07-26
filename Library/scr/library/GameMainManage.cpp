#include <stdio.h>
#include "SceneManage.h"

//---------------------------------------------------
//	プロトタイプ宣言
//---------------------------------------------------


//	シーンクラスのルーチンの制御
void CSceneManager::SceneRoutingManage ()
{
	int _SceneIDTemp = NONE;

	if ( true == GetChangeSceneFlag() )
	{
		m_sceneObj -> Init ();
		UpdateChangeFlag ( false );	//	シーン変更も終わり、初期化も通ったから
	}

	if( _SceneIDTemp = m_sceneObj -> Control () )	//	trueが返ってきたらシーン変更
	{
		if( _SceneIDTemp != GetCurrentScene() )	//	渡されたシーンとマネージャー側の今のシーンが違うので
			UpdateChangeFlag(true);	//	変更フラグを立てる
	}

}