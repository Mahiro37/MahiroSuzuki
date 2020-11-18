//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//================================================
//インクルードファイル
//================================================
#include "main.h"

//=====================================================
//マクロ定義
//=====================================================
#define MAX_BULLET (128)//弾の最大数
#define BULLET_SIZE (50)

//================================================
//構造体定義
//================================================
//敵の状態
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//プレイヤーの弾
	BULLETTYPE_ENEMY,		//敵の弾
	BULLETTYPE_MAX			//弾の種類数
}BULLETTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXCOLOR col;
	int nType;			//種類
	bool bUse;			//使用しているかどうか
	BULLETTYPE state;
	int nLife;			//体力
	int nCounterState;	//状態のカウンタ
}BULLET;

//================================================
//プロトタイプ宣言
//================================================
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType, D3DXCOLOR col);	//(発射位置,方向,タイプ,色)

#endif