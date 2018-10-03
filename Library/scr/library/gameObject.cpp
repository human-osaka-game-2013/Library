/*
	gameObject.cpp
	CGameObject�N���X�̃����o�֐�

*/

#include "gameObject.h"

/*
	�R���X�g���N�^
	@param	CTexture�N���X�I�u�W�F�N�g
	@return	�Ȃ�
*/
CGameObject::CGameObject()	
	: m_posX( 0.f ), m_posY( 0.f ), m_posZ( 0.f ),
	  m_Dir( CH_LEFT ), m_State( STATE_WAIT ), m_HP( 0 ), m_deadFlag( false )
{

}

/*
	�f�X�g���N�^
	@param	�Ȃ�
	@return	�Ȃ�
*/
CGameObject::~CGameObject ()
{
	
}


//--------------------------------------------------------
//	�A�N�Z�b�T
//--------------------------------------------------------
/*
	�������Z�b�g
	@param	�����i�Eor���j
	@return	�Ȃ�
*/
void CGameObject::SetDirection ( CHARADIRECTION _dir )
{
	m_Dir = _dir;
}

/*
	��Ԃ��Z�b�g
	@param	��ԁi�ҋ@�A�U���Ȃǁj
	@return	�Ȃ�
*/
void CGameObject::SetState ( CHARASTATE _state )
{
	m_State = _state;
}

/*
	���W�iX,Y�j���Z�b�g
	@param	���W���
	@return	�Ȃ�
*/
void CGameObject::SetPosition ( float _x, float _y, float _z )
{
	m_posX = _x;
	m_posY = _y;
	m_posZ = _z;
}

/*
	���W�iX�j���Z�b�g
	@param	���W���
	@return	�Ȃ�
*/
void CGameObject::SetPositionX ( float _x )
{
	m_posX = _x;
}

/*
	���W�iY�j���Z�b�g
	@param	���W���
	@return	�Ȃ�
*/
void CGameObject::SetPositionY ( float _y )
{
	m_posY = _y;
}

/*
	���W�iZ�j���Z�b�g
	@param	���W���
	@return	�Ȃ�
*/
void CGameObject::SetPositionZ ( float _z )
{
	m_posZ = _z;
}

/*
	�����̎擾
	@param	�Ȃ�
	@return	�����i�Eor���j
*/
CGameObject::CHARADIRECTION CGameObject::GetDirection ()
{
	return m_Dir;
}

/*
	��Ԃ̎擾
	@param	�Ȃ�
	@return	��ԁi�ҋ@�A�U���Ȃǁj
*/
CGameObject::CHARASTATE CGameObject::GetState ()
{
	return m_State;
}

/*
	���W���iX,Y�j�̎擾
	@param	���WX,���WY
	@return	�Ȃ�
*/
void CGameObject::GetPosition ( float* p_x, float* p_y )
{
	*p_x = m_posX;
	*p_y = m_posY;
}

/*
	���W���iX�j�̎擾
	@param	�Ȃ�
	@return	���W���iX�j
*/
float CGameObject::GetPositionX ()
{
	return m_posX;
}

/*
	���W���iY�j�̎擾
	@param	�Ȃ�
	@return	���W���iY�j
*/
float CGameObject::GetPositionY ()
{
	return m_posY;
}

/*
	���W���iZ�j�̎擾
	@param	�Ȃ�
	@return	���W���iZ�j
*/
float CGameObject::GetPositionZ ()
{
	return m_posZ;
}

/*
	�����蔻��
	@param	��,��,�E,��
	@return	���ʁF���������itrue�j,�������ĂȂ��ifalse�j
*/
bool CGameObject::HitCheck( float _left, float _top, float _right, float _bottom )	
{
	if( _left < m_posX && _right > m_posX )
	{
		if( _top > m_posY && _bottom < m_posY )
		{
			return true;
		}
	}
	return false;
}

/*
	���ʔԍ����Z�b�g
	@param	ID�iint�^�j
	@return	�Ȃ�
*/
void CGameObject::SetID( int _id )
{
	m_id = _id;
}

/*
	���ʔԍ����擾
	@param	�Ȃ�
	@return	���ʔԍ��iint�^�j
*/
int CGameObject::GetID()	
{
	return m_id;
}


/*
	���ʔԍ����Z�b�g
	@param	ID�ibool�^�j
	@return	�Ȃ�
*/
void CGameObject::SetDeadFlag( bool _dFlag )
{
	m_deadFlag = _dFlag;
}

/*
	���ʔԍ����擾
	@param	�Ȃ�
	@return	���ʔԍ��ibool�^�j
*/
bool CGameObject::GetDeadFlag()	
{
	return m_deadFlag;
}