#ifndef _ALLOCATEHIERARCHY_H_
#define _ALLOCATEHIERARCHY_H_

#include<d3dx9.h>
#include<string>

//�A�j���[�V�����K�w���b�V���ǂݍ��݃N���X
class CAllocateHierarchy : public ID3DXAllocateHierarchy{
private:
	//���b�V���t���[���\����
	struct CMeshFrame : public D3DXFRAME{
		D3DXMATRIX CombinedTransformationMatrix;	//�e�t���[���ɉe������s��
	};
	//���b�V���R���e�\����
	struct CMeshContainer : public D3DXMESHCONTAINER{
		LPDIRECT3DTEXTURE9*		ppTexture;		//���b�V���ɓ\��t������e�N�X�`��
		DWORD					BoneNum;		//�{�[���̐�
		DWORD					Weight;			//�d�݂̌�
		LPD3DXBUFFER			pBoneBuf;		//�{�[�����
		D3DXMATRIX**			ppMatRoot;		//�{�[���̃��[���h�s��̐擪�|�C���^
		D3DXMATRIX*				pMatOffset;		//�{�[���̃I�t�Z�b�g�s��
	};
	LPD3DXFRAME					m_pFrameRoot;	//�t���[���̃g�b�v�m�[�h
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;	//�A�j���[�V�����R���g���[���[
public:
    STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, 
                            LPD3DXFRAME *ppNewFrame);
    STDMETHOD(CreateMeshContainer)(THIS_ 
        LPCSTR Name, 
        CONST D3DXMESHDATA *pMeshData, 
        CONST D3DXMATERIAL *pMaterials, 
        CONST D3DXEFFECTINSTANCE *pEffectInstances, 
        DWORD NumMaterials, 
        CONST DWORD *pAdjacency, 
        LPD3DXSKININFO pSkinInfo, 
        LPD3DXMESHCONTAINER *ppNewMeshContainer);
    STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
    STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);
public:
	//���[���h���W�ݒ�
	void SetWorld(LPD3DXMATRIX _World);
	//���b�V���ǂݍ���
	HRESULT Load(LPDIRECT3DDEVICE9 _pDevice,std::string _FileName);
	//�K�w���b�V���`��
	void Draw(LPDIRECT3DDEVICE9 _pDevice);
	//�A�j���[�V�����R���g���[���擾
	LPD3DXANIMATIONCONTROLLER GetAnimCtrl();
	//�t���[���̃A�h���X�擾
	LPD3DXFRAME GetFrame();

private:
	//�t���[�����̃��b�V�����ƂɃ��[���h�ϊ��s����X�V
	void UpdateWorld(LPD3DXFRAME _pFrameBase,LPD3DXMATRIX _pParentMatrix);
	//�{�[���s��̊��蓖�ĂƏ�����(�t���[��)
	HRESULT AllocBone(LPD3DXFRAME _pFrame);
	//�{�[���s��̊��蓖�ĂƏ�����(�R���e�i)
	HRESULT AllocBoneMatrix(LPD3DXMESHCONTAINER _pMeshContainer);
	//�t���[���������_�����O
	void DrawFrame(LPDIRECT3DDEVICE9 _pDevice,LPD3DXFRAME _pFrameBase);
	//�t���[�����̂��ꂼ��̃��b�V���������_�����O
	void DrawContainer(LPDIRECT3DDEVICE9 _pDevice,
		CMeshContainer* _pContainer,
		CMeshFrame* _pFrame);
};

#endif
