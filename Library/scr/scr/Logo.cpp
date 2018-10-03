
#include "../library/AllInput.h"
#include "Logo.h"
#include "../library/Texture.h"

//	�R���X�g���N�^
CLogo::CLogo( int _id ) : CScene( _id )
{
	m_count = 0;
}

//	������
bool CLogo::Init()
{
	logo.SetID( TEX_TEAM_LOGO );
	return true;
}

//	����
int	 CLogo::Control()
{
	logo.Move();

	if( StCheck( ENTER, PUSH ) )
	{

	}
	//	�V�[���ύX�̍X�V
	return GetSceneID();
}

//	2D�`��
void CLogo::Draw()
{
	logo.Draw();
}
