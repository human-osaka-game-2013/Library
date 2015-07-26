#include"LogoObject.h"
#include"../library/Texture.h"
#include"../library/DrawFunc.h"

CLogoObject::CLogoObject() : CGameObject()
{

}

//	移動(オブジェクト制御)の関数
void CLogoObject::Move()
{

}

//	描画の関数
void CLogoObject::Draw()
{
	VertexDraw( GetID(), GetPositionX(), GetPositionY(),800.f, 400.f,
		0.f, 0.f, 1.f, 1.f );
}