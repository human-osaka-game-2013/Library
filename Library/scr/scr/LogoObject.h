
#ifndef _LOGOOBJECT_H_
#define _LOGOOBJECT_H_
#include "../library/gameObject.h"

class CLogoObject : public CGameObject
{

public:
	//	�R���X�g���N�^
	CLogoObject();

public:
	//	�ړ�(�I�u�W�F�N�g����)�̊֐�
	void Move();

	//	�`��̊֐�
	void Draw();
};

#endif