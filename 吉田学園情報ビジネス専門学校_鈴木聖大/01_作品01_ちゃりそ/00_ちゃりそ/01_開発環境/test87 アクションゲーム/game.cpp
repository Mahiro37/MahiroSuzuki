//================================================================
//
//DirectXシューティングゲーム
//Author:鈴木聖大
//
//================================================================

//****************************************************************
//インクルードファイル
//****************************************************************
#include "bg.h"
#include "bg2.h"
#include "bg3.h"
#include "explosion.h"
#include "player.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "block.h"
#include "timer.h"
#include "timerlogo.h"

//****************************************************************
// マクロ定義
//****************************************************************
#define BLOCK_SPEED (-10.0f)//ブロックの流れるスピード
#define SPEEDUP_NUM (0.3f)//スピードアップ量

//****************************************************************
// グローバル変数
//****************************************************************
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
int g_nCounterState;
float g_aBlockSpeed;//だんだん早くなる
int g_nHelloBlockTime;//ブロックが生成される時間
int g_nA;

//****************************************************************
//初期化処理
//****************************************************************
void InitGame(void)
{
	//bgの初期化処理
	InitBg();
	InitBg2();
	InitBg3();
	//ブロックの初期化処理
	InitBlock();
	SetBlock(D3DXVECTOR3(800, BLOCK_POS_Y, 0),D3DXVECTOR3(BLOCK_SPEED, 0, 0.0f),0);
	// ポリゴンの初期化処理
	InitPlayer();
	//タイマーの初期化処理
	InitTimer();
	//タイマーロゴの初期化処理
	InitTimerLogo();
	////弾の初期化処理
	//InitBullet();
	//爆発の初期化処理
	InitExplosion();

	g_gameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_nCounterState = 370;
	g_nHelloBlockTime = 400;
	g_nA = 2;
}

//****************************************************************
//終了処理
//****************************************************************
void UninitGame(void)
{
	//bgの終了処理
	UninitBg();
	UninitBg2();
	UninitBg3();
	//ブロックの終了処理
	UninitBlock();
	// ポリゴンの終了処理
	UninitPlayer();
	//タイマーの終了処理
	UninitTimer();
	//タイマーロゴの終了処理
	UninitTimerLogo();
	//爆発の終了処理
	UninitExplosion();
}

//****************************************************************
//更新処理
//****************************************************************
void UpdateGame(void)
{
	g_nCounterState++;
	//BLOCK_SPEED;

	UpdateBg();
	UpdateBg2();
	UpdateExplosion();
	UpdatePlayer();
	UpdateTimer();
	UpdateBlock();

	srand((unsigned int)time(NULL));
	int num = rand() % 5 + 1;

	if (g_nCounterState == g_nHelloBlockTime)
	{
		if (num==1)
		{
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH, 600, 0.0f), D3DXVECTOR3(BLOCK_SPEED+ g_aBlockSpeed, 0, 0.0f), 1);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 800, 900, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 1400, 700, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 1);
			g_nCounterState = 220;
			g_aBlockSpeed -= SPEEDUP_NUM;
			g_nHelloBlockTime -= g_nA;
		}
		else if (num == 2)
		{
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH, 950, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 800, 600, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 1);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 1400, 1000, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			g_nCounterState = 220;
			g_aBlockSpeed -= SPEEDUP_NUM;
			g_nHelloBlockTime -= g_nA;
		}
		else if (num == 3)
		{
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH, 850, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 700, 900, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 1400, 950, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			g_nCounterState = 220;
			g_aBlockSpeed -= SPEEDUP_NUM;
			g_nHelloBlockTime -= g_nA;
		}
		else if (num == 4)
		{
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH, 650, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 1);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 800, 600, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 1);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 1400, 700, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			g_nCounterState = 220;
			g_aBlockSpeed -= SPEEDUP_NUM;
			g_nHelloBlockTime -= g_nA;
		}
		else if (num == 5)
		{
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH, 850, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 800, 750, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 1);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 1400, 600, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 1);
			g_nCounterState = 220;
			g_aBlockSpeed -= SPEEDUP_NUM;
			g_nHelloBlockTime -= g_nA;
		}
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= COUNT_WAIT_FINISH_GAME)
		{
			g_aBlockSpeed = 0;
			g_nHelloBlockTime = 0;
			g_nA = 0;
			g_gameState = GAMESTATE_NONE;
			StopTimer();
			//画面モードの設定
			SetMode(MODE_RESULT);
		}
		break;
	}
}

//****************************************************************
//描画処理
//****************************************************************
void DrawGame(void)
{
	// bgの描画処理
	DrawBg();
	DrawBg2();
	DrawBg3();
	//ブロックの描画処理
	DrawBlock();
	//爆発の描画処理
	DrawExplosion();
	// ポリゴンの描画処理
	DrawPlayer();
	//タイマーロゴの描画処理
	DrawTimerLogo();
	//タイマーの描画処理
	DrawTimer();
}

//****************************************************************
//設定処理
//****************************************************************
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//****************************************************************
//デバイスの取得
//****************************************************************
GAMESTATE GetGameState(void)
{
	return g_gameState;
}