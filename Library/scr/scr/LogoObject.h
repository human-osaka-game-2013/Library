
#ifndef _LOGOOBJECT_H_
#define _LOGOOBJECT_H_
#include "../library/gameObject.h"

class CLogoObject : public CGameObject
{

public:
	//	コンストラクタ
	CLogoObject();

public:
	//	移動(オブジェクト制御)の関数
	void Move();

	//	描画の関数
	void Draw();
};

#endif