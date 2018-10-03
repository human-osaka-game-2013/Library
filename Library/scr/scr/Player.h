#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "BattleObject.h"

//---------------------------------------------------------------------------------------------
//	�v���C���[�̃N���X
//---------------------------------------------------------------------------------------------
class CPlayer : public CBattleObject
{
public:
	D3DXVECTOR3	m_vecImpact;	//	���˃x�N�g��x,y,z
	bool		m_AttackFlag;	//	���˃t���O

	bool	bJumpFlag;
	bool	bDownFlag;
	bool	bLandFlag;
	float	y_prev,	y_temp;	//	�W�����v���̈ʒu�ۑ��p
	//---------------------------------------------
	int		iHitCount;	//	�����������ɓ_�ł�����ׂ̃J�E���^
	int		iDeadCount;	//	���񂾎��ɓ_�ł����ď����ׂ̃J�E���^

	static const int PLAYER_HP_MAX;	//	EASY��2000	NORMAL��750	HARD��100
	static const float PL_HEIGHT;

public:
	//	�R���X�g���N�^
	CPlayer();
	
public:
	void Initialize(); 

	//	�v���C���[�̊�{����
	void Control();

	//	���˂̐���
	//	����1�F�ˌ���1��1���̊Ԋu�A2�F�A�ˌ�̔����A3�F�A�ː��A4�F������
	void ShotControl();	
		
	//	�v���C���[X�����E�ړ�
	//	1�F�ړ����x�A2�F�_�b�V�����邩�̃t���O(����Ȃ���false = �ʏ�ړ� )
	void MoveX( float _speed, bool _dashF = false );	
	
	//	�W�����v����
	void Jump();
	
	
};


#endif