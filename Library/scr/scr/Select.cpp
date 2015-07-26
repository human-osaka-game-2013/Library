
#include "Battle.h"

//	コンストラクタ
CBattle::CSelect::CSelect( CBattle* _pBattle ) : pBattle( _pBattle )
{
	
}

//	初期化
bool CBattle::CSelect::Init()
{

	return true;
}

//	処理
int	 CBattle::CSelect::Control()
{

	return 1;
}

//	2D描画
void CBattle::CSelect::Draw()
{

}

//	3D描画
void CBattle::CSelect::Render( CRenderManager* pRndMg )
{

}