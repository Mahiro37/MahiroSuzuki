//================================================
//3Dゲーム制作
//Author:鈴木聖大
//================================================
#ifndef PLAYER_H_
#define PLAYER_H_

#define CRT_SECURE_NO_WARNINGS

//=====================================================
// インクルードファイル
//=====================================================
#include "main.h"

//================================================
//マクロ定義
//================================================
#define PLAYER_SIZE_X (20.0f)
#define PLAYER_SIZE_Y (20.0f)
#define PLAYER_SIZE_Z (20.0f)
#define MAX_PLAYER (1)

//================================================
//構造体定義
//================================================
typedef struct
{
	int nType;					//種類
	bool bUse;					//使用しているかどうか
	int nLife;					//体力
	int nCounterState;			//状態のカウンタ
	D3DXVECTOR3 pos;			//位置情報
	D3DXVECTOR3 posOld;			//位置情報
	D3DXVECTOR3 rot;			//!<向き取得用
	D3DXVECTOR3 rotDest;		//目的の角度
	//D3DXVECTOR3 vecU;			//!<上方向ベクトル
	//D3DXMATRIX mtxProjection;	//!<プロジェクションマトリックス
	//D3DXMATRIX mtxView;		//!<ビューマトリックス
	//float fDistance;			//!<視点-注視点の距離
}Player;

//=====================================================
// プロトタイプ宣言
//=====================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player*GetPlayer(void);
void HitPlayer(int nCntPlayer, int nDamage);
bool IsGameOver();

#endif