//================================================
//3Dゲーム制作
//Author:鈴木聖大
//================================================
#ifndef MAIN_H_
#define MAIN_H_

#define CRT_SECURE_NO_WARNINGS

//=====================================================
// インクルードファイル
//=====================================================
#include <windows.h>
//#include <stdlib.h>
//#include <time.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	// 警告対処用("dinput.h"の直前に定義)
#include <dinput.h>

//================================================
//マクロ定義
//================================================
#define SCREEN_WIDTH (1280)		// ウインドウの幅
#define SCREEN_HEIGHT (720)		// ウインドウの高さ
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define NUM_VERTEX (4)
#define NUM_POLYGON (2)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)//頂点座標・カラー・テクスチャ座標
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)//座標・法線・カラー

//=====================================================
// ライブラリのリンク
//=====================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")		// 入力処理に必要

//================================================
//構造体定義
//================================================
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
	float rhw;			// 座標
}VERTEX_3D;

typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			// 座標
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
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