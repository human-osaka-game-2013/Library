
#ifndef _RESULT_H_
#define _RESULT_H_
#include "../library/Scene.h"

class CResult : public CScene
{
private:

public:
	//	コンストラクタ
	CResult( int _id );

public:
	//	初期化
	bool Init();	
	//	処理
	int	 Control();	
	//	2D描画
	void Draw();	
	//	3D描画
	void Render( CRenderManager* pRndMg );	
};

#endif