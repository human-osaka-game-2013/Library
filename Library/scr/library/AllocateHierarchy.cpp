#include<tchar.h>

#include"AllocateHierarchy.h"
#include"lib_head.h"

//フレームオブジェクト生成
HRESULT CAllocateHierarchy::CreateFrame(LPCSTR _Name,LPD3DXFRAME* _ppNewFrame){
	*_ppNewFrame = 0;
	CMeshFrame* pFrame = new CMeshFrame();	//メッシュフレーム生成
	if(!pFrame)return E_FAIL;

	if( _Name != NULL ) {
		pFrame->Name = new char[strlen(_Name) + 1];	//フレーム名を文字数分メモリ確保
		if(!pFrame->Name)return E_FAIL;

		//各項目設定
		strcpy(pFrame->Name,_Name);	//フレーム数
	}
	else
	{
		_Name = "";
		pFrame->Name = new char[strlen(_Name) + 1];	//フレーム名を文字数分メモリ確保
		//各項目設定
		strcpy(pFrame->Name,_Name);	//フレーム数
		if(!pFrame->Name)return E_FAIL;

	}
	D3DXMatrixIdentity(&pFrame->TransformationMatrix);			//フレーム名
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);	//トランスフォーム行列
	pFrame->pMeshContainer		= NULL;							//メッシュコンテナ
	pFrame->pFrameFirstChild	= NULL;							//１番初めの子
	pFrame->pFrameSibling		= NULL;							//兄弟

	//新しいフレーム
	*_ppNewFrame = pFrame;

	return S_OK;
}

//メッシュコンテナ生成
HRESULT CAllocateHierarchy::CreateMeshContainer(
		LPCSTR						_Name,					//フレーム名
		CONST D3DXMESHDATA*			_pMeshData,				//メッシュデータ構造体へのポインタ
		CONST D3DXMATERIAL*			_pMaterials,			//メッシュに使用するマテリアル
		CONST D3DXEFFECTINSTANCE*	_pEffectInstances,		//メッシュに使用するエフェクトインスタンス
		DWORD						_NumMaterials,			//マテリアル数
		CONST DWORD*				_pAdjacency,			//メッシュ隣接性
		LPD3DXSKININFO				_pSkinInfo,				//スキンメッシュへのポインタ
		LPD3DXMESHCONTAINER*		_ppNewMeshContainer){	//生成したメッシュコンテナへのポインタ

	LPDIRECT3DDEVICE9 pDevice = NULL;		//デバイス
	LPD3DXMESH pMesh = _pMeshData->pMesh;	//メッシュ情報
	*_ppNewMeshContainer = NULL;
	DWORD dwBoneAnt = 0;					//ボーン数

	//メッシュコンテナ生成
	CMeshContainer* pMeshContainer = new CMeshContainer();
	if(!pMeshContainer)return E_FAIL;
	//ゼロクリア
	ZeroMemory(pMeshContainer,sizeof(CMeshContainer));

	//フレーム名
	pMeshContainer->MeshData = *_pMeshData;
	pMeshContainer->Name = new char[strlen(_Name) * 1];
	if(!pMeshContainer->Name)return E_FAIL;
	strcpy(pMeshContainer->Name,_Name);

	pMesh->GetDevice(&pDevice);			//メッシュからデバイス取得
	//メッシュに含まれる面の数を取得
	DWORD faceNum = pMesh->GetNumFaces();

	//法線がない場合
	if(!(pMesh->GetFVF() & D3DFVF_NORMAL)){
		//法泉情報が無いので追加
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		//FVFコードを使用して、メッシュのコピー生成
		if(FAILED(pMesh->CloneMeshFVF(
			pMesh->GetOptions(),
			pMesh->GetFVF() | D3DFVF_NORMAL,
			pDevice,
			&pMeshContainer->MeshData.pMesh))){
				//失敗
				return E_FAIL;
		}
		pMesh = pMeshContainer->MeshData.pMesh;
		//メッシュに含まれる各頂点の法泉の向きを計算し、設定
		D3DXComputeNormals(pMesh,NULL);
	}
	//法線がある場合
	else{
		//法線がある場合
		pMeshContainer->MeshData.pMesh = pMesh;
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		//参照カウンタをインクリメント
		pMesh->AddRef();
	}

	//マテリアル設定
	pMeshContainer->NumMaterials	= max(1,_NumMaterials);									//メッシュに含まれるマテリアル数
	pMeshContainer->pMaterials		= new D3DXMATERIAL[pMeshContainer->NumMaterials];		//メッシュマテリアル配列
	pMeshContainer->ppTexture		= new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];	//テクスチャのポインタへのポインタ
	pMeshContainer->pAdjacency		= new DWORD[faceNum * 3];								//メッシュの三角形ごとに３つの隣接情報がある
	if(!pMeshContainer->pAdjacency || !pMeshContainer->pMaterials)return E_FAIL;

	//隣接情報を代入
	memcpy(pMeshContainer->pAdjacency,_pAdjacency,sizeof(DWORD) * faceNum * 3);
	//テクスチャ情報を安全のために初期化
	memset(pMeshContainer->ppTexture,0,sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	//マテリアル情報格納
	if(_NumMaterials > 0){
		//マテリアルがある場合
		memcpy(pMeshContainer->pMaterials,_pMaterials,sizeof(D3DXMATERIAL));

		for(DWORD i=0;i<_NumMaterials;i++){
			//テクスチャがあれば
			if(pMeshContainer->pMaterials[i].pTextureFilename){
				char strTextureName[MAX_PATH];
				strcpy(strTextureName,pMeshContainer->pMaterials[i].pTextureFilename);
				//テクスチャ
				if(FAILED(D3DXCreateTextureFromFileA(
					pDevice,
					strTextureName,
					&pMeshContainer->ppTexture[i]))){
						pMeshContainer->ppTexture[i] = NULL;
				}
				//重複読み込み防止
				pMeshContainer->pMaterials[i].pTextureFilename = NULL;
			}
		}
	}
	else{
		//マテリアルが無い場合
		pMeshContainer->pMaterials[0].pTextureFilename = NULL;
		memset(&pMeshContainer->pMaterials[0].MatD3D,0,sizeof(D3DMATERIAL9));

		//テクスチャが貼られていないメッシュ表示のために光沢指定
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.a = pMeshContainer->pMaterials[0].MatD3D.Diffuse.a;
	}

	
	//エフェクトデータの確認------------------------
	const D3DXEFFECTINSTANCE *pEI = _pEffectInstances;  // 長いので
	pMeshContainer->pEffects = new D3DXEFFECTINSTANCE;
	if( pEI->pEffectFilename != NULL )
		strcpy( pMeshContainer->pEffects->pEffectFilename, pEI->pEffectFilename );
	else
		pMeshContainer->pEffects->pEffectFilename = NULL;

	pMeshContainer->pEffects->NumDefaults = pEI->NumDefaults;
	pMeshContainer->pEffects->pDefaults = new D3DXEFFECTDEFAULT[pEI->NumDefaults];
	
	D3DXEFFECTDEFAULT *pDIST = pEI->pDefaults;	// コピー元
	D3DXEFFECTDEFAULT *pCOPY = pMeshContainer->pEffects->pDefaults;	// コピー先
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
		//スキンメッシュがある
		pMeshContainer->pSkinInfo = _pSkinInfo;
		//参照カウンタインクリメント
		_pSkinInfo->AddRef();

		//ボーン数取得
		dwBoneAnt = _pSkinInfo->GetNumBones();
		pMeshContainer->pMatOffset = new D3DXMATRIX[dwBoneAnt];

		//ボーン行列コピー
		for(DWORD i=0;i<dwBoneAnt;i++){
			memcpy(
				&pMeshContainer->pMatOffset[i],
				pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i),
				sizeof(D3DXMATRIX));
		}
		//頂点単位のブレンドの重みとボーンを適用した新しいメッシュを生み出す
		if(FAILED(pMeshContainer->pSkinInfo->ConvertToBlendedMesh(
			pMesh,							//メッシュ
			NULL,
			pMeshContainer->pAdjacency,		//メッシュの隣接情報
			NULL,NULL,NULL,
			&pMeshContainer->Weight,		//ボーンの重み
			&pMeshContainer->BoneNum,		//ボーン数
			&pMeshContainer->pBoneBuf,		//ボーンテーブル
			&pMeshContainer->MeshData.pMesh	//新しいメッシュ
			))){
				return E_FAIL;
		}
		SAFE_RELEASE(pMesh);

	}
	//新しく生成したメッシュコンテナを呼び出し側にコピー
	*_ppNewMeshContainer = pMeshContainer;

	return S_OK;
}

//フレーム破棄
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

//メッシュコンテナ破棄
HRESULT CAllocateHierarchy::DestroyMeshContainer( THIS_ LPD3DXMESHCONTAINER _pMeshContainerToFree){

	//自身で作った構造体のメンバを解放するために型を変更
	CMeshContainer* pContainer = (CMeshContainer*)_pMeshContainerToFree;
	
	if( !pContainer->Name ){
		NULL_ARRAY_DELETE(pContainer->Name);
	}
	else{
		pContainer->Name = NULL;
		NULL_ARRAY_DELETE(pContainer->Name);
	}
	SAFE_RELEASE(pContainer->MeshData.pMesh);
	
	//テクスチャがあれば
	if(pContainer->ppTexture){
		for(DWORD i=0;i<pContainer->NumMaterials;i++){
			NULL_ARRAY_DELETE(pContainer->pMaterials[i].pTextureFilename);
			SAFE_RELEASE(pContainer->ppTexture[i]);
		}
	}

	NULL_ARRAY_DELETE(pContainer->pMaterials);

	// エフェクト
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

	//コンテナ
	SAFE_DELETE(pContainer);
	//delete pContainer;

	return S_OK;
}


//ボーン行列の割り当てと初期化(フレーム)
HRESULT CAllocateHierarchy::AllocBone(LPD3DXFRAME _pFrame){
	if(_pFrame->pMeshContainer){
		if(FAILED(AllocBoneMatrix(_pFrame->pMeshContainer))){
			return E_FAIL;
		}
	}
	//兄弟フレームのボーン行列確保
	if(_pFrame->pFrameSibling){
		if(FAILED(AllocBone(_pFrame->pFrameSibling))){
			return E_FAIL;
		}
	}
	//子フレームのボーン行列確保
	if(_pFrame->pFrameFirstChild){
		if(FAILED(AllocBone(_pFrame->pFrameFirstChild))){
			return E_FAIL;
		}
	}
	return S_OK;
}
//ボーン行列の割り当てと初期化(コンテナ)
HRESULT CAllocateHierarchy::AllocBoneMatrix(LPD3DXMESHCONTAINER _pMeshContainer){
	CMeshContainer* pContainer = (CMeshContainer*)_pMeshContainer;
	//スキンメッシュが無ければ終了
	if(!pContainer->pSkinInfo) return S_OK;
	//ボーン数を取得
	DWORD dwBoneAnt = pContainer->pSkinInfo->GetNumBones();
	//ボーン行列生成
	pContainer->ppMatRoot = new D3DXMATRIX*[dwBoneAnt];
	for(DWORD i=0;i<dwBoneAnt;i++){
		//ルートフレームの子フレーム検索
		CMeshFrame* pFrame = (CMeshFrame*)D3DXFrameFind(
			m_pFrameRoot,
			pContainer->pSkinInfo->GetBoneName(i));
		if(!pFrame)return E_FAIL;
		//ボーン行列に設定
		pContainer->ppMatRoot[i] = &pFrame->CombinedTransformationMatrix;
	}
	return S_OK;
}

//ワールド座標設定
void CAllocateHierarchy::SetWorld(LPD3DXMATRIX _World){
	UpdateWorld(m_pFrameRoot,_World);
}
//フレーム内のメッシュごとにワールド変換行列を更新
void CAllocateHierarchy::UpdateWorld(LPD3DXFRAME _pFrameBase,LPD3DXMATRIX _pParentMatrix){
	
	CMeshFrame* pFrame = (CMeshFrame*)_pFrameBase;
	//親行列があれば
	if(_pParentMatrix){
		//親行列と変換行列を掛け合わせ
		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix * (*_pParentMatrix);
	}
	else{
		//無い場合
		//変換行列のみセット
		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
	}
	//兄弟フレームを更新
	if(pFrame->pFrameSibling){
		UpdateWorld(pFrame->pFrameSibling,_pParentMatrix);
	}
	//子フレームを更新
	if(pFrame->pFrameFirstChild){
		UpdateWorld(pFrame->pFrameFirstChild,&pFrame->CombinedTransformationMatrix);
	}
}

//メッシュ読み込み
HRESULT CAllocateHierarchy::Load(LPDIRECT3DDEVICE9 _pDevice,std::string _FileName){
	//メッシュ読み込み
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
	//ボーン行列のメモリ確保
	if(FAILED(AllocBone(m_pFrameRoot))){
		MessageBox(NULL,_T("failed to alloc Bone Matrix"),NULL,MB_OK);
		return E_FAIL;
	}

	return S_OK;
}
//階層メッシュ描画
void CAllocateHierarchy::Draw(LPDIRECT3DDEVICE9 _pDevice){
	DrawFrame(_pDevice,m_pFrameRoot);
}

//フレームをレンダリング
void CAllocateHierarchy::DrawFrame(LPDIRECT3DDEVICE9 _pDevice,LPD3DXFRAME _pFrameBase){
	CMeshFrame* pFrame = (CMeshFrame*)_pFrameBase;
	CMeshContainer* pContainer = (CMeshContainer*)pFrame->pMeshContainer;
	//最後の階層までループ
	while(pContainer){
		DrawContainer(_pDevice,pContainer,pFrame);
		//次のメッシュコンテナへ
		pContainer = (CMeshContainer*)pContainer->pNextMeshContainer;
	}
	//兄弟フレーム更新
	if(pFrame->pFrameSibling){
		DrawFrame(_pDevice,pFrame->pFrameSibling);
	}
	//兄弟フレーム更新
	if(pFrame->pFrameFirstChild){
		DrawFrame(_pDevice,pFrame->pFrameFirstChild);
	}
}
//フレーム内のそれぞれのメッシュをレンダリング
void CAllocateHierarchy::DrawContainer(LPDIRECT3DDEVICE9 _pDevice,CMeshContainer* _pContainer,CMeshFrame* _pFrame){
	//スキンメッシュかどうか
	if(_pContainer->pSkinInfo){
		LPD3DXBONECOMBINATION pBoneCombination = (LPD3DXBONECOMBINATION)_pContainer->pBoneBuf->GetBufferPointer();
		DWORD dwPrevBoneID = UINT_MAX;	//前回のボーン番号
		for(DWORD i=0;i<_pContainer->BoneNum;i++){
			DWORD dwBlendMatrixAnt = 0;
			for(DWORD j=0;j<_pContainer->Weight;j++){
				if(pBoneCombination[i].BoneId[j] != UINT_MAX){
					dwBlendMatrixAnt = j;
				}
			}
			//スクリーン座標に変換するために使う行列の個数設定
			_pDevice->SetRenderState(D3DRS_VERTEXBLEND,dwBlendMatrixAnt);
			for(DWORD j=0;j<_pContainer->Weight;j++){
				DWORD matIndex = pBoneCombination[i].BoneId[j];
				if(matIndex != UINT_MAX){
					//オフセット行列とボーン行列を掛ける
					D3DXMATRIX matStack = _pContainer->pMatOffset[matIndex] * (*_pContainer->ppMatRoot[matIndex]);
					//行列スタックに格納
					_pDevice->SetTransform(D3DTS_WORLDMATRIX(j),&matStack);
				}
			}
			//マテリアルセット
			_pDevice->SetMaterial(&_pContainer->pMaterials[pBoneCombination[i].AttribId].MatD3D);
			_pDevice->SetTexture(0,_pContainer->ppTexture[pBoneCombination[i].AttribId]);
			//前回のボーン番号保存
			dwPrevBoneID = pBoneCombination[i].AttribId;
			//描画
			_pContainer->MeshData.pMesh->DrawSubset(i);
		}
	}
	else{
		//通常メッシュの場合
		_pDevice->SetTransform(D3DTS_WORLD,&_pFrame->CombinedTransformationMatrix);
		for(DWORD i=0;i<_pContainer->NumMaterials;i++){
			//マテリアルセット
			_pDevice->SetMaterial(&_pContainer->pMaterials[i].MatD3D);
			_pDevice->SetTexture(0,_pContainer->ppTexture[i]);
			//描画
			_pContainer->MeshData.pMesh->DrawSubset(i);
		}
	}
}
//アニメーションコントローラ取得
LPD3DXANIMATIONCONTROLLER CAllocateHierarchy::GetAnimCtrl(){
	return m_pAnimCtrl;
}

//フレームのアドレス取得
LPD3DXFRAME CAllocateHierarchy::GetFrame()
{
	return m_pFrameRoot;
}
