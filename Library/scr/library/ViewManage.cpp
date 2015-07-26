#include "SceneManage.h"
#include "graphic.h"

//---------------------------------------------------
//	プロトタイプ宣言
//---------------------------------------------------
// 3D描画前処理
void BeginRender ( HRESULT* hr );

// 描画前処理
void BeginDraw ( HRESULT* hr );

// 描画後処理
void EndRender ();

//----------------------------------------------------

//	描画の管理
//	引数：3Dモデルを扱う時はtrueに
HRESULT CSceneManager::ViewManage ( bool b3dView )
{
	HRESULT hr;
	
	if ( b3dView == true )
	{
		RenderManage( &hr );
	}
	DrawManage( &hr );

	return hr;
}

//	レンダリング管理
void CSceneManager::RenderManage ( HRESULT* hr )
{
	BeginRender( hr );

	m_sceneObj -> Render( GetRndManager() );

	EndRender();
}

//	描画管理
void CSceneManager::DrawManage ( HRESULT* hr )
{
	BeginDraw( hr );

	m_sceneObj -> Draw();

	EndRender();
}
