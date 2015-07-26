
#ifndef _BATTLEOBJECT_H_
#define _BATTLEOBJECT_H_
#include "../library/RenderManage.h"
#include "../library/gameObject.h"

//---------------------------------------------------------------------------------------------
//	基本的なゲームオブジェクトのクラス
//---------------------------------------------------------------------------------------------
class CBattleObject : public CGameObject
{
private:
	float m_AnimTime;
	float m_AnimTimeHold;
	int   m_DrawType;

public:
	enum DRAW_TYPE
	{
		TYPE_2D,
		TYPE_3D,
		TYPE_ANIM,
		DRAW_TYPE_MAX
	};

	//	回転度、拡縮率
	D3DXVECTOR3 m_vecRot, m_vecScall;
	D3DXVECTOR3 vecBeforePos;	//前フレーム時の地点

public:
	//	コンストラクタ
	CBattleObject();

public:
	//描画の種類の数値を取得
	int GetDrawType();
	//描画の種類の数値を設定
	void SetDrawType( int _type );

	float GetVectorLength( D3DXVECTOR3 _v );

public:
	//	移動(オブジェクト制御)の関数
	void Move();

	//	描画の関数
	void Draw(){};
	//	描画の関数
	void Draw( CRenderManager* pRndMg );
};

//---------------------------------------------------------------------------------------------
//	障害物のクラス
//---------------------------------------------------------------------------------------------
class CBarrier : public CBattleObject
{
public:
	CBarrier();
};

#endif