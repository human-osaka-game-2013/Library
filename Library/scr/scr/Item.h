#ifndef _ITEM_H_
#define _ITEM_H_

#include "BattleObject.h"
//	ゲーム内でのアイテムクラス
//	主に派生元クラスとして使う
class CItem : public CBattleObject
{
public:
	void*	pCharaPtr;	//	使用主のポインタ
public:
	//	アイテム使用関数
	virtual void Use() = 0;	
	//	アイテム破棄関数
	virtual void Throw() = 0;
};

#endif