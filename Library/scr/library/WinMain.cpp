#include "SceneManage.h"
#include "RenderManage.h"
#include "main.h"
#include "Window.h"
#include "AllInput.h"

//----------------------------------------------------------------
//	�v���g�^�C�v�錾
//----------------------------------------------------------------
// Direct3D�̏�����
// ��1�����F�E�C���h�n���h��
HRESULT InitD3d ( HWND );

//	�E�C���h�E����
int CreateWindowProcess ( HINSTANCE, HWND* );

//�_�C���N�g�C���v�b�g�̏������֐�
HRESULT InitDinput( HWND );

//	�}�E�X���W�̎擾�ƈړ��ʂ����߂�B
//	����1�F�E�C���h�E�n���h��
void CursorSet( HWND );

// �g�p���Ă���S�Ẵe�N�X�`���̉��
void ReleaseAllTexture ();

//	�f�o�C�X�̉��
void FreeDx ( bool );

//----------------------------------------------------------------------
//
//	���C�����[�`��
//
//----------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR IpCmdLine, int nCmdShow )
{
	HWND	hWnd;

	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(87);

	MSG msg;
	
	CreateWindowProcess ( hInstance, &hWnd );

	// Direct3D����̏���������
	if ( FAILED ( InitD3d ( hWnd ) ) ) return 0;
	
	//	�L�[�̏�����
	if ( FAILED ( InitDinput ( hWnd ) ) ) return 0;

	// �T�E���h�̏�����
	//InitXAudio2();

	//	�V�[���Ǘ��I�u�W�F�N�g�̐���
	CSceneManager* pSceneManage = new CSceneManager( CSceneManager::BATTLE );

	//	3D�`��̊Ǘ��I�u�W�F�N�g�̐���
	CRenderManager* pRenderManage = pSceneManage -> GetRndManager();

	pRenderManage -> CameraInit();

	//	�g�p����S�Ẳ摜��ǂݍ���
	if ( false == AllLoadTexture () )	return 0;
	//	�g�p����S�Ă�x�t�@�C���ǂݍ���
	if( false ==  pRenderManage -> AllLoadXFile() ) return 0;
	
	srand(( unsigned )time( NULL ));

	DWORD SyncOld = timeGetTime();
	DWORD SyncNow;

	timeBeginPeriod(1);

	ZeroMemory (&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		Sleep(1);

		if ( PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}

		else
		{
			SyncNow = timeGetTime();

			if (SyncNow - SyncOld >= 1000 / 60)
			{
				//	�}�E�X���W���ړ��ʂ̍X�V
				CursorSet( hWnd );
				//	�L�[���͂̃`�F�b�N
				AllKeyCheck();
				//	�}�E�X�N���b�N�̓��̓`�F�b�N
				AllButtonCheck();

				//	�W���C�X�e�B�b�N�̏��X�V
				CXInput::UpdateStick();

				//	�Q�[�����C���֐�
				pSceneManage -> GameMain ( hWnd );

				SyncOld = SyncNow;

			}
		}
	}

	timeEndPeriod(1);

	ReleaseAllTexture();

	pRenderManage -> AllReleaseMesh();

	//ReleaseXAudio2();

	if ( false == pSceneManage -> DeleteSceneObj() )	return 0;

	FreeDx( true );

	delete pSceneManage;

	return (int)msg.wParam;
}
