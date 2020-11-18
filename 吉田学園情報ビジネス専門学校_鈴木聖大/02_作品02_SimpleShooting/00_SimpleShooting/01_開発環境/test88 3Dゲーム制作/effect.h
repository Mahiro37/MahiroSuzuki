//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#define _CRT_SECURE_NO_WARNINGS

//================================================
//インクルードファイル
//================================================
#include "main.h"

//================================================
// マクロ定義
//================================================
#define MAX_EFFECT (1)
#define VALUE_MOVE (10.0f)		//ポリゴンの移動量
#define EFFECT_SIZE_X (50)		// X座標の大きさ
#define EFFECT_SIZE_Y (50)		// Y座標の大きさ
#define	EFFECT_POS_X (180) 
#define	EFFECT_POS_Y (180) 

//================================================
//構造体定義
//================================================
typedef enum
{
	EFFECTTYPE_GAMECLEAR,		//ゲームクリア
	EFFECTTYPE_GAMEOVER,		//ゲームオーバー
	EFFECTTYPE_002,				//
	EFFECTTYPE_003,				//
	EFFECTTYPE_004,				//
	EFFECTTYPE_005,				//
	EFFECTTYPE_MAX
}EFFECTTYPE;//エフェクトの種類

typedef struct
{
	D3DXVECTOR3 pos;	//現在の位置
	D3DXVECTOR3 posOld; //1F前の位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 size;   //大きさ
	D3DXMATRIX mtxWorld;//行列計算用
	//BULLETTYPE type;	//種類
	bool bUse;			//使用しているかどうか
}EFFECT;

//================================================
//プロトタイプ宣言
//================================================
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size);

#endif