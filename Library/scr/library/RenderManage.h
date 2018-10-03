#ifndef _RENDER_MANAGE_H_
#define _RENDER_MANAGE_H_

#include "graphic.h"
#include "AllocateHierarchy.h"
#include "gameObject.h"

//	���b�V���f�[�^
struct MESH_INFO
{
	LPD3DXMESH			pMesh;			//	���b�V���f�[�^�̊i�[
	D3DMATERIAL9*		pMeshMaterials;	//	�}�e���A���̃f�[�^
	LPDIRECT3DTEXTURE9*	pMeshTextures;	//	�e�N�X�`���̃f�[�^
	DWORD				dwNumMaterials;	//	
};

//	�J�������
struct CAMERA_INFO
{
	D3DXVECTOR3 eyePos;		// ���_���Wxyz
	D3DXVECTOR3 lookPos;	// �����_���Wxyz
	float		radian;		// ���_��]�␳�x
};

class CRenderManager
{
public:
	//	�g�p���郁�b�V���t�@�C����ID�Ƃ��ė�
	enum THING_ID
	{
		TH_BG1,

		TH_BOX_1,

		TH_BULLET,

		THING_MAX
	};

	//	�g�p����A�j���[�V�����t�����b�V���t�@�C����
	//	ID�Ƃ��ė�
	enum ANIM_THING_ID
	{
		AN_WAIT = CGameObject::STATE_WAIT,

		AN_RUN = CGameObject::STATE_WALK,

		AN_JUMP = CGameObject::STATE_JUMP,

		AN_DOWN = CGameObject::STATE_DOWN,

		AN_THING_MAX
	};

public:
	const D3DXVECTOR3 LEFT_ROT;
	const D3DXVECTOR3 RIGHT_ROT;
	const D3DXVECTOR3 CENTER_ROT;
	const D3DXVECTOR3 INIT_EYE_POS;
	const D3DXVECTOR3 INIT_LOOK_POS;
	D3DXVECTOR3	vecCursorPos;

	//	�A�j���[�V�����t�����b�V���f�[�^�ۑ��ϐ�
	CAllocateHierarchy AllocateHierarchy[ AN_THING_MAX ];

private:
	MESH_INFO MeshInfo[ THING_MAX ];	//	���b�V���f�[�^�ۑ��p�����o�ϐ�

	CAMERA_INFO CameraInfo;		//	�J�������ۑ��p�����o�ϐ�

public:
	//	�R���X�g���N�^
	CRenderManager();

public:
	//	x�t�@�C���ǂݍ���
	//	(in)���b�V���t�@�C����ID�C�t�@�C���A�h���X (out)�ǂݍ��ݐ�����true	���s��false
	bool LoadXFile( THING_ID _id, LPCSTR _xFileName );

	//	�g�p����S�Ă�x�t�@�C���ǂݍ���
	bool AllLoadXFile();

	//	�J������񏉊���
	void CameraInit();

	/*
		�r���{�[�h�p�̒��_�`��
	*/
	void CRenderManager::BillboardingTransform( int _id, D3DXVECTOR3 _vecPosition );
	
	//	3D�`�揈��
	void Transform( int _id, D3DXVECTOR3 _vecPosition, D3DXVECTOR3 _vecRoate, D3DXVECTOR3 _vecScall );

	//	3D�A�j���[�V�����t���`�揈��
	void AnimationTransform( int _id, D3DXVECTOR3 _vecPosition, D3DXVECTOR3 _vecRoate, D3DXVECTOR3 _vecScall );

	//	���b�V���f�[�^�̉��
	void ReleaseMesh( int _id );

	//	�S���b�V���f�[�^�����
	void AllReleaseMesh();

	// �X�N���[�����W�����[���h���W�ɕϊ�
	D3DXVECTOR3* CalcScreenToWorld
	(
	   D3DXVECTOR3* pout,	
	   int Sx,				//	�X�N���[�����W����
	   int Sy,				//	�X�N���[�����W����
	   float fZ,			//	�ˉe��Ԃł�Z�l�i0�`1�j
	   int Screen_w,		//	�X�N���[���̉���
	   int Screen_h,		//	�X�N���[���̏c��
	   D3DXMATRIXA16* View,	//	�r���[�s��
	   D3DXMATRIXA16* Prj		//	�ˉe�ϊ��s��
	);

	//	�X�N���[�����W���̃}�E�X���W�����[���h���W�ɕϊ�
	void MousePosTransform();

public:
	//	���_���W�̎擾
	D3DXVECTOR3 GetEyePos();
	
	//	�����_���W�̎擾
	D3DXVECTOR3 GetLookPos();
	
	//	���_��]�␳�x�̎擾
	float	GetRad();
};

#endif