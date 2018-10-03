#include "SceneManage.h"
#include "graphic.h"

//---------------------------------------------------
//	�v���g�^�C�v�錾
//---------------------------------------------------
// 3D�`��O����
void BeginRender ( HRESULT* hr );

// �`��O����
void BeginDraw ( HRESULT* hr );

// �`��㏈��
void EndRender ();

//----------------------------------------------------

//	�`��̊Ǘ�
//	�����F3D���f������������true��
HRESULT CSceneManager::ViewManage ( bool b3dView )
{
	HRESULT hr;
	
	if ( b3dView == true )
	{
		RenderManage( &hr );
	}
	DrawManage( &hr );

	return hr;
}

//	�����_�����O�Ǘ�
void CSceneManager::RenderManage ( HRESULT* hr )
{
	BeginRender( hr );

	m_sceneObj -> Render( GetRndManager() );

	EndRender();
}

//	�`��Ǘ�
void CSceneManager::DrawManage ( HRESULT* hr )
{
	BeginDraw( hr );

	m_sceneObj -> Draw();

	EndRender();
}
