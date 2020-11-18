//================================================================
//
//DirectXシューティングゲーム
//Author:鈴木聖大
//
//================================================================

//****************************************************************
//インクルードファイル
//****************************************************************
#include "main.h"		// ヘッダファイルの読み込み
#include "player.h"
#include "bg.h"
#include "input.h"
#include "explosion.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "tutorial.h"
#include "timer.h"

//****************************************************************
// マクロ定義
//****************************************************************
#define CLASS_NAME "WindowClass"	// ウインドウクラスの名前
#define WINDOW_NAME "ちゃりそ"		// ウインドウの名前(キャプション)

//****************************************************************
// プロトタイプ宣言
//****************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//****************************************************************
// グローバル変数
//****************************************************************
LPDIRECT3D9 g_pD3D = NULL;					// Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		// Direct3Dデバイスへのポインタ(描画に必要)
MODE g_mode = MODE_TITLE;//モード

//****************************************************************
// メイン関数
//****************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),			// WNDCLASSEXのメモリサイズを指定
		CS_CLASSDC,					// 表示するウインドウのスタイルを設定
		WindowProc,					// ウインドウプロシージャのアドレス(関数名)を指定
		0,							// 通常は使用しないので"0"を指定
		0,							// 通常は使用しないので"0"を指定
		hInstance,					// WinMainのパラメータのインスタンスハンドルを設定
		LoadIcon(NULL,IDI_APPLICATION),		// 使用するアイコンを指定(Windowsが持っているアイコンを使うならNULL)
		LoadCursor(NULL, IDC_ARROW),		// マウスカーソルを指定
		(HBRUSH)(COLOR_WINDOW + 1),			// ウインドウのクライアント領域の背景色を設定
		NULL,						// Windowにつけるメニューを設定
		CLASS_NAME,					// ウインドウクラスの名前
		LoadIcon(NULL, IDI_APPLICATION),	// 小さいアイコンの設定された場合の情報を記述
	};
	HWND hWnd;					// ウインドウハンドル（識別子）
	MSG msg;					// メッセージを格納する変数
	RECT rect =
	{
		WINDOW_POS_X,
		WINDOW_POS_Y,
		(WINDOW_POS_X + SCREEN_WIDTH),
		(WINDOW_POS_Y + SCREEN_HEIGHT)
	};

	// 以下の4行はアニメーションを入れるときに重要
	DWORD dwCurrentTime;		// 現在時刻
	DWORD dwExecLastTime;		// 最後に処理した時刻



	// ウインドウクラスの登録
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウインドウの作成
	hWnd = CreateWindowEx(0,		// 拡張ウインドウスタイル
		CLASS_NAME,					//ウインドウクラスの名前
		WINDOW_NAME,				// ウインドウの名前
		WS_OVERLAPPEDWINDOW,		// ウインドウのスタイル
		CW_USEDEFAULT,				// ウインドウの左上X座標（ここに任意の値を入れると…）
		CW_USEDEFAULT,				// ウインドウの左上Y座標（ここに任意の値を入れると…）
		SCREEN_WIDTH,				// ウインドウの幅
		SCREEN_HEIGHT,				// ウインドウの高さ
		NULL,						// 親ウインドウのハンドル
		NULL,						// メニューハンドルまたは子ウインドウID
		hInstance,					// インスタンスハンドル
		NULL);						// ウインドウ作成データ

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();	// 現在の時刻取得

									// 初期化処理(ウインドウを作成してから行う)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// ウインドウの表示（必ずセットで書く）
	ShowWindow(hWnd, nCmdShow);		// 指定されたウインドウの表示状態を指定(ウインドウを表示)
	UpdateWindow(hWnd);				// ウインドウの状態を直ちに反映(ウインドウのクライアント領域を更新

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{	// Windowsの処理
			if (msg.message == WM_QUIT)
			{	// WM_QUITメッセージが来たらループを抜ける
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{	// DirectXの処理	アニメーションに必要
			dwCurrentTime = timeGetTime();		// システム時刻を取得
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))			// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;		// 処理した時刻を保存
				// 更新処理
				Update();
				// 描画処理
				Draw();
			}
		}
	}
	// 終了処理
	Uninit();

	// ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return (int)msg.wParam;
}

//****************************************************************
// ウインドウプロシージャ
//****************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:		// ウインドウの破棄
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:		// キーを押したときの処理
		switch (wParam)
		{
		case VK_ESCAPE:

			DestroyWindow(hWnd);	// ウインドウ破棄

		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);		// 規定処理の提供
}

//****************************************************************
// 初期化処理
// hInstance : インスタンスのハンドル
// hWnd      : ウインドウのハンドル
// bWindow   : ウインドウモードにするかどうか
//****************************************************************
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;				// ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;		// プレゼンテーションパラメータ
										// Direct3Dオブジェクト生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{

		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{

			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{

				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面(左回り)をカリング
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// 透明度を使うか
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// aデスティネーションカラー

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//タイトルの初期化
	SetMode(MODE_TITLE);
	InitTitle();
	InitGame();
	// キーボードの初期化
	InitKeyboard(hInstance, hWnd);
	//リザルトの初期化
	InitResult();

	return S_OK;
}

//****************************************************************
// 終了処理
//****************************************************************
void Uninit(void)
{
	if (g_pD3DDevice != NULL)
	{	// Direct3Dデバイスの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	//タイトル画面の終了処理
	UninitTitle();
	//チュートリアル画面の終了処理
	UninitTutorial();
	//ゲーム画面の終了処理
	UninitGame();
	//リザルト画面の終了処理
	UninitResult();
}

//****************************************************************
// 更新処理
//****************************************************************
void Update(void)
{
	// 各種オブジェクトの更新処理
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE:	//タイトル画面の更新
		UpdateTitle();
		break;
	case MODE_TUTORIAL: //チュートリアル画面の更新
		UpdateTutorial();
		break;
	case MODE_GAME:		//ゲーム画面の更新
		UpdateGame();
		break;
	case MODE_RESULT:	//リザルト画面の更新
		UpdateResult();
		break;
	}
}

//****************************************************************
// 描画処理
//****************************************************************
void Draw(void)
{
	// バッファ＆Zバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	// Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:	//タイトル画面の更新
			DrawTitle();
			break;

		case MODE_TUTORIAL: //チュートリアル画面の更新
			DrawTutorial();
			break;

		case MODE_GAME:		//ゲーム画面の更新
			DrawGame();
			break;

		case MODE_RESULT:	//リザルト画面の更新
			DrawResult();
			break;
		}
		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}
	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	// DirectXでの描画処理
}

//****************************************************************
// デバイスの取得
//****************************************************************
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//****************************************************************
//
//****************************************************************
MODE GetMode(void)
{
	return g_mode;
}

//****************************************************************
//
//****************************************************************
void SetMode(MODE mode)
{
	g_mode = mode;

	switch (g_mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_TUTORIAL:
		InitTutorial();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	}
}