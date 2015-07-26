
#include "../library/RenderManage.h"
#include "BattleObject.h"

/*
	コンストラクタ
*/
CBattleObject::CBattleObject() : CGameObject(), m_AnimTime( 0.f ), m_AnimTimeHold( 0.f ), m_DrawType( TYPE_2D ),
	m_vecRot( 0.f, 0.f, 0.f ), m_vecScall( 1.f, 1.f, 1.f ), vecBeforePos( 0.f, 0.f, 0.f )
{
	 
}

/*
	コンストラクタ
*/
CBarrier::CBarrier() : CBattleObject()
{

}

/*
	移動(オブジェクト制御)の関数
*/
void CBattleObject::Move()
{
	
}

/*
	描画の関数
*/
void CBattleObject::Draw( CRenderManager* pRndMg )
{
	int _dType = GetDrawType();

	D3DXVECTOR3 pos( GetPositionX(), GetPositionY(), GetPositionZ() );
	
	//	描画タイプが3Dモデルを使うなら
	if( _dType >= TYPE_3D )
	{
		D3DXVECTOR3 rot;

		if( GetDirection() != CH_DIRECTION_MAX )
			rot = GetDirection() ? pRndMg -> RIGHT_ROT : pRndMg -> LEFT_ROT;
		else{
			rot = pRndMg -> CENTER_ROT;
		}
		D3DXVECTOR3 scl( 10.f, 10.f, 10.f );
		
		//	描画タイプが3Dアニメーション付きモデルを使うなら
		if( _dType >= TYPE_ANIM )
		{
			D3DXVECTOR3 scl( 0.1f, 0.1f, 0.1f );

			LPD3DXANIMATIONCONTROLLER pAnimControl = pRndMg -> AllocateHierarchy[ GetState()].GetAnimCtrl();
			
			//	アニメーションコントローラーが取得できたら
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
		//	描画タイプが3Dモデル（メッシュデータのみ）を使うなら
		else
		{
			pRndMg -> Transform( GetID() , pos, rot, scl );
		}
	}
	//	描画タイプが平面の頂点のみを使うなら
	else
	{
		pRndMg -> BillboardingTransform( GetID(), pos );
	}
}

//描画の種類の数値を取得
int CBattleObject::GetDrawType()
{
	return m_DrawType;
}

//描画の種類の数値を設定
void CBattleObject::SetDrawType( int _type )
{
	m_DrawType = _type;
}