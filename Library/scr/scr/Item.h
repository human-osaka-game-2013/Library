#ifndef _ITEM_H_
#define _ITEM_H_

#include "BattleObject.h"
//	�Q�[�����ł̃A�C�e���N���X
//	��ɔh�����N���X�Ƃ��Ďg��
class CItem : public CBattleObject
{
public:
	void*	pCharaPtr;	//	�g�p��̃|�C���^
public:
	//	�A�C�e���g�p�֐�
	virtual void Use() = 0;	
	//	�A�C�e���j���֐�
	virtual void Throw() = 0;
};

#endif