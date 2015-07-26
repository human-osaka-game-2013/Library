#include "Input.h"

#ifndef	_KEY_H_
#define _KEY_H_

// 使用するキーの種類
// KeyCheckと共に使うキーが増えればココに種類を追加していく
enum eKEYKIND
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	JUMP,
	FIRE,

	ENTER,

	KEYMAX
};

#endif