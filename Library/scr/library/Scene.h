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
	int m_sceneID;	//	シーンID保存変数(コンストラクタの時にシーンIDが入る)
	int m_count;	//	シーン内でのカウント

public:
	//	コンストラクタ
	CScene( int _id );
	//	デストラクタ
	~CScene();
public:
	virtual bool Init() = 0;		// 初期化の仮想関数
	virtual int	 Control()	= 0;	// 処理の仮想関数	
									// GetSceneID()でシーンIDを返して、マネージャーの方でシーン変更に使わせる
	virtual void Draw()	= 0;		// 2D描画の仮想関数
	virtual void Render( CRenderManager* pRndMg )	= 0;	// 3D描画の仮想関数

public:
	//	シーンIDを取得
	int GetSceneID();	

	//	シーンIDを更新
	void SetSceneID( int _id );
};

#endif