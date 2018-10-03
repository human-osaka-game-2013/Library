
#include "../library/RenderManage.h"
#include "BattleObject.h"

/*
	�R���X�g���N�^
*/
CBattleObject::CBattleObject() : CGameObject(), m_AnimTime( 0.f ), m_AnimTimeHold( 0.f ), m_DrawType( TYPE_2D ),
	m_vecRot( 0.f, 0.f, 0.f ), m_vecScall( 1.f, 1.f, 1.f ), vecBeforePos( 0.f, 0.f, 0.f )
{
	 
}

/*
	�R���X�g���N�^
*/
CBarrier::CBarrier() : CBattleObject()
{

}

/*
	�ړ�(�I�u�W�F�N�g����)�̊֐�
*/
void CBattleObject::Move()
{
	
}

/*
	�`��̊֐�
*/
void CBattleObject::Draw( CRenderManager* pRndMg )
{
	int _dType = GetDrawType();

	D3DXVECTOR3 pos( GetPositionX(), GetPositionY(), GetPositionZ() );
	
	//	�`��^�C�v��3D���f�����g���Ȃ�
	if( _dType >= TYPE_3D )
	{
		D3DXVECTOR3 rot;

		if( GetDirection() != CH_DIRECTION_MAX )
			rot = GetDirection() ? pRndMg -> RIGHT_ROT : pRndMg -> LEFT_ROT;
		else{
			rot = pRndMg -> CENTER_ROT;
		}
		D3DXVECTOR3 scl( 10.f, 10.f, 10.f );
		
		//	�`��^�C�v��3D�A�j���[�V�����t�����f�����g���Ȃ�
		if( _dType >= TYPE_ANIM )
		{
			D3DXVECTOR3 scl( 0.1f, 0.1f, 0.1f );

			LPD3DXANIMATIONCONTROLLER pAnimControl = pRndMg -> AllocateHierarchy[ GetState()].GetAnimCtrl();
			
			//	�A�j���[�V�����R���g���[���[���擾�ł�����
			if( pAnimControl )
			{
				pAnimControl -> AdvanceTime( m_AnimTime-m_AnimTimeHold,NULL );
				m_AnimTimeHold=m_AnimTime;
			}

			pRndMg -> AnimationTransform( GetState(), pos, rot, scl );

			if( GetState() == STATE_WALK )
				m_AnimTime+=0.05f;

			if( m_AnimTime > 1.0f )
			{
				m_AnimTime=0.0f;
			}
		}
		//	�`��^�C�v��3D���f���i���b�V���f�[�^�̂݁j���g���Ȃ�
		else
		{
			pRndMg -> Transform( GetID() , pos, rot, scl );
		}
	}
	//	�`��^�C�v�����ʂ̒��_�݂̂��g���Ȃ�
	else
	{
		pRndMg -> BillboardingTransform( GetID(), pos );
	}
}

//�`��̎�ނ̐��l���擾
int CBattleObject::GetDrawType()
{
	return m_DrawType;
}

//�`��̎�ނ̐��l��ݒ�
void CBattleObject::SetDrawType( int _type )
{
	m_DrawType = _type;
}