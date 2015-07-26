#include "graphic.h"
#include "SceneManage.h"
#include "AllInput.h"

//---------------------------------------------------
//	プロトタイプ宣言
//---------------------------------------------------

//	ゲームメイン関数
int CSceneManager::GameMain ( HWND hWnd )
{
	Manage();

	SceneRoutingManage();

	ViewManage( true );	//	今回のゲームでは3Dを使用するのでtrue

	return 0;
}