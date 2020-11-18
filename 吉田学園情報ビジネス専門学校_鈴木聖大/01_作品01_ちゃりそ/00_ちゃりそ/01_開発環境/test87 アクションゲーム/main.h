#pragma once
//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS

//=====================================================
// インクルードファイル
//=====================================================
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	// 警告対処用("dinput.h"の直前に定義)
#include <dinput.h>

//=====================================================
// マクロ定義
//=====================================================
#define SCREEN_WIDTH (1280)		// ウインドウの幅
#define SCREEN_HEIGHT (720)		// ウインドウの高さ
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define NUM_VERTEX (4)			// 頂点数
#define NUM_POLYGON (2)			// ポリゴン (三角形の数)
#define POLYGON_SIZE_X (150)
#define POLYGON_SIZE_Y (150)
#define MAX_TYPE_ENEMY (128)
#define MAX_BLOCK (10)
#define BLOCK_SIZE_X_0 (2500)
#define BLOCK_SIZE_Y_0 (300)
#define BLOCK_SIZE_X_1 (600)
#define BLOCK_SIZE_Y_1 (300)
#define BLOCK_SIZE_X_2 (200)
#define BLOCK_SIZE_Y_2 (1000)
#define BLOCK_POS_X (2000)
#define BLOCK_POS_Y (650)
#define PLAYER_WIDTH_COLLISION POLYGON_SIZE_X
#define PLAYER_HEIGHT_COLLISION POLYGON_SIZE_Y
// 頂点フォーマット(頂点座標[2D]/頂点カラー/テクスチャ座標)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//=====================================================
// ライブラリのリンク
//=====================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")		// 入力処理に必要

//=====================================================
// 構造体定義
//=====================================================
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
}VERTEX_2D;

//モードの選択
typedef enum
{
	MODE_TITLE = 0,//タイトル画面
	MODE_TUTORIAL,//チュートリアル画面
	MODE_GAME,//ゲーム画面
	MODE_RESULT,//リザルト画面
	MODE_MAX
}MODE;

//=====================================================
// プロトタイプ宣言
//=====================================================
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
#endif