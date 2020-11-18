#pragma once
//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#define _CRT_SECURE_NO_WARNINGS
#include "main.h"

//================================================
//マクロ定義
//================================================
#define MAX_ENEMY (3)//敵の最大数
#define MAX_ENEMY_SIZE (100) //敵のサイズ

//================================================
//列挙型定義
//================================================
//敵の状態
typedef enum
{
	ENEMYSTATE_NOMAL = 0,	//通常
	ENEMYSTATE_DAMAGE,		//ダメージ
	ENEMYSTATE_MAX			//状態の最大数
}ENEMYSTATE;

//================================================
//構造体定義
//================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	int nType;			//種類
	bool bUse;			//使用しているかどうか
	int nLife;			//体力
	ENEMYSTATE state;	//状態
	int nCounterState;	//状態のカウンタ
	int nCounterBullet;	//弾を撃つ間隔
}ENEMY;


//================================================
//プロトタイプ宣言
//================================================
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType, int nLife);
ENEMY*GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif