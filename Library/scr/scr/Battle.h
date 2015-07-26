
#ifndef _BATTLE_H_
#define _BATTLE_H_
#include "../library/Scene.h"
#include "Player.h"

#define	ONE_FR	60.f

class CBattle : public CScene
{
public:
	enum OBJECT_ID {
		
		PLAYER1,
		PLAYER2,
		PLAYER3,

		PLAYER_MAX,

		BACKGROUND = 0,
		OBJ_MAX,

		BLOCK = 0,
		BLOCK_MAX = BLOCK + 6,
		

		BATTLE_MAX
	};


	enum BATTLE_SCENE
	{
		CHARA_SELECT,

		BATTLE,

		RESULT
	};

	static const float WALK_SPEED;		//	(仮)移動スピード
	static const float GROUND_Y_LOW;	//	ステージの地面位置Y
	static const float STAGE_Z;			//	ステージのZ軸方向の基準座標
	static const float STAGE_X;			//	ステージのX軸方向の最大値
	static const float STAGE_Y;			//	ステージのY軸方向の最大値
#define BLOCK_W 20.f
#define BLOCK_H 5.f

	/*
		キャラセレクトクラス
	*/
	class CSelect
	{
	private:
		CBattle* pBattle;	//	CBattleのポインタ

	public:
		//	コンストラクタ
		CSelect( CBattle* _pBattle );
	
	public:
		//	初期化
		bool Init();	
		//	処理
		int	 Control();	
		//	2D描画
		void Draw();	
		//	3D描画
		void Render( CRenderManager* pRndMg );	
	};

	/*
		バトルリザルトクラス
	*/
	class CResult
	{
	private:
		CBattle* pBattle;	//	CBattleのポインタ

	public:
		//	コンストラクタ
		CResult( CBattle* _pBattle );
	
	public:
		//	初期化
		bool Init();	
		//	処理
		int	 Control();	
		//	2D描画
		void Draw();	
		//	3D描画
		void Render( CRenderManager* pRndMg );	
	};

private:
	CBattleObject battleObj[OBJ_MAX];
	CPlayer playerObj[PLAYER_MAX];
	CBarrier barrierObj[BLOCK_MAX];
	
	CSelect*	pSelect;	//	キャラセレクトクラスのポインタ
	CResult*	pResult;	//	リザルトクラスのポインタ



public:
	//	コンストラクタ
	CBattle( int _id );

	//	デストラクタ
	~CBattle();

public:
	//	初期化
	bool Init();	
	//	処理
	int	 Control();	
	//	2D描画
	void Draw();	
	//	3D描画
	void Render( CRenderManager* pRndMg );	
};


#endif