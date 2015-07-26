#ifndef _RENDER_MANAGE_H_
#define _RENDER_MANAGE_H_

#include "graphic.h"
#include "AllocateHierarchy.h"
#include "gameObject.h"

//	メッシュデータ
struct MESH_INFO
{
	LPD3DXMESH			pMesh;			//	メッシュデータの格納
	D3DMATERIAL9*		pMeshMaterials;	//	マテリアルのデータ
	LPDIRECT3DTEXTURE9*	pMeshTextures;	//	テクスチャのデータ
	DWORD				dwNumMaterials;	//	
};

//	カメラ情報
struct CAMERA_INFO
{
	D3DXVECTOR3 eyePos;		// 視点座標xyz
	D3DXVECTOR3 lookPos;	// 注視点座標xyz
	float		radian;		// 視点回転補正度
};

class CRenderManager
{
public:
	//	使用するメッシュファイルをIDとして列挙
	enum THING_ID
	{
		TH_BG1,

		TH_BOX_1,

		TH_BULLET,

		THING_MAX
	};

	//	使用するアニメーション付きメッシュファイルを
	//	IDとして列挙
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

	//	アニメーション付きメッシュデータ保存変数
	CAllocateHierarchy AllocateHierarchy[ AN_THING_MAX ];

private:
	MESH_INFO MeshInfo[ THING_MAX ];	//	メッシュデータ保存用メンバ変数

	CAMERA_INFO CameraInfo;		//	カメラ情報保存用メンバ変数

public:
	//	コンストラクタ
	CRenderManager();

public:
	//	xファイル読み込み
	//	(in)メッシュファイルのID，ファイルアドレス (out)読み込み成功→true	失敗→false
	bool LoadXFile( THING_ID _id, LPCSTR _xFileName );

	//	使用する全てのxファイル読み込み
	bool AllLoadXFile();

	//	カメラ情報初期化
	void CameraInit();

	/*
		ビルボード用の頂点描画
	*/
	void CRenderManager::BillboardingTransform( int _id, D3DXVECTOR3 _vecPosition );
	
	//	3D描画処理
	void Transform( int _id, D3DXVECTOR3 _vecPosition, D3DXVECTOR3 _vecRoate, D3DXVECTOR3 _vecScall );

	//	3Dアニメーション付き描画処理
	void AnimationTransform( int _id, D3DXVECTOR3 _vecPosition, D3DXVECTOR3 _vecRoate, D3DXVECTOR3 _vecScall );

	//	メッシュデータの解放
	void ReleaseMesh( int _id );

	//	全メッシュデータを解放
	void AllReleaseMesh();

	// スクリーン座標をワールド座標に変換
	D3DXVECTOR3* CalcScreenToWorld
	(
	   D3DXVECTOR3* pout,	
	   int Sx,				//	スクリーン座標内ｘ
	   int Sy,				//	スクリーン座標内ｙ
	   float fZ,			//	射影空間でのZ値（0～1）
	   int Screen_w,		//	スクリーンの横幅
	   int Screen_h,		//	スクリーンの縦幅
	   D3DXMATRIXA16* View,	//	ビュー行列
	   D3DXMATRIXA16* Prj		//	射影変換行列
	);

	//	スクリーン座標内のマウス座標をワールド座標に変換
	void MousePosTransform();

public:
	//	視点座標の取得
	D3DXVECTOR3 GetEyePos();
	
	//	注視点座標の取得
	D3DXVECTOR3 GetLookPos();
	
	//	視点回転補正度の取得
	float	GetRad();
};

#endif