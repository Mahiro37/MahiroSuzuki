#pragma once
//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#define _CRT_SECURE_NO_WARNINGS

//================================================
//インクルードファイル
//================================================
#include "main.h"

//=====================================================
//マクロ定義
//=====================================================
#define MAX_EXPLOSION (128)//爆発の最大数
#define EXPLOSION_SIZE (20)//爆発のサイズ

//================================================
//プロトタイプ宣言
//================================================
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);

#endif