
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
	int		iCurrentScene;		//	今のシーン
	bool	bChangeSceneFlag;	//	シーン変更フラグ

public:	
	CSceneManager( int _scene );	//	コンストラクタ

public:
	//	ゲームメイン関数
	int GameMain ( HWND hWnd );
	
	//	シーン管理
	void Manage ();
	
	//	シーンクラスのルーチンの制御
	void SceneRoutingManage ();
	
	//	描画の管理
	//	引数：3Dモデルを扱う時はtrueに
	HRESULT ViewManage ( bool b3dView = false );
	
	//	レンダリング管理(3D)
	void RenderManage ( HRESULT* );
	
	//	描画管理(2D)
	void DrawManage ( HRESULT* );

	//	シーンオブジェクトの解放
	bool DeleteSceneObj();

public:
	//	CRnderManagerのオブジェクトのポインタを取得
	CRenderManager* GetRndManager();

	//	今のシーン状態を取得
	int		GetCurrentScene();
	//	シーン変更フラグを取得
	bool	GetChangeSceneFlag();
	//	シーン変更フラグの更新
	void	UpdateChangeFlag( bool bTemp );

};

#endif
