#ifndef _ALLOCATEHIERARCHY_H_
#define _ALLOCATEHIERARCHY_H_

#include<d3dx9.h>
#include<string>

//アニメーション階層メッシュ読み込みクラス
class CAllocateHierarchy : public ID3DXAllocateHierarchy{
private:
	//メッシュフレーム構造体
	struct CMeshFrame : public D3DXFRAME{
		D3DXMATRIX CombinedTransformationMatrix;	//各フレームに影響する行列
	};
	//メッシュコンテ構造体
	struct CMeshContainer : public D3DXMESHCONTAINER{
		LPDIRECT3DTEXTURE9*		ppTexture;		//メッシュに貼り付けられるテクスチャ
		DWORD					BoneNum;		//ボーンの数
		DWORD					Weight;			//重みの個数
		LPD3DXBUFFER			pBoneBuf;		//ボーン情報
		D3DXMATRIX**			ppMatRoot;		//ボーンのワールド行列の先頭ポインタ
		D3DXMATRIX*				pMatOffset;		//ボーンのオフセット行列
	};
	LPD3DXFRAME					m_pFrameRoot;	//フレームのトップノード
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;	//アニメーションコントローラー
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
	//ワールド座標設定
	void SetWorld(LPD3DXMATRIX _World);
	//メッシュ読み込み
	HRESULT Load(LPDIRECT3DDEVICE9 _pDevice,std::string _FileName);
	//階層メッシュ描画
	void Draw(LPDIRECT3DDEVICE9 _pDevice);
	//アニメーションコントローラ取得
	LPD3DXANIMATIONCONTROLLER GetAnimCtrl();
	//フレームのアドレス取得
	LPD3DXFRAME GetFrame();

private:
	//フレーム内のメッシュごとにワールド変換行列を更新
	void UpdateWorld(LPD3DXFRAME _pFrameBase,LPD3DXMATRIX _pParentMatrix);
	//ボーン行列の割り当てと初期化(フレーム)
	HRESULT AllocBone(LPD3DXFRAME _pFrame);
	//ボーン行列の割り当てと初期化(コンテナ)
	HRESULT AllocBoneMatrix(LPD3DXMESHCONTAINER _pMeshContainer);
	//フレームをレンダリング
	void DrawFrame(LPDIRECT3DDEVICE9 _pDevice,LPD3DXFRAME _pFrameBase);
	//フレーム内のそれぞれのメッシュをレンダリング
	void DrawContainer(LPDIRECT3DDEVICE9 _pDevice,
		CMeshContainer* _pContainer,
		CMeshFrame* _pFrame);
};

#endif
