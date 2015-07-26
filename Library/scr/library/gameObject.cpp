/*
	gameObject.cpp
	CGameObjectクラスのメンバ関数

*/

#include "gameObject.h"

/*
	コンストラクタ
	@param	CTextureクラスオブジェクト
	@return	なし
*/
CGameObject::CGameObject()	
	: m_posX( 0.f ), m_posY( 0.f ), m_posZ( 0.f ),
	  m_Dir( CH_LEFT ), m_State( STATE_WAIT ), m_HP( 0 ), m_deadFlag( false )
{

}

/*
	デストラクタ
	@param	なし
	@return	なし
*/
CGameObject::~CGameObject ()
{
	
}


//--------------------------------------------------------
//	アクセッサ
//--------------------------------------------------------
/*
	向きをセット
	@param	向き（右or左）
	@return	なし
*/
void CGameObject::SetDirection ( CHARADIRECTION _dir )
{
	m_Dir = _dir;
}

/*
	状態をセット
	@param	状態（待機、攻撃など）
	@return	なし
*/
void CGameObject::SetState ( CHARASTATE _state )
{
	m_State = _state;
}

/*
	座標（X,Y）をセット
	@param	座標情報
	@return	なし
*/
void CGameObject::SetPosition ( float _x, float _y, float _z )
{
	m_posX = _x;
	m_posY = _y;
	m_posZ = _z;
}

/*
	座標（X）をセット
	@param	座標情報
	@return	なし
*/
void CGameObject::SetPositionX ( float _x )
{
	m_posX = _x;
}

/*
	座標（Y）をセット
	@param	座標情報
	@return	なし
*/
void CGameObject::SetPositionY ( float _y )
{
	m_posY = _y;
}

/*
	座標（Z）をセット
	@param	座標情報
	@return	なし
*/
void CGameObject::SetPositionZ ( float _z )
{
	m_posZ = _z;
}

/*
	向きの取得
	@param	なし
	@return	向き（右or左）
*/
CGameObject::CHARADIRECTION CGameObject::GetDirection ()
{
	return m_Dir;
}

/*
	状態の取得
	@param	なし
	@return	状態（待機、攻撃など）
*/
CGameObject::CHARASTATE CGameObject::GetState ()
{
	return m_State;
}

/*
	座標情報（X,Y）の取得
	@param	座標X,座標Y
	@return	なし
*/
void CGameObject::GetPosition ( float* p_x, float* p_y )
{
	*p_x = m_posX;
	*p_y = m_posY;
}

/*
	座標情報（X）の取得
	@param	なし
	@return	座標情報（X）
*/
float CGameObject::GetPositionX ()
{
	return m_posX;
}

/*
	座標情報（Y）の取得
	@param	なし
	@return	座標情報（Y）
*/
float CGameObject::GetPositionY ()
{
	return m_posY;
}

/*
	座標情報（Z）の取得
	@param	なし
	@return	座標情報（Z）
*/
float CGameObject::GetPositionZ ()
{
	return m_posZ;
}

/*
	当たり判定
	@param	左,上,右,下
	@return	結果：当たった（true）,当たってない（false）
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
	識別番号をセット
	@param	ID（int型）
	@return	なし
*/
void CGameObject::SetID( int _id )
{
	m_id = _id;
}

/*
	識別番号を取得
	@param	なし
	@return	識別番号（int型）
*/
int CGameObject::GetID()	
{
	return m_id;
}


/*
	識別番号をセット
	@param	ID（bool型）
	@return	なし
*/
void CGameObject::SetDeadFlag( bool _dFlag )
{
	m_deadFlag = _dFlag;
}

/*
	識別番号を取得
	@param	なし
	@return	識別番号（bool型）
*/
bool CGameObject::GetDeadFlag()	
{
	return m_deadFlag;
}