/**
*@file	gameObject.h
*@author	�T�c
*/
//	���d�C���N���[�h�h�~
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

/**
*@brief	�Q�[���I�u�W�F�N�g�N���X
*@details	�Q�[�����Ŏg���I�u�W�F�N�g��
*/
class CGameObject
{
public:	
	//	enum
	//	�I�u�W�F�N�g�̌���
	enum CHARADIRECTION {
		CH_NONE = -1,
		CH_LEFT,
		CH_RIGHT,
		CH_FRONT,
		CH_BACK,
		CH_DIRECTION_MAX,
		
	};

	//	�I�u�W�F�N�g�̏��
	enum CHARASTATE {
		STATE_NONE = -1,
		STATE_WAIT,		
		STATE_WALK,
		STATE_JUMP,	
		STATE_DOWN,
		STATE_DAMAGE,	
		STATE_ATTACK,
		CH_STATE_MAX,
	};

private:	//	�����o�ϐ�
	CHARADIRECTION	m_Dir;		//	����
	CHARASTATE		m_State;	//	���

	float m_posX;		//	X���W
	float m_posY;		//	Y���W
	float m_posZ;		//	Z���W

	int	m_id;		//	���ʔԍ��i�I�u�W�F�N�g�ŗL��ID)

	bool m_deadFlag;	//	�\���ȂǃI�u�W�F�N�g�����ݏo���邩�̔��f�Ɏg��

public:
	//	�R���X�g���N�^
	CGameObject ();	//	�iin�j�I�u�W�F�N�g��id
	//	�f�X�g���N�^
	~CGameObject ();

public:	
	//	�ړ��̉��z�֐�
	virtual void Control () = 0;

	//	�`��̉��z�֐�
	virtual void Draw() = 0;
	
	bool HitCheck( float _left, float _top, float _right, float _bottom );

public:	// �A�N�Z�b�T
	void SetDirection ( CHARADIRECTION _dir );
	void SetState ( CHARASTATE _state );
	void SetPosition ( float _x, float _y, float _z );
	void SetPositionX ( float _x );
	void SetPositionY ( float _y );
	void SetPositionZ ( float _z );
	void SetID( int _id );
	void SetDeadFlag( bool _dFlag );

	CHARADIRECTION GetDirection ();
	CHARASTATE GetState ();
	void GetPosition ( float* p_x, float* p_y );
	float GetPositionX ();
	float GetPositionY ();
	float GetPositionZ ();
	int GetID();
	bool GetDeadFlag();
};

#endif