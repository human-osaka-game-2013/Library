/**
*@file	gameObject.h
*@author	亀田
*/
//	多重インクルード防止
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

/**
*@brief	ゲームオブジェクトクラス
*@details	ゲーム内で使うオブジェクトの
*/
class CGameObject
{
public:	
	//	enum
	//	オブジェクトの向き
	enum CHARADIRECTION {
		CH_NONE = -1,
		CH_LEFT,
		CH_RIGHT,
		CH_FRONT,
		CH_BACK,
		CH_DIRECTION_MAX,
		
	};

	//	オブジェクトの状態
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

private:	//	メンバ変数
	CHARADIRECTION	m_Dir;		//	向き
	CHARASTATE		m_State;	//	状態

	float m_posX;		//	X座標
	float m_posY;		//	Y座標
	float m_posZ;		//	Z座標

	int	m_id;		//	識別番号（オブジェクト固有のID)

	bool m_deadFlag;	//	表示などオブジェクトが存在出来るかの判断に使う

public:
	//	コンストラクタ
	CGameObject ();	//	（in）オブジェクトのid
	//	デストラクタ
	~CGameObject ();

public:	
	//	移動の仮想関数
	virtual void Control () = 0;

	//	描画の仮想関数
	virtual void Draw() = 0;
	
	bool HitCheck( float _left, float _top, float _right, float _bottom );

public:	// アクセッサ
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