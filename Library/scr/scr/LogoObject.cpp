#include"LogoObject.h"
#include"../library/Texture.h"
#include"../library/DrawFunc.h"

CLogoObject::CLogoObject() : CGameObject()
{

}

//	�ړ�(�I�u�W�F�N�g����)�̊֐�
void CLogoObject::Move()
{

}

//	�`��̊֐�
void CLogoObject::Draw()
{
	VertexDraw( GetID(), GetPositionX(), GetPositionY(),800.f, 400.f,
		0.f, 0.f, 1.f, 1.f );
}