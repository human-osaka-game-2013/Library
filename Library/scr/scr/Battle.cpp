#include "../library/AllInput.h"
#include "Battle.h"
#include "../library/Texture.h"

const float CBattle::WALK_SPEED = 1.f;
const float CBattle::GROUND_Y_LOW = -60.f;
const float CBattle::STAGE_Z = 90.f;
const float CBattle::STAGE_X = 120.f;
const float CBattle::STAGE_Y = 50.f;
const D3DXVECTOR3 BG_POS( -1.2f, 0.026f, -99.04f );

//	コンストラクタ
CBattle::CBattle( int _id ) : CScene( _id )
{
	pSelect = new CSelect( this );
	pResult = new CResult( this );
}

//	デストラクタ
CBattle::~CBattle()
{
	SAFE_DELETE(pSelect);
	SAFE_DELETE(pResult);
}

//	初期化
bool CBattle::Init()
{
	for( int i = 0; i < PLAYER_MAX; i++ )
	{
		playerObj[ i ].Initialize();
	}

	playerObj[ PLAYER1 ].SetID( PLAYER1 );
	playerObj[ PLAYER1 ].SetDrawType( CBattleObject::TYPE_ANIM );
	playerObj[ PLAYER1 ].SetPosition( -STAGE_X, GROUND_Y_LOW, STAGE_Z );

	playerObj[ PLAYER2 ].SetID( PLAYER2 );
	playerObj[ PLAYER2 ].SetDrawType( CBattleObject::TYPE_ANIM );
	playerObj[ PLAYER2 ].SetPosition( STAGE_X, GROUND_Y_LOW, STAGE_Z );

	playerObj[ PLAYER3 ].SetID( PLAYER3 );
	playerObj[ PLAYER3 ].SetDrawType( CBattleObject::TYPE_ANIM );
	playerObj[ PLAYER3 ].SetPosition( STAGE_X-STAGE_X, GROUND_Y_LOW, STAGE_Z );

	battleObj[ BACKGROUND ].SetID( CRenderManager::TH_BG1 );
	battleObj[ BACKGROUND ].SetDrawType( CBattleObject::TYPE_2D );	
	battleObj[ BACKGROUND ].SetPosition(BG_POS.x, BG_POS.y, BG_POS.z);

	barrierObj[0].SetID( CRenderManager::TH_BOX_1 );
	barrierObj[0].SetDrawType( CBattleObject::TYPE_3D );	
	barrierObj[0].SetPosition( 0, GROUND_Y_LOW-1, STAGE_Z );
	barrierObj[1].SetID( CRenderManager::TH_BOX_1 );
	barrierObj[1].SetDrawType( CBattleObject::TYPE_3D );	
	barrierObj[1].SetPosition( -STAGE_X, GROUND_Y_LOW, STAGE_Z );
	barrierObj[2].SetID( CRenderManager::TH_BOX_1 );
	barrierObj[2].SetDrawType( CBattleObject::TYPE_3D );	
	barrierObj[2].SetPosition( -STAGE_X, GROUND_Y_LOW, STAGE_Z );
	barrierObj[3].SetID( CRenderManager::TH_BOX_1 );
	barrierObj[3].SetDrawType( CBattleObject::TYPE_3D );	
	barrierObj[3].SetPosition( -STAGE_X, GROUND_Y_LOW, STAGE_Z );
	barrierObj[4].SetID( CRenderManager::TH_BOX_1 );
	barrierObj[4].SetDrawType( CBattleObject::TYPE_3D );	
	barrierObj[4].SetPosition( -STAGE_X, GROUND_Y_LOW, STAGE_Z );
	barrierObj[5].SetID( CRenderManager::TH_BOX_1 );
	barrierObj[5].SetDrawType( CBattleObject::TYPE_3D );	
	barrierObj[5].SetPosition( -STAGE_X, GROUND_Y_LOW, STAGE_Z );

	return true;
}

//	処理
int	 CBattle::Control()
{
	//	プレイヤーのアニメーション状態をマイフレーム待機状態に一旦戻す
	playerObj[ PLAYER1 ].SetState( CGameObject::STATE_WAIT );  
	playerObj[ PLAYER1 ].SetDirection( CGameObject::CH_DIRECTION_MAX );

	playerObj[ PLAYER2 ].SetState( CGameObject::STATE_WAIT );  
	playerObj[ PLAYER2 ].SetDirection( CGameObject::CH_DIRECTION_MAX );

	playerObj[ PLAYER3 ].SetState( CGameObject::STATE_WAIT );  
	playerObj[ PLAYER3 ].SetDirection( CGameObject::CH_DIRECTION_MAX );

	barrierObj[ 0 ].SetState( CGameObject::STATE_WAIT );  
	barrierObj[ 0 ].SetDirection( CGameObject::CH_DIRECTION_MAX );


//	プレイヤー1
	/*
		Xboxコントローラーの入力に応じて
		各プレイヤーの移動とアニメーションの切り替え
	*/
	if( CXInput::CheckStickState( 0, CXInput::CROSS_LEFT, CXInput::ON ) || StCheck( LEFT, ON ) )
	{
		playerObj[ PLAYER1 ].SetDirection( CGameObject::CH_LEFT );
		playerObj[ PLAYER1 ].SetState( CGameObject::STATE_WALK );

		playerObj[ PLAYER1 ].MoveX( -WALK_SPEED );
		//for( int i = 0; i < BLOCK_MAX; i++ )
		//{
		//	if ( playerObj[ PLAYER1 ].HitCheck( barrierObj[i].GetPositionX()-BLOCK_W,
		//										barrierObj[i].GetPositionY()+BLOCK_H,
		//										barrierObj[i].GetPositionX()+BLOCK_W,
		//										barrierObj[i].GetPositionY()) )
		//	{
		//		playerObj[ PLAYER1 ].SetPositionX( playerObj[ PLAYER1 ].GetPositionX()+WALK_SPEED );
		//		break;
		//	}
		//}
	}
	if( CXInput::CheckStickState( 0, CXInput::CROSS_RIGHT, CXInput::ON ) || StCheck( RIGHT, ON ) )
	{
		playerObj[ PLAYER1 ].SetDirection( CGameObject::CH_RIGHT );
		playerObj[ PLAYER1 ].SetState( CGameObject::STATE_WALK );
		
		playerObj[ PLAYER1 ].MoveX( WALK_SPEED );
		//for( int i = 0; i < BLOCK_MAX; i++ )
		//{
		//	if ( true == playerObj[ PLAYER1 ].HitCheck( barrierObj[i].GetPositionX()-BLOCK_W,
		//										barrierObj[i].GetPositionY()+BLOCK_H,
		//										barrierObj[i].GetPositionX()+BLOCK_W,
		//										barrierObj[i].GetPositionY()) )
		//	{
		//		playerObj[ PLAYER1 ].SetPositionX( playerObj[ PLAYER1 ].GetPositionX()-WALK_SPEED );
		//		break;
		//	}
		//}
	}
	/*
		ジャンプ及びしゃがみは素材が無いため仮で待機状態をセット
	*/
	if( CXInput::CheckStickState( 0, CXInput::BUTTON_A, CXInput::ON ) || StCheck( UP, PUSH ) )
	{
		playerObj[ PLAYER1 ].SetState( CGameObject::STATE_JUMP );

	}
	if( CXInput::CheckStickState( 0, CXInput::CROSS_DOWN, CXInput::ON ) || StCheck( DOWN, ON ) )
	{
		playerObj[ PLAYER1 ].SetState( CGameObject::STATE_DOWN );
	}
	

//	仮
//	プレイヤー2
	if( CXInput::CheckStickState( 1, CXInput::CROSS_LEFT, CXInput::ON ) || StCheck( LEFT, ON ) )
	{
		playerObj[ PLAYER2 ].SetDirection( CGameObject::CH_LEFT );
		playerObj[ PLAYER2 ].SetState( CGameObject::STATE_WALK );

		playerObj[ PLAYER2 ].MoveX( -WALK_SPEED );
		//for( int i = 0; i < BLOCK_MAX; i++ )
		//{
		//	if ( playerObj[ PLAYER1 ].HitCheck( barrierObj[i].GetPositionX()-BLOCK_W,
		//										barrierObj[i].GetPositionY()+BLOCK_H,
		//										barrierObj[i].GetPositionX()+BLOCK_W,
		//										barrierObj[i].GetPositionY()) )
		//	{
		//		playerObj[ PLAYER1 ].SetPositionX( playerObj[ PLAYER1 ].GetPositionX()+WALK_SPEED );
		//		break;
		//	}
		//}
	}
	if( CXInput::CheckStickState( 1, CXInput::CROSS_RIGHT, CXInput::ON ) || StCheck( RIGHT, ON ) )
	{
		playerObj[ PLAYER2 ].SetDirection( CGameObject::CH_RIGHT );
		playerObj[ PLAYER2 ].SetState( CGameObject::STATE_WALK );
		
		playerObj[ PLAYER2 ].MoveX( WALK_SPEED );
		//for( int i = 0; i < BLOCK_MAX; i++ )
		//{
		//	if ( true == playerObj[ PLAYER1 ].HitCheck( barrierObj[i].GetPositionX()-BLOCK_W,
		//										barrierObj[i].GetPositionY()+BLOCK_H,
		//										barrierObj[i].GetPositionX()+BLOCK_W,
		//										barrierObj[i].GetPositionY()) )
		//	{
		//		playerObj[ PLAYER1 ].SetPositionX( playerObj[ PLAYER1 ].GetPositionX()-WALK_SPEED );
		//		break;
		//	}
		//}
	}
	if( CXInput::CheckStickState( 1, CXInput::BUTTON_A, CXInput::ON ) || StCheck( UP, PUSH ) )
	{
		playerObj[ PLAYER2 ].SetState( CGameObject::STATE_JUMP );
		
	}
	if( CXInput::CheckStickState( 1, CXInput::CROSS_DOWN, CXInput::ON ) || StCheck( DOWN, ON ) )
	{
		playerObj[ PLAYER2 ].SetState( CGameObject::STATE_DOWN );
	}

//	仮
//	プレイヤー3
	if( CXInput::CheckStickState( 2, CXInput::CROSS_LEFT, CXInput::ON ) || StCheck( LEFT, ON ) )
	{
		playerObj[ PLAYER3 ].SetDirection( CGameObject::CH_LEFT );
		playerObj[ PLAYER3 ].SetState( CGameObject::STATE_WALK );

		playerObj[ PLAYER3 ].MoveX( -WALK_SPEED );
		//for( int i = 0; i < BLOCK_MAX; i++ )
		//{
		//	if ( playerObj[ PLAYER1 ].HitCheck( barrierObj[i].GetPositionX()-BLOCK_W,
		//										barrierObj[i].GetPositionY()+BLOCK_H,
		//										barrierObj[i].GetPositionX()+BLOCK_W,
		//										barrierObj[i].GetPositionY()) )
		//	{
		//		playerObj[ PLAYER1 ].SetPositionX( playerObj[ PLAYER1 ].GetPositionX()+WALK_SPEED );
		//		break;
		//	}
		//}
	}
	if( CXInput::CheckStickState( 2, CXInput::CROSS_RIGHT, CXInput::ON ) || StCheck( RIGHT, ON ) )
	{
		playerObj[ PLAYER3 ].SetDirection( CGameObject::CH_RIGHT );
		playerObj[ PLAYER3 ].SetState( CGameObject::STATE_WALK );
		
		playerObj[ PLAYER3 ].MoveX( WALK_SPEED );
		//for( int i = 0; i < BLOCK_MAX; i++ )
		//{
		//	if ( true == playerObj[ PLAYER1 ].HitCheck( barrierObj[i].GetPositionX()-BLOCK_W,
		//										barrierObj[i].GetPositionY()+BLOCK_H,
		//										barrierObj[i].GetPositionX()+BLOCK_W,
		//										barrierObj[i].GetPositionY()) )
		//	{
		//		playerObj[ PLAYER1 ].SetPositionX( playerObj[ PLAYER1 ].GetPositionX()-WALK_SPEED );
		//		break;
		//	}
		//}
	}
	if( CXInput::CheckStickState( 2, CXInput::BUTTON_A, CXInput::ON ) || StCheck( UP, PUSH ) )
	{
		playerObj[ PLAYER3 ].SetState( CGameObject::STATE_JUMP );

	}
	if( CXInput::CheckStickState( 2, CXInput::CROSS_DOWN, CXInput::ON ) || StCheck( DOWN, ON ) )
	{
		playerObj[ PLAYER3 ].SetState( CGameObject::STATE_DOWN );
	}


	return 0;
}

//	2D描画
void CBattle::Draw()
{

}

//	3D描画
void CBattle::Render( CRenderManager* pRndMg )
{
	pRndMg -> MousePosTransform();

	for( int i = 0; i < OBJ_MAX; i++ )
	{
		battleObj[ i ].Draw( pRndMg );
	}
	for( int i = 0; i < BLOCK_MAX; i++ )
	{
		barrierObj[ i ].Draw( pRndMg );
	}
	for( int i = 0; i < PLAYER_MAX; i++ )
	{
		playerObj[ i ].Draw( pRndMg );
	}
	
}