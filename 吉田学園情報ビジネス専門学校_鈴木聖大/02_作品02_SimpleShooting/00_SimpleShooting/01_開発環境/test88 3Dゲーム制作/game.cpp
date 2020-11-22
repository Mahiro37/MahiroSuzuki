//=====================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//=====================================================
#include "main.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "input.h"
#include "wallblock.h"
#include "shadow.h"
#include "enemy.h"
#include "damageblock.h"
#include "bullet.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "clearlogo.h"
#include "gameoverlogo.h"
#include "blur.h"
#include "borderlogo.h"
#include "startlogo.h"
#include "effect.h"
#include "barrier.h"
#include "controller.h"

//=====================================================
// グローバル変数
//=====================================================
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCntStartState;
int g_nCntFinishState;
float g_Blockx;
bool isCamera;

//=====================================================
//初期化処理
//=====================================================
void InitGame(void)
{
	g_nCntStartState = 0;
	g_nCntFinishState = 0;
	g_Blockx = 0;
	isCamera = false;

	int nCntBlock;

	//ゲームスタートロゴの初期化
	InitStartlogo();

	//ゲームクリアロゴの初期化
	InitClearlogo();

	//ゲームオーバーロゴの初期化
	InitGameoverlogo();

	//ロゴの境界線の初期化
	InitBorderlogo();

	//ぼかしの初期化
	InitBlur();

	//エフェクトの初期化
	InitEffect();

	//ポリゴンの初期化
	InitPolygon();

	//バリアの初期化
	InitBarrier();
	SetBarrier(D3DXVECTOR3(0, 2, 10), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 15.0f));

	//モデルの初期化
	InitPlayer();

	//敵の初期化
	InitEnemy();
	SetEnemy(D3DXVECTOR3(-110.0f, 2.0f, 110.0f), 0, 0);
	SetEnemy(D3DXVECTOR3(0.0f, 2.0f, 110.0f), 0, 1);
	SetEnemy(D3DXVECTOR3(110.0f, 2.0f, 110.0f), 0, 2);
	SetEnemy(D3DXVECTOR3(-110.0f, 2.0f, 0.0f), 0, 3);
	SetEnemy(D3DXVECTOR3(110.0f, 2.0f, 0.0f), 0, 4);
	SetEnemy(D3DXVECTOR3(-110.0f, 2.0f, -110.0f), 0, 5);
	SetEnemy(D3DXVECTOR3(0.0f, 2.0f, -110.0f), 0, 6);
	SetEnemy(D3DXVECTOR3(110.0f, 2.0f, -110.0f), 0, 7);
	SetEnemy(D3DXVECTOR3(0.0f, 2.0f, 10.0f), 1, 8);

	//カメラの初期化
	InitCamera();

	//ライトの初期化
	InitLight();

	////影の初期化
	//InitShadow();

	//弾の初期化
	InitBullet();

	//ダメージブロックの初期化
	InitDamageblock();
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			for (nCntBlock = 0; nCntBlock < 17; nCntBlock++)
			{
				if (nCntBlock == 6 || nCntBlock == 11)
				{
					g_Blockx += 17.5f;
				}
				SetDamageblock(D3DXVECTOR3(-158 + g_Blockx, 2, 53), D3DXVECTOR3(12.0f, 12.0f, 12.0f), 0);
				g_Blockx += 17.5f;
			}
		}
		else if (i == 1)
		{
			for (nCntBlock = 0; nCntBlock < 17; nCntBlock++)
			{
				if (nCntBlock == 6 || nCntBlock == 11)
				{
					g_Blockx += 17.5f;
				}
				SetDamageblock(D3DXVECTOR3(-158 + g_Blockx, 2, -53), D3DXVECTOR3(12.0f, 12.0f, 12.0f), 0);
				g_Blockx += 17.5f;
			}
		}
		else if (i == 2)
		{
			for (nCntBlock = 0; nCntBlock < 17; nCntBlock++)
			{
				if (nCntBlock == 6 || nCntBlock == 11)
				{
					g_Blockx += 17.5f;
				}
				SetDamageblock(D3DXVECTOR3(-53, 2, 158 - g_Blockx), D3DXVECTOR3(12.0f, 12.0f, 12.0f), 0);
				g_Blockx += 17.5f;
			}
		}
		else if (i == 3)
		{
			for (nCntBlock = 0; nCntBlock < 17; nCntBlock++)
			{
				if (nCntBlock == 6 || nCntBlock == 11)
				{
					g_Blockx += 17.5f;
				}
				SetDamageblock(D3DXVECTOR3(52, 2, 158 - g_Blockx), D3DXVECTOR3(12.0f, 12.0f, 12.0f), 0);
				g_Blockx += 17.5f;
			}
		}

		g_Blockx = 0;
	}
	SetDamageblock(D3DXVECTOR3(100.0f, 2.0f, 53.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f), 0);

	//ブロックの初期化
	InitBlock();
	SetBlock(D3DXVECTOR3(0, 0, 172), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 9.0f, 12.0f));	//奥の壁
	SetBlock(D3DXVECTOR3(172, 0, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.8f, 9.0f, 500.0f));	//右の壁
	SetBlock(D3DXVECTOR3(-172, 0, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.8f, 9.0f, 500.0f));	//左の壁
	SetBlock(D3DXVECTOR3(0, 0, -172), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 9.0f, 10.0f));	//手前の壁

	g_gameState = GAMESTATE_NORMAL;
}

//=====================================================
//終了処理
//=====================================================
void UninitGame(void)
{
	//ゲームスタートロゴの終了処理
	UninitStartlogo();

	//ゲームクリアロゴの終了処理
	UninitClearlogo();

	//ゲームオーバーロゴの終了処理
	UninitGameoverlogo();

	//ロゴの境界線の終了処理
	UninitBorderlogo();

	//ぼかしの終了処理
	UninitBlur();

	//エフェクトの終了処理
	UninitEffect();

	//ポリゴンの終了処理
	UninitPolygon();

	//バリアの終了処理
	UninitBarrier();

	//モデルの終了処理
	UninitPlayer();

	//敵の終了処理
	UninitEnemy();

	////影の終了処理
	//UninitShadow();

	//弾の終了処理
	UninitBullet();

	//ダメージブロックの終了処理
	UninitDamageblock();

	//ブロックの終了処理
	UninitBlock();
}

//=====================================================
//更新処理
//=====================================================
void UpdateGame(void)
{
	Enemy pEnemy;

	g_nCntStartState++;

	if (g_nCntStartState >= COUNT_WAIT_START_GAME)
	{
		//ゲームを "クリア" or "ゲームオーバー" するまで更新
		if (IsGameClear() == false && IsGameOver() == false)
		{
			//カメラの更新処理
			UpdateCamera();
			if (GetJoypadPress(4))
			{
				InitCamera();
				isCamera = true;
			}
			else
			{
				isCamera = false;
			}

			//エフェクトの更新処理
			UpdateEffect();

			//バリアの更新処理
			UpdateBarrier();

			//モデルの更新処理
			UpdatePlayer();

			//敵の更新処理
			UpdateEnemy();

			//弾の更新処理
			UpdateBullet();

			//ダメージブロックの更新処理
			UpdateDamageblock();

			//ブロックの更新処理
			UpdateBlock();
		}
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;

	case GAMESTATE_END:
		g_nCntFinishState++;
		if (g_nCntFinishState >= COUNT_WAIT_FINISH_GAME)
		{
			g_gameState = GAMESTATE_NONE;
			SetMode(MODE_RESULT);
			g_nCntStartState = 0;
			g_nCntFinishState = 0;
		}
		break;
	}
}

//=====================================================
//描画処理
//=====================================================
void DrawGame(void)
{
	//カメラの設定処理
	SetCamera();

	//バリアの描画
	DrawBarrier();

	//モデルの描画
	DrawPlayer();

	//敵の描画
	DrawEnemy();

	////影の描画
	//DrawShadow();

	//ダメージブロックの描画
	DrawDamageblock();

	//ブロックの描画
	DrawBlock();

	//ポリゴンの描画
	DrawPolygon();

	//ゲームを "クリア" or "ゲームオーバー" するまで描画
	if (IsGameClear() == false && IsGameOver() == false)
	{
		//弾の描画
		DrawBullet();

		//雑魚敵を全滅するまで描画
		if (IsZakoDown() == false)
		{
			//if (isCamera == true)
			//{
				//エフェクトの描画
				DrawEffect();
			//}
		}

	}

	if (g_nCntStartState <= COUNT_WAIT_START_GAME)
	{
		//ゲームスタートロゴの描画
		DrawStartlogo();
	}

	//ゲームを "クリア" or "ゲームオーバー" したら描画
	if (IsGameClear() == true || IsGameOver() == true)
	{

		//ぼかしの描画
		DrawBlur();


		//ゲームクリアしたとき
		if (IsGameClear() == true)
		{
			//ゲームクリアロゴの描画
			DrawClearlogo();

			//ロゴの境界線の描画
			DrawBorderlogo();
		}


		//ゲームオーバーしたとき
		if (IsGameOver() == true)
		{
			//ゲームオーバーロゴの描画
			DrawGameoverlogo();

			//ロゴの境界線の描画
			DrawBorderlogo();
		}

	}
}

//=====================================================
//設定処理
//=====================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCntFinishState = 0;
}

//=====================================================
//デバイスの取得
//=====================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}