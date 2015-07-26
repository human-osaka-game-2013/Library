#include "SceneManage.h"
#include "RenderManage.h"
#include "main.h"
#include "Window.h"
#include "AllInput.h"

//----------------------------------------------------------------
//	プロトタイプ宣言
//----------------------------------------------------------------
// Direct3Dの初期化
// 第1引数：ウインドハンドル
HRESULT InitD3d ( HWND );

//	ウインドウ生成
int CreateWindowProcess ( HINSTANCE, HWND* );

//ダイレクトインプットの初期化関数
HRESULT InitDinput( HWND );

//	マウス座標の取得と移動量を決める。
//	引数1：ウインドウハンドル
void CursorSet( HWND );

// 使用している全てのテクスチャの解放
void ReleaseAllTexture ();

//	デバイスの解放
void FreeDx ( bool );

//----------------------------------------------------------------------
//
//	メインルーチン
//
//----------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR IpCmdLine, int nCmdShow )
{
	HWND	hWnd;

	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(87);

	MSG msg;
	
	CreateWindowProcess ( hInstance, &hWnd );

	// Direct3D周りの初期化処理
	if ( FAILED ( InitD3d ( hWnd ) ) ) return 0;
	
	//	キーの初期化
	if ( FAILED ( InitDinput ( hWnd ) ) ) return 0;

	// サウンドの初期化
	//InitXAudio2();

	//	シーン管理オブジェクトの生成
	CSceneManager* pSceneManage = new CSceneManager( CSceneManager::BATTLE );

	//	3D描画の管理オブジェクトの生成
	CRenderManager* pRenderManage = pSceneManage -> GetRndManager();

	pRenderManage -> CameraInit();

	//	使用する全ての画像を読み込み
	if ( false == AllLoadTexture () )	return 0;
	//	使用する全てのxファイル読み込み
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
				//	マウス座標＆移動量の更新
				CursorSet( hWnd );
				//	キー入力のチェック
				AllKeyCheck();
				//	マウスクリックの入力チェック
				AllButtonCheck();

				//	ジョイスティックの情報更新
				CXInput::UpdateStick();

				//	ゲームメイン関数
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
