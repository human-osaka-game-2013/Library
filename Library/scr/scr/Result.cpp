
#include "Battle.h"

//	�R���X�g���N�^
CBattle::CResult::CResult( CBattle* _pBattle ) : pBattle( _pBattle )
{

}

//	������
bool CBattle::CResult::Init()
{

	return true;
}

//	����
int	 CBattle::CResult::Control()
{

	return 1;
}

//	2D�`��
void CBattle::CResult::Draw()
{

}

//	3D�`��
void CBattle::CResult::Render( CRenderManager* pRndMg )
{

}