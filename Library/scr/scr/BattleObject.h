
#ifndef _BATTLEOBJECT_H_
#define _BATTLEOBJECT_H_
#include "../library/RenderManage.h"
#include "../library/gameObject.h"

//---------------------------------------------------------------------------------------------
//	��{�I�ȃQ�[���I�u�W�F�N�g�̃N���X
//---------------------------------------------------------------------------------------------
class CBattleObject : public CGameObject
{
private:
	float m_AnimTime;
	float m_AnimTimeHold;
	int   m_DrawType;

public:
	enum DRAW_TYPE
	{
		TYPE_2D,
		TYPE_3D,
		TYPE_ANIM,
		DRAW_TYPE_MAX
	};

	//	��]�x�A�g�k��
	D3DXVECTOR3 m_vecRot, m_vecScall;
	D3DXVECTOR3 vecBeforePos;	//�O�t���[�����̒n�_

public:
	//	�R���X�g���N�^
	CBattleObject();

public:
	//�`��̎�ނ̐��l���擾
	int GetDrawType();
	//�`��̎�ނ̐��l��ݒ�
	void SetDrawType( int _type );

	float GetVectorLength( D3DXVECTOR3 _v );

public:
	//	�ړ�(�I�u�W�F�N�g����)�̊֐�
	void Move();

	//	�`��̊֐�
	void Draw(){};
	//	�`��̊֐�
	void Draw( CRenderManager* pRndMg );
};

//---------------------------------------------------------------------------------------------
//	��Q���̃N���X
//---------------------------------------------------------------------------------------------
class CBarrier : public CBattleObject
{
public:
	CBarrier();
};

#endif