#include "Battle.h"
#include "../library/AllInput.h"

const int CPlayer::PLAYER_HP_MAX = 100;	//	EASY→2000	NORMAL→750	HARD→100
const float CPlayer::PL_HEIGHT = 20.f;

/*
	コンストラクタ
*/
CPlayer::CPlayer() : CBattleObject(), m_vecImpact( 0.f, 0.f, 0.f ), m_AttackFlag( false ),
	bJumpFlag( false ), bDownFlag( false ), bLandFlag( false ), y_prev( 0.f ), y_temp( 0.f ),
	iHitCount(0), iDeadCount(0)
{
	
}

/*
	プレイヤーの初期化
*/
void CPlayer::Initialize()
{
	SetHP( PLAYER_HP_MAX );
	y_prev = GetPositionY();
	SetDeadFlag( false );

	m_AttackFlag = false;
	bJumpFlag = false;
	bDownFlag = false;
	bLandFlag = false;
	m_vecImpact.x = GetPositionX();
	m_vecImpact.y = GetPositionY() + PL_HEIGHT/2;
	m_vecImpact.z = GetPositionZ();
	
}

/*
	プレイヤーの基本処理
*/
void CPlayer::Control()
{
	/*if( bJumpFlag || !bLandFlag )
	{
		Jump ();

		for( int i = 0; i < CBattle::BLOCK_MAX-CBattle::BLOCK; i++ ){
			if( HitCheck( barrierObj[i]. ) ) 
			{
				if( this->vecPosition.y > block[i].vecPosition.y ) {
					vecPosition.y = block[i].vecPosition.y + block[i].BBox.vecMax.y +0.05f;  
					bJumpFlag = false;
					bLandFlag = true;
					break;
				}
				else {
					vecPosition.y = block[i].vecPosition.y - this ->BBox.vecMax.y;
					y_prev = vecPosition.y;
					break;
				}
			}
		}
		

		if( vecPosition.y <= object[SKY].vecPosition.y ) {
			vecPosition.y = object[SKY].vecPosition.y +0.05f;
			bJumpFlag = false;
			bLandFlag = true;
		}
	}
	else
	{
		int iCount = 0;
		while( iCount == -1 || iCount < BLOCK_MAX )
		{
			if( BoxImpact( &block[iCount], this, 1 ) ) {
				iCount = -1;
			}
			else {
				iCount++;
			}
		}
		if( iCount != -1 ){
			bLandFlag = false;
			y_prev = vecPosition.y;
		}
	}*/
}



/*
	プレイヤーX軸左右移動
	1：移動速度、2：ダッシュするかのフラグ(入れないとfalse = 通常移動 )
*/
void CPlayer::MoveX( float _speed, bool _dashF )
{
	SetPositionX( GetPositionX() + _speed );
	m_vecImpact.x = -1.0f;
	if ( !HitCheck( -CBattle::STAGE_X, CBattle::STAGE_Y, CBattle::STAGE_X, CBattle::GROUND_Y_LOW-0.5f ) )
	{
		SetPositionX( GetPositionX() - _speed );
	}
	
}

/*
	ジャンプ処理
*/
void CPlayer::Jump()
{
	if ( bJumpFlag )
	{
		y_temp = GetPositionY();
		SetPositionY( GetPositionY() +( GetPositionY() - y_prev ) - 0.05f);
		y_prev = y_temp;	
	}
}
