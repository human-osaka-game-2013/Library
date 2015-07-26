
#ifndef	_MOUSE_FUNC_H_
#define _MOUSE_FUNC_H_

long GetCursorPosX ();	//	マウス座標の取得X
long GetCursorPosY ();	//	マウス座標の取得Y

long GetCursorMoveVolX ();	//	マウスの移動量の取得X
long GetCursorMoveVolY ();	//	マウスの移動量の取得Y

void AllButtonCheck ();	//	マウスの全てのボタンをチェック
//	マウスボタン別状態判定
//	第1引数( ボタンの種類 )、第2引数( ボタンの状態 )
bool MouseStCheck ( int, int );

#endif