#pragma once
//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _PLAYER_H_			// 2重インクルードファイル
#define _PLAYER_H_

//=====================================================
// マクロ定義
//=====================================================
#define VALUE_MOVE (10.0f)	//ポリゴンの移動量
#define PLAYER_POS_X (150)
#define PLAYER_POS_Y (360)

//=====================================================
//構造体定義
//=====================================================
typedef enum
{
	PLAYERSTATE_NOMAL = 0,	//通常
	PLAYERSTATE_DAMAGE,		//ダメージ
	PLAYERSTATE_MAX			//状態の最大数
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	int nType;			//種類
	bool bUse;			//使用しているかどうか
	int nLife;			//体力
	PLAYERSTATE state;	//状態
	int nCounterState;	//状態のカウンタ
	int nCounterBullet;	//弾を撃つ間隔
}PLAYER;

//=====================================================
// プロトタイプ宣言
//=====================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
void HitPlayer(int nDamage);

#endif