
#include "Battle.h"

//	�R���X�g���N�^
CBattle::CSelect::CSelect( CBattle* _pBattle ) : pBattle( _pBattle )
{
	
}

//	������
bool CBattle::CSelect::Init()
{

	return true;
}

//	����
int	 CBattle::CSelect::Control()
{

	return 1;
}

//	2D�`��
void CBattle::CSelect::Draw()
{

}

//	3D�`��
void CBattle::CSelect::Render( CRenderManager* pRndMg )
{

}