#ifndef _LIB_HEAD_INCLUDE_

#define _LIB_HEAD_INCLUDE_
#define DIRECTINPUT_VERSION 0x0800

//�v���v���֘A�w�b�_�[�t�@�C��
#include <stdio.h>
#include <windows.h>	//window��b�t�@�C��
#include <d3dx9.h>	
#include <dinput.h>
#include <dinputd.h>
#include <mmsystem.h>	//wav�Đ�
#include <XAudio2.h>	//mp3,wma�Đ�
#include <time.h>
#include <XInput.h>
#include <cstdlib>

//���C�u�����Ǎ�
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9d.lib" )
#pragma comment ( lib, "dinput8.lib" )
#pragma comment ( lib, "dxguid.lib" )
#pragma comment	(lib, "dsound.lib")	//wav�Đ�
#pragma comment	(lib, "winmm.lib")
#pragma comment(lib, "Xinput.lib")

#define	CLASS_DELETE(p)	{ if(p) { delete (p); (p) = NULL;} }	//	�N���X�|�C���^�̍폜
#define SAFE_RELEASE(p) { if(p) { (p) -> Release(); (p) = NULL; } }
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = NULL; } }
#define NULL_DELETE(p) { if(p) { delete (p); (p) = NULL; } }
#define NULL_ARRAY_DELETE(p) { if(p) { delete[] (p); (p) = NULL; } }

#define D3DFVF ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK, __FILE__, __LINE__ )
#define new DBG_NEW
#endif
#endif

#endif