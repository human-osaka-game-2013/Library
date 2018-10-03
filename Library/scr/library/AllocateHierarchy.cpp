#include<tchar.h>

#include"AllocateHierarchy.h"
#include"lib_head.h"

//�t���[���I�u�W�F�N�g����
HRESULT CAllocateHierarchy::CreateFrame(LPCSTR _Name,LPD3DXFRAME* _ppNewFrame){
	*_ppNewFrame = 0;
	CMeshFrame* pFrame = new CMeshFrame();	//���b�V���t���[������
	if(!pFrame)return E_FAIL;

	if( _Name != NULL ) {
		pFrame->Name = new char[strlen(_Name) + 1];	//�t���[�����𕶎������������m��
		if(!pFrame->Name)return E_FAIL;

		//�e���ڐݒ�
		strcpy(pFrame->Name,_Name);	//�t���[����
	}
	else
	{
		_Name = "";
		pFrame->Name = new char[strlen(_Name) + 1];	//�t���[�����𕶎������������m��
		//�e���ڐݒ�
		strcpy(pFrame->Name,_Name);	//�t���[����
		if(!pFrame->Name)return E_FAIL;

	}
	D3DXMatrixIdentity(&pFrame->TransformationMatrix);			//�t���[����
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);	//�g�����X�t�H�[���s��
	pFrame->pMeshContainer		= NULL;							//���b�V���R���e�i
	pFrame->pFrameFirstChild	= NULL;							//�P�ԏ��߂̎q
	pFrame->pFrameSibling		= NULL;							//�Z��

	//�V�����t���[��
	*_ppNewFrame = pFrame;

	return S_OK;
}

//���b�V���R���e�i����
HRESULT CAllocateHierarchy::CreateMeshContainer(
		LPCSTR						_Name,					//�t���[����
		CONST D3DXMESHDATA*			_pMeshData,				//���b�V���f�[�^�\���̂ւ̃|�C���^
		CONST D3DXMATERIAL*			_pMaterials,			//���b�V���Ɏg�p����}�e���A��
		CONST D3DXEFFECTINSTANCE*	_pEffectInstances,		//���b�V���Ɏg�p����G�t�F�N�g�C���X�^���X
		DWORD						_NumMaterials,			//�}�e���A����
		CONST DWORD*				_pAdjacency,			//���b�V���אڐ�
		LPD3DXSKININFO				_pSkinInfo,				//�X�L�����b�V���ւ̃|�C���^
		LPD3DXMESHCONTAINER*		_ppNewMeshContainer){	//�����������b�V���R���e�i�ւ̃|�C���^

	LPDIRECT3DDEVICE9 pDevice = NULL;		//�f�o�C�X
	LPD3DXMESH pMesh = _pMeshData->pMesh;	//���b�V�����
	*_ppNewMeshContainer = NULL;
	DWORD dwBoneAnt = 0;					//�{�[����

	//���b�V���R���e�i����
	CMeshContainer* pMeshContainer = new CMeshContainer();
	if(!pMeshContainer)return E_FAIL;
	//�[���N���A
	ZeroMemory(pMeshContainer,sizeof(CMeshContainer));

	//�t���[����
	pMeshContainer->MeshData = *_pMeshData;
	pMeshContainer->Name = new char[strlen(_Name) * 1];
	if(!pMeshContainer->Name)return E_FAIL;
	strcpy(pMeshContainer->Name,_Name);

	pMesh->GetDevice(&pDevice);			//���b�V������f�o�C�X�擾
	//���b�V���Ɋ܂܂��ʂ̐����擾
	DWORD faceNum = pMesh->GetNumFaces();

	//�@�����Ȃ��ꍇ
	if(!(pMesh->GetFVF() & D3DFVF_NORMAL)){
		//�@���񂪖����̂Œǉ�
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		//FVF�R�[�h���g�p���āA���b�V���̃R�s�[����
		if(FAILED(pMesh->CloneMeshFVF(
			pMesh->GetOptions(),
			pMesh->GetFVF() | D3DFVF_NORMAL,
			pDevice,
			&pMeshContainer->MeshData.pMesh))){
				//���s
				return E_FAIL;
		}
		pMesh = pMeshContainer->MeshData.pMesh;
		//���b�V���Ɋ܂܂��e���_�̖@��̌������v�Z���A�ݒ�
		D3DXComputeNormals(pMesh,NULL);
	}
	//�@��������ꍇ
	else{
		//�@��������ꍇ
		pMeshContainer->MeshData.pMesh = pMesh;
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		//�Q�ƃJ�E���^���C���N�������g
		pMesh->AddRef();
	}

	//�}�e���A���ݒ�
	pMeshContainer->NumMaterials	= max(1,_NumMaterials);									//���b�V���Ɋ܂܂��}�e���A����
	pMeshContainer->pMaterials		= new D3DXMATERIAL[pMeshContainer->NumMaterials];		//���b�V���}�e���A���z��
	pMeshContainer->ppTexture		= new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];	//�e�N�X�`���̃|�C���^�ւ̃|�C���^
	pMeshContainer->pAdjacency		= new DWORD[faceNum * 3];								//���b�V���̎O�p�`���ƂɂR�̗אڏ�񂪂���
	if(!pMeshContainer->pAdjacency || !pMeshContainer->pMaterials)return E_FAIL;

	//�אڏ�����
	memcpy(pMeshContainer->pAdjacency,_pAdjacency,sizeof(DWORD) * faceNum * 3);
	//�e�N�X�`���������S�̂��߂ɏ�����
	memset(pMeshContainer->ppTexture,0,sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	//�}�e���A�����i�[
	if(_NumMaterials > 0){
		//�}�e���A��������ꍇ
		memcpy(pMeshContainer->pMaterials,_pMaterials,sizeof(D3DXMATERIAL));

		for(DWORD i=0;i<_NumMaterials;i++){
			//�e�N�X�`���������
			if(pMeshContainer->pMaterials[i].pTextureFilename){
				char strTextureName[MAX_PATH];
				strcpy(strTextureName,pMeshContainer->pMaterials[i].pTextureFilename);
				//�e�N�X�`��
				if(FAILED(D3DXCreateTextureFromFileA(
					pDevice,
					strTextureName,
					&pMeshContainer->ppTexture[i]))){
						pMeshContainer->ppTexture[i] = NULL;
				}
				//�d���ǂݍ��ݖh�~
				pMeshContainer->pMaterials[i].pTextureFilename = NULL;
			}
		}
	}
	else{
		//�}�e���A���������ꍇ
		pMeshContainer->pMaterials[0].pTextureFilename = NULL;
		memset(&pMeshContainer->pMaterials[0].MatD3D,0,sizeof(D3DMATERIAL9));

		//�e�N�X�`�����\���Ă��Ȃ����b�V���\���̂��߂Ɍ���w��
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.a = pMeshContainer->pMaterials[0].MatD3D.Diffuse.a;
	}

	
	//�G�t�F�N�g�f�[�^�̊m�F------------------------
	const D3DXEFFECTINSTANCE *pEI = _pEffectInstances;  // �����̂�
	pMeshContainer->pEffects = new D3DXEFFECTINSTANCE;
	if( pEI->pEffectFilename != NULL )
		strcpy( pMeshContainer->pEffects->pEffectFilename, pEI->pEffectFilename );
	else
		pMeshContainer->pEffects->pEffectFilename = NULL;

	pMeshContainer->pEffects->NumDefaults = pEI->NumDefaults;
	pMeshContainer->pEffects->pDefaults = new D3DXEFFECTDEFAULT[pEI->NumDefaults];
	
	D3DXEFFECTDEFAULT *pDIST = pEI->pDefaults;	// �R�s�[��
	D3DXEFFECTDEFAULT *pCOPY = pMeshContainer->pEffects->pDefaults;	// �R�s�[��
	for(unsigned int i=0; i<pEI->NumDefaults; i++)
	{
		pCOPY[i].pParamName = new char[strlen(pDIST[i].pParamName) + 1];
		if( pDIST[i].pParamName != NULL )
		{
			strcpy( pCOPY[i].pParamName, pDIST[i].pParamName);
		}
		DWORD NumBytes = pCOPY[i].NumBytes = pDIST[i].NumBytes;
		pCOPY[i].Type = pDIST[i].Type;
		if(pDIST[i].Type <= D3DXEDT_DWORD){
			pCOPY[i].pValue = new DWORD[ NumBytes ];
			memcpy( pCOPY[i].pValue, pDIST[i].pValue, NumBytes);
		}
		NULL_ARRAY_DELETE(pCOPY[i].pParamName);
		NULL_ARRAY_DELETE(pCOPY[i].pValue);
	}

	//---------------------------------------------

	if(_pSkinInfo){
		//�X�L�����b�V��������
		pMeshContainer->pSkinInfo = _pSkinInfo;
		//�Q�ƃJ�E���^�C���N�������g
		_pSkinInfo->AddRef();

		//�{�[�����擾
		dwBoneAnt = _pSkinInfo->GetNumBones();
		pMeshContainer->pMatOffset = new D3DXMATRIX[dwBoneAnt];

		//�{�[���s��R�s�[
		for(DWORD i=0;i<dwBoneAnt;i++){
			memcpy(
				&pMeshContainer->pMatOffset[i],
				pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i),
				sizeof(D3DXMATRIX));
		}
		//���_�P�ʂ̃u�����h�̏d�݂ƃ{�[����K�p�����V�������b�V���𐶂ݏo��
		if(FAILED(pMeshContainer->pSkinInfo->ConvertToBlendedMesh(
			pMesh,							//���b�V��
			NULL,
			pMeshContainer->pAdjacency,		//���b�V���̗אڏ��
			NULL,NULL,NULL,
			&pMeshContainer->Weight,		//�{�[���̏d��
			&pMeshContainer->BoneNum,		//�{�[����
			&pMeshContainer->pBoneBuf,		//�{�[���e�[�u��
			&pMeshContainer->MeshData.pMesh	//�V�������b�V��
			))){
				return E_FAIL;
		}
		SAFE_RELEASE(pMesh);

	}
	//�V���������������b�V���R���e�i���Ăяo�����ɃR�s�[
	*_ppNewMeshContainer = pMeshContainer;

	return S_OK;
}

//�t���[���j��
HRESULT CAllocateHierarchy::DestroyFrame(THIS_ LPD3DXFRAME _pFrameToFree){

	if(_pFrameToFree->Name)
	  NULL_ARRAY_DELETE(_pFrameToFree->Name);
	if(_pFrameToFree->pMeshContainer)
	   DestroyMeshContainer(_pFrameToFree->pMeshContainer);
	if(_pFrameToFree->pFrameSibling)
	   DestroyFrame(_pFrameToFree->pFrameSibling);
	if(_pFrameToFree->pFrameFirstChild)
	   DestroyFrame(_pFrameToFree->pFrameFirstChild);
	
	SAFE_DELETE(_pFrameToFree);
	
	return S_OK;
}

//���b�V���R���e�i�j��
HRESULT CAllocateHierarchy::DestroyMeshContainer( THIS_ LPD3DXMESHCONTAINER _pMeshContainerToFree){

	//���g�ō�����\���̂̃����o��������邽�߂Ɍ^��ύX
	CMeshContainer* pContainer = (CMeshContainer*)_pMeshContainerToFree;
	
	if( !pContainer->Name ){
		NULL_ARRAY_DELETE(pContainer->Name);
	}
	else{
		pContainer->Name = NULL;
		NULL_ARRAY_DELETE(pContainer->Name);
	}
	SAFE_RELEASE(pContainer->MeshData.pMesh);
	
	//�e�N�X�`���������
	if(pContainer->ppTexture){
		for(DWORD i=0;i<pContainer->NumMaterials;i++){
			NULL_ARRAY_DELETE(pContainer->pMaterials[i].pTextureFilename);
			SAFE_RELEASE(pContainer->ppTexture[i]);
		}
	}

	NULL_ARRAY_DELETE(pContainer->pMaterials);

	// �G�t�F�N�g
	if( pContainer->pEffects != NULL )
	{
		for( int i=0; i<pContainer->pEffects->NumDefaults; i++){
			NULL_ARRAY_DELETE(pContainer->pEffects->pDefaults[i].pParamName);
			NULL_ARRAY_DELETE(pContainer->pEffects->pDefaults[i].pValue);
		}
		NULL_ARRAY_DELETE(pContainer->pEffects->pEffectFilename);
		NULL_ARRAY_DELETE(pContainer->pEffects->pDefaults);
	}
	SAFE_DELETE(pContainer->pEffects);
	//delete pContainer->pEffects;

	NULL_ARRAY_DELETE(pContainer->pAdjacency);
	NULL_ARRAY_DELETE(pContainer->ppTexture);
	NULL_ARRAY_DELETE(pContainer->pMatOffset);
	NULL_ARRAY_DELETE(pContainer->ppMatRoot);
	SAFE_RELEASE(pContainer->pBoneBuf);
	SAFE_RELEASE(pContainer->pSkinInfo);

	//�R���e�i
	SAFE_DELETE(pContainer);
	//delete pContainer;

	return S_OK;
}


//�{�[���s��̊��蓖�ĂƏ�����(�t���[��)
HRESULT CAllocateHierarchy::AllocBone(LPD3DXFRAME _pFrame){
	if(_pFrame->pMeshContainer){
		if(FAILED(AllocBoneMatrix(_pFrame->pMeshContainer))){
			return E_FAIL;
		}
	}
	//�Z��t���[���̃{�[���s��m��
	if(_pFrame->pFrameSibling){
		if(FAILED(AllocBone(_pFrame->pFrameSibling))){
			return E_FAIL;
		}
	}
	//�q�t���[���̃{�[���s��m��
	if(_pFrame->pFrameFirstChild){
		if(FAILED(AllocBone(_pFrame->pFrameFirstChild))){
			return E_FAIL;
		}
	}
	return S_OK;
}
//�{�[���s��̊��蓖�ĂƏ�����(�R���e�i)
HRESULT CAllocateHierarchy::AllocBoneMatrix(LPD3DXMESHCONTAINER _pMeshContainer){
	CMeshContainer* pContainer = (CMeshContainer*)_pMeshContainer;
	//�X�L�����b�V����������ΏI��
	if(!pContainer->pSkinInfo) return S_OK;
	//�{�[�������擾
	DWORD dwBoneAnt = pContainer->pSkinInfo->GetNumBones();
	//�{�[���s�񐶐�
	pContainer->ppMatRoot = new D3DXMATRIX*[dwBoneAnt];
	for(DWORD i=0;i<dwBoneAnt;i++){
		//���[�g�t���[���̎q�t���[������
		CMeshFrame* pFrame = (CMeshFrame*)D3DXFrameFind(
			m_pFrameRoot,
			pContainer->pSkinInfo->GetBoneName(i));
		if(!pFrame)return E_FAIL;
		//�{�[���s��ɐݒ�
		pContainer->ppMatRoot[i] = &pFrame->CombinedTransformationMatrix;
	}
	return S_OK;
}

//���[���h���W�ݒ�
void CAllocateHierarchy::SetWorld(LPD3DXMATRIX _World){
	UpdateWorld(m_pFrameRoot,_World);
}
//�t���[�����̃��b�V�����ƂɃ��[���h�ϊ��s����X�V
void CAllocateHierarchy::UpdateWorld(LPD3DXFRAME _pFrameBase,LPD3DXMATRIX _pParentMatrix){
	
	CMeshFrame* pFrame = (CMeshFrame*)_pFrameBase;
	//�e�s�񂪂����
	if(_pParentMatrix){
		//�e�s��ƕϊ��s����|�����킹
		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix * (*_pParentMatrix);
	}
	else{
		//�����ꍇ
		//�ϊ��s��̂݃Z�b�g
		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
	}
	//�Z��t���[�����X�V
	if(pFrame->pFrameSibling){
		UpdateWorld(pFrame->pFrameSibling,_pParentMatrix);
	}
	//�q�t���[�����X�V
	if(pFrame->pFrameFirstChild){
		UpdateWorld(pFrame->pFrameFirstChild,&pFrame->CombinedTransformationMatrix);
	}
}

//���b�V���ǂݍ���
HRESULT CAllocateHierarchy::Load(LPDIRECT3DDEVICE9 _pDevice,std::string _FileName){
	//���b�V���ǂݍ���
	if(FAILED(D3DXLoadMeshHierarchyFromX(
		_FileName.c_str(),
		D3DXMESH_MANAGED,
		_pDevice,
		this,
		NULL,
		&m_pFrameRoot,
		&m_pAnimCtrl))){

		MessageBox(NULL,_T("failed to load X File"),NULL,MB_OK);
		return E_FAIL;
	}
	//�{�[���s��̃������m��
	if(FAILED(AllocBone(m_pFrameRoot))){
		MessageBox(NULL,_T("failed to alloc Bone Matrix"),NULL,MB_OK);
		return E_FAIL;
	}

	return S_OK;
}
//�K�w���b�V���`��
void CAllocateHierarchy::Draw(LPDIRECT3DDEVICE9 _pDevice){
	DrawFrame(_pDevice,m_pFrameRoot);
}

//�t���[���������_�����O
void CAllocateHierarchy::DrawFrame(LPDIRECT3DDEVICE9 _pDevice,LPD3DXFRAME _pFrameBase){
	CMeshFrame* pFrame = (CMeshFrame*)_pFrameBase;
	CMeshContainer* pContainer = (CMeshContainer*)pFrame->pMeshContainer;
	//�Ō�̊K�w�܂Ń��[�v
	while(pContainer){
		DrawContainer(_pDevice,pContainer,pFrame);
		//���̃��b�V���R���e�i��
		pContainer = (CMeshContainer*)pContainer->pNextMeshContainer;
	}
	//�Z��t���[���X�V
	if(pFrame->pFrameSibling){
		DrawFrame(_pDevice,pFrame->pFrameSibling);
	}
	//�Z��t���[���X�V
	if(pFrame->pFrameFirstChild){
		DrawFrame(_pDevice,pFrame->pFrameFirstChild);
	}
}
//�t���[�����̂��ꂼ��̃��b�V���������_�����O
void CAllocateHierarchy::DrawContainer(LPDIRECT3DDEVICE9 _pDevice,CMeshContainer* _pContainer,CMeshFrame* _pFrame){
	//�X�L�����b�V�����ǂ���
	if(_pContainer->pSkinInfo){
		LPD3DXBONECOMBINATION pBoneCombination = (LPD3DXBONECOMBINATION)_pContainer->pBoneBuf->GetBufferPointer();
		DWORD dwPrevBoneID = UINT_MAX;	//�O��̃{�[���ԍ�
		for(DWORD i=0;i<_pContainer->BoneNum;i++){
			DWORD dwBlendMatrixAnt = 0;
			for(DWORD j=0;j<_pContainer->Weight;j++){
				if(pBoneCombination[i].BoneId[j] != UINT_MAX){
					dwBlendMatrixAnt = j;
				}
			}
			//�X�N���[�����W�ɕϊ����邽�߂Ɏg���s��̌��ݒ�
			_pDevice->SetRenderState(D3DRS_VERTEXBLEND,dwBlendMatrixAnt);
			for(DWORD j=0;j<_pContainer->Weight;j++){
				DWORD matIndex = pBoneCombination[i].BoneId[j];
				if(matIndex != UINT_MAX){
					//�I�t�Z�b�g�s��ƃ{�[���s����|����
					D3DXMATRIX matStack = _pContainer->pMatOffset[matIndex] * (*_pContainer->ppMatRoot[matIndex]);
					//�s��X�^�b�N�Ɋi�[
					_pDevice->SetTransform(D3DTS_WORLDMATRIX(j),&matStack);
				}
			}
			//�}�e���A���Z�b�g
			_pDevice->SetMaterial(&_pContainer->pMaterials[pBoneCombination[i].AttribId].MatD3D);
			_pDevice->SetTexture(0,_pContainer->ppTexture[pBoneCombination[i].AttribId]);
			//�O��̃{�[���ԍ��ۑ�
			dwPrevBoneID = pBoneCombination[i].AttribId;
			//�`��
			_pContainer->MeshData.pMesh->DrawSubset(i);
		}
	}
	else{
		//�ʏ탁�b�V���̏ꍇ
		_pDevice->SetTransform(D3DTS_WORLD,&_pFrame->CombinedTransformationMatrix);
		for(DWORD i=0;i<_pContainer->NumMaterials;i++){
			//�}�e���A���Z�b�g
			_pDevice->SetMaterial(&_pContainer->pMaterials[i].MatD3D);
			_pDevice->SetTexture(0,_pContainer->ppTexture[i]);
			//�`��
			_pContainer->MeshData.pMesh->DrawSubset(i);
		}
	}
}
//�A�j���[�V�����R���g���[���擾
LPD3DXANIMATIONCONTROLLER CAllocateHierarchy::GetAnimCtrl(){
	return m_pAnimCtrl;
}

//�t���[���̃A�h���X�擾
LPD3DXFRAME CAllocateHierarchy::GetFrame()
{
	return m_pFrameRoot;
}
