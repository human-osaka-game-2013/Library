#include "RenderManage.h"
#include "MouseFunc.h"
#include "Window.h"

/*
	�w�i�|���̐��l
*/
const float fWidth = 10.f, fHeight = 10.f;
const float fTu1 = 0.f, fTv1 = 0.f, fTu2 = 1.f, fTv2 = 1.f;

/*
	�R���X�g���N�^
*/
CRenderManager::CRenderManager() : 
	INIT_EYE_POS( 0.f, 0.f, -100.f ), INIT_LOOK_POS( 0.f, 0.f, 0.f ), 
	LEFT_ROT(0.f*D3DX_PI/180.f, 90.f*D3DX_PI/180.f, 0.f), RIGHT_ROT(0.f*D3DX_PI/180.f, -90.f*D3DX_PI/180.f, 0.f ),
	CENTER_ROT(0.f*D3DX_PI/180.f, 0.f*D3DX_PI/180.f, 0.f), vecCursorPos( 0.f,0.f, 0.f )
{

}

/*
	���b�V���̓Ǎ������`��o�b�t�@
*/
bool CRenderManager::LoadXFile( THING_ID _id, LPCSTR _xFileName )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	//x�t�@�C�����烁�b�V�������[�h����
	LPD3DXBUFFER	pD3DXMtrlBuffer	= NULL;

	if(FAILED(D3DXLoadMeshFromX(
		_xFileName,
		D3DXMESH_SYSTEMMEM,
		pD3Device,
		NULL,
		&pD3DXMtrlBuffer,
		NULL,
		&MeshInfo[ _id ].dwNumMaterials,
		&MeshInfo[ _id ].pMesh
		) ) )
	{
		MessageBoxA(NULL,"x�t�@�C���̓ǂݍ��݂Ɏ��s���܂���",_xFileName,MB_OK);
		return false;
	}


	D3DXMATERIAL*	d3dxMaterials	= (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	MeshInfo[ _id ].pMeshMaterials		= new D3DMATERIAL9[MeshInfo[ _id ].dwNumMaterials];
	MeshInfo[ _id ].pMeshTextures		= new LPDIRECT3DTEXTURE9[MeshInfo[ _id ].dwNumMaterials];

	for(DWORD i=0;	i<MeshInfo[ _id ].dwNumMaterials;	i++)
	{
		MeshInfo[ _id ].pMeshMaterials[i]			= d3dxMaterials[i].MatD3D;
		MeshInfo[ _id ].pMeshMaterials[i].Ambient	= MeshInfo[ _id ].pMeshMaterials[i].Diffuse;
		MeshInfo[ _id ].pMeshTextures[i]			= NULL;

		if(d3dxMaterials[i].pTextureFilename != NULL && lstrlen(d3dxMaterials[i].pTextureFilename) >0)
		{
			if(FAILED (D3DXCreateTextureFromFileEx (pD3Device,
													d3dxMaterials[i].pTextureFilename,
													D3DX_DEFAULT_NONPOW2,
													D3DX_DEFAULT_NONPOW2,
													D3DX_DEFAULT,
													0,
													D3DFMT_UNKNOWN,
													D3DPOOL_MANAGED,
													D3DX_FILTER_NONE,
													D3DX_FILTER_NONE,
													D3DCOLOR_ARGB ( 0, 0, 255, 0),
													NULL, NULL,
													&MeshInfo[ _id ].pMeshTextures[i]) ) )
			{
				MessageBox(NULL,TEXT("�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���"),NULL,MB_OK);
			}
		}
	}

	
	pD3DXMtrlBuffer->Release();

	return true;
}

/*
	�J������񏉊���
*/
void CRenderManager::CameraInit()
{
	//���_�̏�����
	CameraInfo.eyePos.x = INIT_EYE_POS.x;
	CameraInfo.eyePos.y = INIT_EYE_POS.y;
	CameraInfo.eyePos.z = INIT_EYE_POS.z;

	//�����_�̏�����
	CameraInfo.lookPos.x = INIT_LOOK_POS.x;
	CameraInfo.lookPos.y = INIT_LOOK_POS.y;
	CameraInfo.lookPos.z = INIT_LOOK_POS.z;

	//��]�Ɏg�p
	CameraInfo.radian = atan2f( INIT_LOOK_POS.x, INIT_LOOK_POS.z);
}

/*
	3D�`�揈��
*/
void CRenderManager::Transform( int _id, D3DXVECTOR3 _vecPosition, D3DXVECTOR3 _vecRoate, D3DXVECTOR3 _vecScall )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	//���[���h�g�����X�t�H�[��(��΍��W�ϊ�)
	//matWorld->y����]
	D3DXMATRIXA16	matWorld,matPosition, matScall, matRoate;						//[�ŏI�I�ȃ��[���h�g�����X�t�H�[��][���s�ړ��s����i�[����s��]
	D3DXMatrixIdentity(&matWorld);												//�P�ʍs��̍쐬�֐�
	D3DXMatrixRotationYawPitchRoll(&matRoate, _vecRoate.y, _vecRoate.x, _vecRoate.z);	//��]�s��̍쐬�֐�
	D3DXMatrixScaling(&matScall, _vecScall.x, _vecScall.y, _vecScall.z);					//�g��s��̍쐬�֐�
	D3DXMatrixTranslation(&matPosition, _vecPosition.x, _vecPosition.y, _vecPosition.z);	//���s�ړ��s��̍쐬�֐�

	D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);								//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);								//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);							//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)

	//�D3DTS_WORLD(���[���h�g�����X�t�H�[��)���matWorld�s����W���Ƃ��ģ�l�X�Ȏ�ނ̕ϊ����s�����Ƃ������_�����O�p�C�v���C��/Direct3D�ɒʒm
	pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	//�r���[�g�����X�t�H�[��
	//D3DXVECTOR3...3���̍s�x�N�g��
	//D3DXMATRIXA16...4x4�̍s��
	//�����_��J�����ʒu�̓����o��CameraInfo�������Ă���
	D3DXVECTOR3 eyePos	= GetEyePos();
	D3DXVECTOR3 lookPos	= GetLookPos();
	float		radian	= GetRad();

	D3DXVECTOR3	vecEyePt	( eyePos );		//�J����(���_)�ʒu
	D3DXVECTOR3	vecLookatPt	( lookPos );	//�����ʒu
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//����ʒu
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	pD3Device->SetTransform(D3DTS_VIEW, &matView);

	//�����_�X�V
	lookPos	 = vecLookatPt;

	//�v���W�F�N�V�����g�����X�t�H�[��(�ˉe�ϊ�)
	D3DXMATRIXA16	matProj;

	//	�ύX���܂���	12/13
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.0f, 0.0f, 200.f);
	//--------------------------------------------------------------------
	
	pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	//���C�g�����Ă�@���F�ŋ��ʔ��˗L��ɐݒ�
	D3DXVECTOR3	vecDirection(1,1,1);
	D3DLIGHT9		light;
	ZeroMemory(&light,sizeof(D3DLIGHT9) );
	light.Type		= D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r	= 1.0f;
	light.Diffuse.g	= 1.0f;
	light.Diffuse.b	= 1.0f;
	light.Specular.r	= 1.0f;
	light.Specular.g	= 1.0f;
	light.Specular.b	= 1.0f;
	light.Ambient.r	= 1.0f;	
	light.Ambient.g	= 1.0f;
	light.Ambient.b	= 1.0f;

	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction,&vecDirection);
	light.Range		= 200.f;
	pD3Device->SetLight(0,&light);
	pD3Device->LightEnable(0,TRUE);

	//�����_�����O
	for(DWORD i=0;	i < MeshInfo[ _id ].dwNumMaterials ; i++)
	{
		pD3Device->SetMaterial(&MeshInfo[ _id ].pMeshMaterials[i]);
		pD3Device->SetTexture(0,MeshInfo[ _id ].pMeshTextures[i]);
		MeshInfo[ _id ].pMesh->DrawSubset(i);
	}

	
}

/*
	�r���{�[�h�p�̒��_�`��	���݂͎g�p�o���܂���B������������
*/
void CRenderManager::BillboardingTransform( int _id, D3DXVECTOR3 _vecPosition )
{
	//LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();
	//LPDIRECT3DVERTEXBUFFER9 vb;

	//pD3Device -> SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
	//pD3Device -> SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	////	���_�o�b�t�@���f�o�C�X�ɐݒ�
	//pD3Device -> SetStreamSource( 0, vb, 0, sizeof(VERTEXS) );
	//pD3Device -> SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );


	////	���_�o�b�t�@�̃��b�N
	//VERTEXS* v;

	//if (SUCCEEDED( vb->Lock( 0, 4 * sizeof(VERTEXS), (void**)&v, 0 )))
	//{
	//	//	���_���W�̐ݒ�
	//	v[0].x = _vecPosition.x +fWidth/2;
	//	v[0].y = _vecPosition.y +fHeight/2;
	//	v[1].x = _vecPosition.x -fWidth/2;
	//	v[1].y = _vecPosition.y +fHeight/2;
	//	v[2].x = _vecPosition.x -fWidth/2;
	//	v[2].y = _vecPosition.y -fHeight/2;
	//	v[3].x = _vecPosition.x +fWidth/2;
	//	v[3].y = _vecPosition.y -fHeight/2;

	//	//	UV���W
	//	v[0].tu = fTu1;
	//	v[0].tv = fTv1;
	//	v[1].tu = fTu2;
	//	v[1].tv = fTv1;
	//	v[2].tu = fTu2;
	//	v[2].tv = fTv2;
	//	v[3].tu = fTu1;
	//	v[3].tv = fTv2;

	//	//	Z, RHW, ���_�F�̐ݒ�
	//	for (int i=0; i<4; i++) {
	//		v[i].Z=0;
	//		//v[i].RHW=0; 
	//		v[i].color=D3DCOLOR_ARGB(255,255,255,255);
	//	}

	//	//VERTEXS customVertex9[4] = {
	////		{ _vecPosition.x +fWidth/2,	_vecPosition.y +fHeight/2, _vecPosition.z, 0xff000000, fTu1, fTv1 },	//2
	////		{ _vecPosition.x -fWidth/2,	_vecPosition.y +fHeight/2, _vecPosition.z, 0xff000000, fTu2, fTv1 },	//3
	////		{ _vecPosition.x -fWidth/2,	_vecPosition.y -fHeight/2, _vecPosition.z, 0xff000000, fTu2, fTv2 },	//0
	////		{ _vecPosition.x +fWidth/2,	_vecPosition.y -fHeight/2, _vecPosition.z, 0xff000000, fTu1, fTv2 },	//1
	////	
	////};
	//}
	//D3DXVECTOR3 _vecRotate( 0.f, 0.f, -90.f*D3DX_PI/180.f );
	//D3DXVECTOR3 _vecScall( 1.6f, 1.f, 1.f );

	////���[���h�g�����X�t�H�[��(��΍��W�ϊ�)
	////matWorld->y����]
	//D3DXMATRIXA16	matWorld,matPosition, matScall, matRoate;						//[�ŏI�I�ȃ��[���h�g�����X�t�H�[��][���s�ړ��s����i�[����s��]
	//D3DXMatrixIdentity(&matWorld);												//�P�ʍs��̍쐬�֐�
	//D3DXMatrixRotationYawPitchRoll(&matRoate, _vecRotate.y, _vecRotate.x, _vecRotate.z);	//��]�s��̍쐬�֐�
	//D3DXMatrixScaling(&matScall, _vecScall.x, _vecScall.y, _vecScall.z);					//�g��s��̍쐬�֐�
	//D3DXMatrixTranslation(&matPosition, _vecPosition.x, _vecPosition.y, _vecPosition.z);	//���s�ړ��s��̍쐬�֐�

	//D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);								//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	//D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);								//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	//D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);							//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)

	////�D3DTS_WORLD(���[���h�g�����X�t�H�[��)���matWorld�s����W���Ƃ��ģ�l�X�Ȏ�ނ̕ϊ����s�����Ƃ������_�����O�p�C�v���C��/Direct3D�ɒʒm
	//pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	////�r���[�g�����X�t�H�[��
	////D3DXVECTOR3...3���̍s�x�N�g��
	////D3DXMATRIXA16...4x4�̍s��
	//D3DXVECTOR3 eyePos	= GetEyePos();
	//D3DXVECTOR3 lookPos	= GetLookPos();
	//float		radian	= GetRad();

	//D3DXVECTOR3	vecEyePt	( eyePos );		//�J����(���_)�ʒu
	//D3DXVECTOR3	vecLookatPt	( lookPos );	//�����ʒu
	//D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//����ʒu
	//D3DXMATRIXA16	matView;
	//D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	//pD3Device->SetTransform(D3DTS_VIEW, &matView);

	////�����_�X�V
	//lookPos	 = vecLookatPt;

	////�v���W�F�N�V�����g�����X�t�H�[��(�ˉe�ϊ�)
	//D3DXMATRIXA16	matProj;

	////	�ύX���܂���	12/13
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.0f, 200.0f);
	////--------------------------------------------------------------------
	//
	//pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	////���C�g�����Ă�@���F�ŋ��ʔ��˗L��ɐݒ�
	//D3DXVECTOR3	vecDirection(1,1,1);
	//D3DLIGHT9		light;
	//ZeroMemory(&light,sizeof(D3DLIGHT9) );
	//light.Type		= D3DLIGHT_DIRECTIONAL;
	//light.Diffuse.r	= 1.0f;
	//light.Diffuse.g	= 1.0f;
	//light.Diffuse.b	= 1.0f;
	//light.Specular.r	= 1.0f;
	//light.Specular.g	= 1.0f;
	//light.Specular.b	= 1.0f;
	//light.Ambient.r	= 1.0f;	
	//light.Ambient.g	= 1.0f;
	//light.Ambient.b	= 1.0f;

	//D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction,&vecDirection);
	//light.Range		= 200.f;
	//pD3Device->SetLight(0,&light);
	//pD3Device->LightEnable(0,TRUE);

	////���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	//// D3DXMATRIXA16 matWorld,matCurrentView,matPosition;
	//// D3DXMatrixIdentity(&matWorld);
	//// D3DXMatrixTranslation(&matPosition,_vecPosition.x,_vecPosition.y,
	////	 _vecPosition.z);
	//// D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);
	//// ���݂̃r���[�s��𓾂āA�A
	//// pD3Device->GetTransform(D3DTS_VIEW,&matCurrentView);
	////  ������t�s��ɂ��āA�A
	//// D3DXMatrixInverse(&matCurrentView,NULL,&matCurrentView);
	////  ���[���h�s��Ɋ|�����킹��ƁA�r���[�ϊ���ł��������ƂɂȂ�
	//// D3DXMatrixMultiply(&matWorld,&matWorld,&matCurrentView);

 ////    pD3Device->SetTransform( D3DTS_WORLD, &matWorld );
	//// 
	//// �r���[�g�����X�t�H�[��
	////D3DXVECTOR3...3���̍s�x�N�g��
	////D3DXMATRIXA16...4x4�̍s��
	////�����_��J�����ʒu��camera.cpp�������Ă���
	////D3DXVECTOR3 eyePos	= GetEyePos();
	////D3DXVECTOR3 lookPos	= GetLookPos();
	////float		radian	= GetRad();

	////D3DXVECTOR3	vecEyePt	( eyePos );		//�J����(���_)�ʒu
	////D3DXVECTOR3	vecLookatPt	( lookPos );	//�����ʒu
	////D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//����ʒu
	////D3DXMATRIXA16	matView;
	////D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	////pD3Device->SetTransform(D3DTS_VIEW, &matView);

	////�����_�X�V
	////lookPos	 = vecLookatPt;

	////�v���W�F�N�V�����g�����X�t�H�[��(�ˉe�ϊ�)
	////D3DXMATRIXA16	matProj;
	////D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.f, 1.f, 200.f);
	////pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	////���C�g�����Ă�@���F�ŋ��ʔ��˗L��ɐݒ�
	////D3DXVECTOR3	vecDirection(1,1,1);
	////D3DLIGHT9		light;
	////ZeroMemory(&light,sizeof(D3DLIGHT9) );
	////light.Type		= D3DLIGHT_DIRECTIONAL;
	////light.Diffuse.r	= 1.0f;
	////light.Diffuse.g	= 1.0f;
	////light.Diffuse.b	= 1.0f;
	////light.Specular.r	= 1.0f;
	////light.Specular.g	= 1.0f;
	////light.Specular.b	= 1.0f;
	////light.Ambient.r	= 1.0f;	
	////light.Ambient.g	= 1.0f;
	////light.Ambient.b	= 1.0f;

	////D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction,&vecDirection);
	////light.Range		= 200.f;
	////pD3Device->SetLight(0,&light);
	////pD3Device->LightEnable(0,TRUE);

	////_vecPosition.z = -0.5f;

	////VERTEXS* pVertex;

	////pD3Device -> CreateVertexBuffer( sizeof(VERTEXS) * 4, 0, D3DFVF, D3DPOOL_MANAGED, &vb, NULL);
	////vb->Lock(0,0,(void **)&pVertex,0);
	////memcpy(pVertex,customVertex9,sizeof(VERTEXS) * 4);
	////vb->Unlock();

	//
	//TEXTUREINFO* TextureInfo = GetTextInfo();

	//pD3Device -> SetTexture ( 0, TextureInfo[_id].pTexture );
	//pD3Device -> DrawPrimitive(D3DPT_TRIANGLEFAN,0,2);

	//pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/*
	3D�A�j���[�V�����t���`�揈��
*/
void CRenderManager::AnimationTransform( int _id, D3DXVECTOR3 _vecPosition, D3DXVECTOR3 _vecRoate, D3DXVECTOR3 _vecScall )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	//���[���h�g�����X�t�H�[��(��΍��W�ϊ�)
	//matWorld->y����]
	D3DXMATRIXA16	matWorld,matPosition, matScall, matRoate;						//[�ŏI�I�ȃ��[���h�g�����X�t�H�[��][���s�ړ��s����i�[����s��]
	D3DXMatrixIdentity(&matWorld);												//�P�ʍs��̍쐬�֐�
	D3DXMatrixRotationYawPitchRoll(&matRoate, _vecRoate.y, _vecRoate.x, _vecRoate.z);	//��]�s��̍쐬�֐�
	D3DXMatrixScaling(&matScall, _vecScall.x, _vecScall.y, _vecScall.z);					//�g��s��̍쐬�֐�
	D3DXMatrixTranslation(&matPosition, _vecPosition.x, _vecPosition.y, _vecPosition.z);	//���s�ړ��s��̍쐬�֐�

	D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);								//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);								//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);							//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)

	//�D3DTS_WORLD(���[���h�g�����X�t�H�[��)���matWorld�s����W���Ƃ��ģ�l�X�Ȏ�ނ̕ϊ����s�����Ƃ������_�����O�p�C�v���C��/Direct3D�ɒʒm
	pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	//�r���[�g�����X�t�H�[��
	//D3DXVECTOR3...3���̍s�x�N�g��
	//D3DXMATRIXA16...4x4�̍s��
	//�����_��J�����ʒu�̓����o��CameraInfo�������Ă���
	D3DXVECTOR3 eyePos	= GetEyePos();
	D3DXVECTOR3 lookPos	= GetLookPos();
	float		radian	= GetRad();

	D3DXVECTOR3	vecEyePt	( eyePos );		//�J����(���_)�ʒu
	D3DXVECTOR3	vecLookatPt	( lookPos );	//�����ʒu
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//����ʒu
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	pD3Device->SetTransform(D3DTS_VIEW, &matView);

	//�����_�X�V
	lookPos	 = vecLookatPt;

	//�v���W�F�N�V�����g�����X�t�H�[��(�ˉe�ϊ�)
	D3DXMATRIXA16	matProj;

	//	�ύX���܂���	12/13
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.9f, 200.0f);
	//--------------------------------------------------------------------
	
	pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	//���C�g�����Ă�@���F�ŋ��ʔ��˗L��ɐݒ�
	D3DXVECTOR3	vecDirection(1,1,1);
	D3DLIGHT9		light;
	ZeroMemory(&light,sizeof(D3DLIGHT9) );
	light.Type		= D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r	= 1.0f;
	light.Diffuse.g	= 1.0f;
	light.Diffuse.b	= 1.0f;
	light.Specular.r	= 1.0f;
	light.Specular.g	= 1.0f;
	light.Specular.b	= 1.0f;
	light.Ambient.r	= 1.0f;	
	light.Ambient.g	= 1.0f;
	light.Ambient.b	= 1.0f;

	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction,&vecDirection);
	light.Range		= 200.f;
	pD3Device->SetLight(0,&light);
	pD3Device->LightEnable(0,TRUE);

	LPD3DXMATRIX _World = &matWorld;

	AllocateHierarchy[ _id ].SetWorld( _World );

	AllocateHierarchy[ _id ].Draw( pD3Device );
}

/*
	�g�p����S�Ă�x�t�@�C���ǂݍ���
*/	
bool CRenderManager::AllLoadXFile()
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	if( E_FAIL == AllocateHierarchy[AN_WAIT].Load( pD3Device, "resource/xfile/tiny/wait.x" ) )
		return false;
	if( E_FAIL == AllocateHierarchy[AN_RUN].Load( pD3Device, "resource/xfile/tiny/run.x" ) )
		return false;
	if( E_FAIL == AllocateHierarchy[AN_JUMP].Load( pD3Device, "resource/xfile/tiny/jump.x" ) )
		return false;
	if( E_FAIL == AllocateHierarchy[AN_DOWN].Load( pD3Device, "resource/xfile/tiny/down.x" ) )
		return false;
	if( false == LoadXFile( TH_BG1, "resource/xfile/stage1.x" ) )
		return false;
	if( false == LoadXFile( TH_BOX_1, "resource/xfile/block.X" ) )
		return false;
	if( false == LoadXFile( TH_BULLET, "resource/xfile/bullet.x") )
		return false;
	return true;

}

/*
	���b�V���f�[�^�̉��
*/
void CRenderManager::ReleaseMesh( int _id )
{
	//���b�V�����
	SAFE_RELEASE( MeshInfo[ _id ].pMesh );
	
	//�e�N�X�`�����
	for( DWORD i = 0; i < MeshInfo[ _id ].dwNumMaterials; i++ )
	{
		SAFE_RELEASE( MeshInfo[ _id ].pMeshTextures[i] );
	}
	 
	//�z����
	NULL_ARRAY_DELETE( MeshInfo[ _id ].pMeshTextures);
	NULL_ARRAY_DELETE( MeshInfo[ _id ].pMeshMaterials);

}

/*
	�S���b�V���f�[�^�����
*/
void CRenderManager::AllReleaseMesh()
{
	for( int iCount = 0; iCount < THING_MAX; iCount++ )
	{
		ReleaseMesh( iCount );
	}
	for( int iCount = 0; iCount < AN_THING_MAX; iCount++ )
	{
		LPD3DXFRAME pFrame = NULL;
		pFrame = AllocateHierarchy[iCount].GetFrame();
		AllocateHierarchy[iCount].DestroyFrame( pFrame );
		AllocateHierarchy[iCount].GetAnimCtrl()->Release();
	}
}

//	���_���W�̎擾
D3DXVECTOR3 CRenderManager::GetEyePos() { return CameraInfo.eyePos; }

//	�����_���W�̎擾
D3DXVECTOR3 CRenderManager::GetLookPos(){ return CameraInfo.lookPos; }

//	���_��]�␳�x�̎擾
float CRenderManager::GetRad()	{ return CameraInfo.radian; }


/*
	�X�N���[�����W�����[���h���W�ɕϊ�
*/
D3DXVECTOR3* CRenderManager::CalcScreenToWorld
(
   D3DXVECTOR3* pout,	
   int Sx,				//	�X�N���[�����W����
   int Sy,				//	�X�N���[�����W����
   float fZ,			//	�ˉe��Ԃł�Z�l�i0�`1�j
   int Screen_w,		//	�X�N���[���̉���
   int Screen_h,		//	�X�N���[���̏c��
   D3DXMATRIXA16* View,	//	�r���[�s��
   D3DXMATRIXA16* Prj	//	�ˉe�ϊ��s��
)
{
   // �e�s��̋t�s����Z�o
   D3DXMATRIXA16 InvView, InvPrj, VP, InvViewport;
   D3DXMatrixInverse( &InvView, NULL, View );
   D3DXMatrixInverse( &InvPrj, NULL, Prj );
   D3DXMatrixIdentity( &VP );
   VP._11 = Screen_w/2.0f; VP._22 = -Screen_h/2.0f;
   VP._41 = Screen_w/2.0f; VP._42 = Screen_h/2.0f;
   D3DXMatrixInverse( &InvViewport, NULL, &VP );

   // �t�ϊ�
   D3DXMATRIXA16 tmp = InvViewport * InvPrj * InvView;
   D3DXVec3TransformCoord( pout, &D3DXVECTOR3((float)Sx,(float)Sy,fZ), &tmp );

   return pout;
}

/*
	�X�N���[�����W���̃}�E�X���W�����[���h���W�ɕϊ�
*/
void CRenderManager::MousePosTransform()
{
	D3DXMATRIXA16	matView;
	D3DXMATRIXA16	matProj;

	D3DXVECTOR3	vecEyePt	( GetEyePos() );	//�J����(���_)�ʒu
	D3DXVECTOR3	vecLookatPt	( GetLookPos() );	//�����ʒu
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);	//����ʒu

	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.9f, 100.0f);

	CalcScreenToWorld ( &vecCursorPos, GetCursorMoveVolX(), GetCursorMoveVolY(), 
						1.f, WIDTH, HEIGHT, &matView, &matProj );

	char msg[256];
	ZeroMemory(msg, sizeof(msg));
	sprintf_s(msg, "vecCursorPos x = %f, y = %f, z = %f\n", vecCursorPos.x, vecCursorPos.y, vecCursorPos.z);
	OutputDebugStringA(msg);
}