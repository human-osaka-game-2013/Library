#include "device.h"
#include "joystick_XInput.h"

//---------------------------------------------------
//	�v���g�^�C�v�錾
//---------------------------------------------------

// �L�[�{�[�h�p�I�u�W�F�N�g�쐬
HRESULT InitKeyDevice ( HWND );

// �}�E�X�p�I�u�W�F�N�g�쐬
HRESULT InitMouseDevice ( HWND, bool bForeGroundMode = true );

//---------------------------------------------------
// �|�C���^�ϐ��錾
//---------------------------------------------------
LPDIRECT3D9				pDirect3D;	//3D�I�u�W�F�N�g
D3DPRESENT_PARAMETERS	d3dpp;
LPDIRECT3DDEVICE9	pD3Device;
LPDIRECTINPUT8			pDinput	= NULL; //�C���v�b�g -> ���͏���

//	
LPDIRECT3DDEVICE9	Getd3Device () { return pD3Device; }
//
LPDIRECTINPUT8	GetInputDevice () { return pDinput; }

// Direct3D�̏�����
// ��1�����F�E�C���h�n���h��
HRESULT InitD3d ( HWND hWnd )
{
	D3DDISPLAYMODE d3ddm;
	
	// DirectX �I�u�W�F�N�g�̐���
	if( NULL == ( pDirect3D = Direct3DCreate9 ( D3D_SDK_VERSION ) ) )
	{
		MessageBoxA(0,"Direct3D�̍쐬�Ɏ��s���܂���","",MB_OK);
		return E_FAIL;
	}

	// Display Mode �̐ݒ�
	pDirect3D -> GetAdapterDisplayMode ( D3DADAPTER_DEFAULT, &d3ddm );

	ZeroMemory(	&d3dpp, sizeof ( d3dpp ));

	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount  = 1;
	d3dpp.SwapEffect	   = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed		   = TRUE;

	if( FAILED( pDirect3D->CreateDevice( D3DADAPTER_DEFAULT,
										 D3DDEVTYPE_HAL,
										 hWnd,
										 D3DCREATE_HARDWARE_VERTEXPROCESSING,
										 &d3dpp,
										 &pD3Device ) ) )
	{
		MessageBoxA(0,"HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�",NULL,MB_OK);
		if( FAILED( pDirect3D->CreateDevice( D3DADAPTER_DEFAULT,
											 D3DDEVTYPE_REF,
											 hWnd,
											 D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											 &d3dpp,
											 &pD3Device ) ) )
		{
			MessageBoxA(0,"DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���",NULL,MB_OK);
				return E_FAIL;
		}    
	}

	return S_OK;
}

//�_�C���N�g�C���v�b�g�̏������֐�
HRESULT InitDinput(HWND hWnd)
{
	HRESULT hr;
	
	//�DirectInput��I�u�W�F�N�g�̍쐬
	if(FAILED (hr = DirectInput8Create ( GetModuleHandle(NULL),
										 DIRECTINPUT_VERSION,
										 IID_IDirectInput8,
										 (VOID**)&pDinput,
										 NULL ) ) )
	{
		return hr;
	}
	//	�L�[�{�[�h�f�o�C�X�̃I�u�W�F�N�g�̍쐬
	if (FAILED (hr = InitKeyDevice ( hWnd ) ) )
	{
		return hr;
	}
	
	//	�}�E�X�f�o�C�X�̃I�u�W�F�N�g�̍쐬
	if (FAILED (hr = InitMouseDevice ( hWnd, false ) ) )
	{
		return hr;
	}	

	//	CXInput�N���X�̏�����
	CXInput::Initialize();

	return S_OK;
}