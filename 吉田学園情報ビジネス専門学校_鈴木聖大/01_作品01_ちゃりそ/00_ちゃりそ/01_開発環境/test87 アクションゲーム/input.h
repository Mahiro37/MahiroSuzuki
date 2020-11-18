#pragma once
//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#define _CRT_SECURE_NO_WARNINGS

//================================================
//インクルードファイル
//================================================
#include "main.h"

//================================================
//プロトタイプ宣言
//================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
//bool GetKeyboardRelease(int nKey);

#endif