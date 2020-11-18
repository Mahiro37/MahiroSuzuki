//=====================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//=====================================================
#include "bg.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "player.h"
#include "title.h"
#include "game.h"

//=====================================================
// グローバル変数
//=====================================================
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;

//=====================================================
//初期化処理
//=====================================================
void InitGame(void)
{
	//bgの初期化処理
	InitBg();

	// プレイヤーの初期化処理
	InitPlayer();

	//弾の初期化処理
	InitBullet();

	//爆発の初期化処理
	InitExplosion();

	//敵の初期化処理
	InitEnemy();

	SetEnemy(D3DXVECTOR3(300.0f, 100.0f, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 0, 3);
	SetEnemy(D3DXVECTOR3(600.0f, 200.0f, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 0, 5);
	SetEnemy(D3DXVECTOR3(900.0f, 100.0f, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 0, 3);
}

//=====================================================
//終了処理
//=====================================================
void UninitGame(void)
{
	//bgの終了処理
	UninitBg();

	// プレイヤーの終了処理
	UninitPlayer();

	//弾の終了処理
	UninitBullet();

	//爆発の終了処理
	UninitExplosion();

	//敵の終了処理
	UninitEnemy();
}

//=====================================================
//更新処理
//=====================================================
void UpdateGame(void)
{
	UpdateBg();

	UpdateBullet();

	UpdateEnemy();

	UpdateExplosion();

	UpdatePlayer();
}

//=====================================================
//描画処理
//=====================================================
void DrawGame(void)
{
	// bgの描画処理
	DrawBg();

	//敵の描画処理
	DrawEnemy();

	// ポリゴンの描画処理
	DrawPlayer();

	//弾の描画処理
	DrawBullet();

	//爆発の描画処理
	DrawExplosion();
}

//=====================================================
//設定処理
//=====================================================
void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
	g_nCounterGameState = 0;
}

//=====================================================
//デバイスの取得
//=====================================================
GAMESTATE GetGamesate(void)
{
	return g_gamestate;
}