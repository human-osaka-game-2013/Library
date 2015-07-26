#ifndef _SELECT_H_
#define _SELECT_H_
#include "../library/Scene.h"

class CSelect : public CScene
{
private:

public:
	//	コンストラクタ
	CSelect( int _id );

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