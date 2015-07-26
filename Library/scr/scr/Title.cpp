
#include "Title.h"

//	コンストラクタ
CTitle::CTitle( int _id ) : CScene( _id )
{

}

//	初期化
bool CTitle::Init()
{

	return true;		
}

//	処理
int	 CTitle::Control()
{

	return 1;
}

//	2D描画
void CTitle::Draw()
{

}

//	3D描画
void CTitle::Render( CRenderManager* pRndMg )
{

}