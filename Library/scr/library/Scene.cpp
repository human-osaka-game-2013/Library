
#include "Scene.h"
//	コンストラクタ
CScene::CScene( int _id ) : m_sceneID( _id )
{

}

//	デストラクタ
CScene::~CScene()
{

}

//	自分のシーンIDを取得
int CScene::GetSceneID()
{
	return m_sceneID;
}

//	シーンIDを更新
void CScene::SetSceneID( int _id )
{
	m_sceneID = _id;
}