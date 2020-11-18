//=============================================================================
//
// ジョイパッドの処理[controller.h]
// Author : 後藤慎之助
//
//=============================================================================
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#define _CRT_SECURE_NO_WARNINGS_

//=============================================================================
// インクルードファイル
//=============================================================================
#include"main.h"

//=============================================================================
// 外部変数
//=============================================================================
extern LPDIRECTINPUT8		pDInput;
extern LPDIRECTINPUTDEVICE8	pDIKeyboard;
extern BYTE					diKeyState[256];
extern LPDIRECTINPUTDEVICE8	pDIJoypad;
extern DWORD				diJoyState;
extern LPDIRECTINPUTDEVICE8	pDIMouse;
extern DIMOUSESTATE			diMouseState;

//=============================================================================
//マクロ定義
//=============================================================================
#define BUTTON_UP     (0)	    //十字キー上
#define BUTTON_DOWN   (18000)	//十字キー下
#define BUTTON_LEFT   (27000)	//十字キー左
#define BUTTON_RIGHT  (9000)	//十字キー右

#define CROSSZONE (4500)        //十字キーの許容範囲
//
//#define SAFE_RELEASE(x)	if(x){x->Release();x=NULL;} //開放処理を簡単にする
//

//=============================================================================
//構造体定義
//=============================================================================
typedef enum
{
	BUTTON_X = 0,//X
	BUTTON_Y,//Y
	BUTTON_A,//X
	BUTTON_B,//Y
	BUTTON_L1,//LB
	BUTTON_R1,//RB
	BUTTON_L2,//BACK
	BUTTON_R2,//START
	BUTTON_L3,	//L押し込み
	BUTTON_R3,//R押し込み
	BUTTON_BACK,		//
	BUTTON_START,		//
	BUTTON_M,
	MAX_BUTTON
}BUTTON;//ボタンの数

		//-----------------------------------------------------------------------------
		// プロトタイプ宣言 function-prototypes
		//-----------------------------------------------------------------------------
bool InitDInput(HINSTANCE);
HRESULT InitJoypad(HINSTANCE hInstance, HWND hWnd);
void UpdateJoypad(void);
void ReleaseDInput(void);
bool GetJoypadPress(int nButton);
bool GetJoypadTrigger(int nButton);
bool GetJoypadRelease(int nButton);
DIJOYSTATE2 GetController(void);
#endif
