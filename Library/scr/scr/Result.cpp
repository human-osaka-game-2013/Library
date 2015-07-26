
#include "Battle.h"

//	コンストラクタ
CBattle::CResult::CResult( CBattle* _pBattle ) : pBattle( _pBattle )
{

}

//	初期化
bool CBattle::CResult::Init()
{

	return true;
}

//	処理
int	 CBattle::CResult::Control()
{

	return 1;
}

//	2D描画
void CBattle::CResult::Draw()
{

}

//	3D描画
void CBattle::CResult::Render( CRenderManager* pRndMg )
{

}