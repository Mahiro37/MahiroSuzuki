//================================================================
//
//DirectXシューティングゲーム
//Author:鈴木聖大
//
//================================================================

//****************************************************************
//インクルードファイル
//****************************************************************
#include "input.h"

//****************************************************************
// マクロ定義
//****************************************************************
#define NUM_KEY_MAX (256)			// キー最大数

//****************************************************************
// グローバル変数
//****************************************************************
LPDIRECTINPUT8 g_pInput = NULL;					// DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		// 入力デバイス(キーボード)へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];					// キーボードの入力情報ワーク
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//キーボードのトリガー情報
BYTE g_aKeyStateRelease[NUM_KEY_MAX];			//キーボードのリリース情報

//****************************************************************
// キーボードの初期化
//****************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputオブジェクトの作成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	// 入力デバイス(キーボード)の作成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	// データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	// 協調モードを設定(フォアグラウンド＆非排他モード)
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//****************************************************************
// キーボードの終了処理
//****************************************************************
void UninitKeyboard(void)
{
	// 入力デバイス(キーボード)の開放
	if (g_pDevKeyboard != NULL)
	{
		// キーボードへのアクセス権を開放(入力制御終了)
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	// DirectInputオブジェクトの開放
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//****************************************************************
// キーボードの更新処理
//****************************************************************
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		// キーボードの入力情報
	int nCntKey;						// ローカル変数

	// デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] =
				(g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];

			g_aKeyState[nCntKey] = aKeyState[nCntKey];// キープレス情報を保存

			g_aKeyStateRelease[nCntKey] =
				(g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&~aKeyState[nCntKey];

			g_aKeyState[nCntKey] = aKeyState[nCntKey];// キープレス情報を保存
		}
	}
	// キーボードの更新処理
	else
	{
		// キーボードへのアクセス権を取得
		g_pDevKeyboard->Acquire();
	}
}


//****************************************************************
// キーボードのプレス状態を取得
//****************************************************************
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//****************************************************************
// キーボードのトリガー状態を取得
//****************************************************************
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}