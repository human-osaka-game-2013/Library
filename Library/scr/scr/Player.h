#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "BattleObject.h"

//---------------------------------------------------------------------------------------------
//	プレイヤーのクラス
//---------------------------------------------------------------------------------------------
class CPlayer : public CBattleObject
{
public:
	D3DXVECTOR3	m_vecImpact;	//	発射ベクトルx,y,z
	bool		m_AttackFlag;	//	発射フラグ

	bool	bJumpFlag;
	bool	bDownFlag;
	bool	bLandFlag;
	float	y_prev,	y_temp;	//	ジャンプ時の位置保存用
	//---------------------------------------------
	int		iHitCount;	//	当たった時に点滅させる為のカウンタ
	int		iDeadCount;	//	死んだ時に点滅させて消す為のカウンタ

	static const int PLAYER_HP_MAX;	//	EASY→2000	NORMAL→750	HARD→100
	static const float PL_HEIGHT;

public:
	//	コンストラクタ
	CPlayer();
	
public:
	void Initialize(); 

	//	プレイヤーの基本処理
	void Control();

	//	発射の制御
	//	引数1：射撃時1発1発の間隔、2：連射後の反動、3：連射数、4：武器種類
	void ShotControl();	
		
	//	プレイヤーX軸左右移動
	//	1：移動速度、2：ダッシュするかのフラグ(入れないとfalse = 通常移動 )
	void MoveX( float _speed, bool _dashF = false );	
	
	//	ジャンプ処理
	void Jump();
	
	
};


#endif