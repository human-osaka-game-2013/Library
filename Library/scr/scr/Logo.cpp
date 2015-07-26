
#include "../library/AllInput.h"
#include "Logo.h"
#include "../library/Texture.h"

//	コンストラクタ
CLogo::CLogo( int _id ) : CScene( _id )
{
	m_count = 0;
}

//	初期化
bool CLogo::Init()
{
	logo.SetID( TEX_TEAM_LOGO );
	return true;
}

//	処理
int	 CLogo::Control()
{
	logo.Move();

	if( StCheck( ENTER, PUSH ) )
	{

	}
	//	シーン変更の更新
	return GetSceneID();
}

//	2D描画
void CLogo::Draw()
{
	logo.Draw();
}
