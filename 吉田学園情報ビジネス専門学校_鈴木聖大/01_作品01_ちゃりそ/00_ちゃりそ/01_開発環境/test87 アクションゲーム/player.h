#pragma once
//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _PLAYER_H_			// 2重インクルードファイル
#define _PLAYER_H_

#define _CRT_SECURE_NO_WARNINGS

//================================================
//インクルードファイル
//================================================
#include "main.h" 

//=====================================================
//マクロ定義
//=====================================================
#define	PLAYER_SIZE (45) //プレイヤーのサイズ
#define PLAYER_LIFE (1) //プレイヤーの寿命
#define	PLAYER_POS_X (200) //プレイヤーの初期位置
#define	PLAYER_POS_Y (200) //プレイヤーの初期位置

//=====================================================
//構造体定義
//=====================================================
//敵の状態
typedef enum
{
	PLAYERSTATE_NORMAL = 0,//通常
	PLAYERSTATE_DAMAGE,//ダメージ
	PLAYERSTATE_MAX//状態の最大数
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;//現在の位置
	D3DXVECTOR3 posOld;//前回の位置
	D3DXVECTOR3 move;//移動量
	PLAYERSTATE state;
	bool bUse;//使用しているかどうか
	int nLife;//体力
	bool bJump;//ジャンプ中かどうか
	int nCounterState;//状態のカウンタ
}PLAYER;

//=====================================================
// プロトタイプ宣言
//=====================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
PLAYER *GetPlayer(void);

#endif