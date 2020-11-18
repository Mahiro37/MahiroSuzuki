//================================================================
//
//DirectXシューティングゲーム
//Author:鈴木聖大
//
//================================================================

//****************************************************************
//インクルードファイル
//****************************************************************
#include "main.h"
#include "player.h"
#include "input.h"
#include "game.h"
#include "explosion.h"
#include "block.h"
#include "timer.h"

//****************************************************************
// マクロ定義
//****************************************************************
#define VALUE_MOVE (10.0f) //ポリゴンの移動量
#define VALUE_JUMP (20.0f) //ジャンプ力 20
#define GRAVITY (1.2f) //重力 1.2

//****************************************************************
// グローバル変数
//****************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	// 頂点バッファへのポインタ
int g_nCounterAnim;			// アニメーションカウンター
int g_nPatternAnim;			// アニメーションパターンNo.
bool g_bScondJump;
int g_aNumPlayer;
PLAYER g_player;//プレイヤーの情報

//****************************************************************
// 初期化処理
//****************************************************************
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_player.pos = D3DXVECTOR3(0.0f, BLOCK_SIZE_Y_0, 0.0f);//プレイヤーの初期位置
	g_nCounterAnim = 0;		// アニメーションカウンターの初期化
	g_nPatternAnim = 0;		// アニメーションパターンNo.の初期化
	g_aNumPlayer = 1;

	g_bScondJump = false;
	g_player.bUse = true;
	g_player.nLife = PLAYER_LIFE;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/player.png",&g_pTexturePlayer);

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// バッファサイズ
		D3DUSAGE_WRITEONLY,				// (固定)
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,				// (固定)
		&g_pVtxBuffPlayer,				// 変数名が変わると変更が必要
		NULL);
	VERTEX_2D * pVtx;		// 頂点情報へのポインタ

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

	// rhwの設定(値は1.0で固定)		/ あまり変えることはない
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定(0～255の数値で設定)	/ 全体の色
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 左上頂点の色	透明度255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 右上頂点の色	透明度255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 左下頂点の色	透明度255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 右上頂点の色	透明度255

	// テクスチャ座標の設定		画面に対しての分割数
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の更新
	//pVtx[0].pos = D3DXVECTOR3(g_player.pos.x + (80.0f / 2), g_player.pos.y - (80.0f / 2), 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + (80.0f / 2), g_player.pos.y + (80.0f / 2), 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - (80.0f / 2), g_player.pos.y - (80.0f / 2), 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_player.pos.x - (80.0f / 2), g_player.pos.y + (80.0f / 2), 0.0f);

	g_player.pos = D3DXVECTOR3(PLAYER_POS_X, PLAYER_POS_Y, 0.0f);

	// 頂点データをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//****************************************************************
// ポリゴン終了処理
//****************************************************************
void UninitPlayer(void)
{
	// テクスチャの開放
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//****************************************************************
// 更新処理
//****************************************************************
void UpdatePlayer(void)
{
	// 頂点情報へのポインタ		位置や色を入れるときの最初に入れる(&pVtx)
	VERTEX_2D *pVtx;
	int nCntBlock = 0;
	BLOCK * pBlock = GetBlock(nCntBlock);
	//宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCounterAnim++;				// カウンター加算
	if (g_nCounterAnim == 8)		// 8fpsで次のアニメーション	＝ アニメーションの速さ
	{
		g_nCounterAnim = 0;			// カウンターを初期値に戻す
		g_nPatternAnim++;

		if (g_nPatternAnim == 4)	// 動かしたい画像の枚数
		{
			g_nPatternAnim = 0;		// カウンターを初期地に戻す
		}
	}

	// 頂点バッファのロック		位置や色を入れるときの最初に必要
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.bUse == true)
	{
		switch (g_player.state)
		{
		case PLAYERSTATE_NORMAL:
			break;
		case PLAYERSTATE_DAMAGE:
			g_player.nCounterState--;
			if (g_player.nCounterState <= 0)
			{
				g_player.state = PLAYERSTATE_NORMAL;

				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
		}

	// 移動の処理
		//前回の位置を保存
		g_player.posOld = g_player.pos;

		//重力
		g_player.move.y += GRAVITY;

		//位置更新
		g_player.pos.y += g_player.move.y;

		//２段ジャンプ
		if (g_bScondJump == true)
		{
			//スペースキーが押された時
			if (GetKeyboardTrigger(DIK_SPACE))
			{
				g_player.move.y = 0;
				g_player.move.y -= VALUE_JUMP-2;	//ジャンプの強さ
				g_bScondJump = false;
			}
			//上矢印キーが押されたとき
			else if (GetKeyboardTrigger(DIK_UP))
			{
				g_player.move.y = 0;
				g_player.move.y -= VALUE_JUMP + 3;	//ジャンプの強さ
				g_bScondJump = false;
			}
			//下矢印キーが押されたとき
			else if (GetKeyboardTrigger(DIK_DOWN))
			{
				g_player.move.y = 0;
				g_player.move.y -= VALUE_JUMP - 5;	//ジャンプの強さ
				g_bScondJump = false;
			}
		}

		//ブロック上にいるとき
		if (CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, D3DXVECTOR3(PLAYER_WIDTH_COLLISION, PLAYER_HEIGHT_COLLISION, 0.0f)))
		{
			g_player.bJump = false;
			g_bScondJump = true;

			g_player.move.y += GRAVITY;

			// テクスチャ座標を更新
			pVtx[0].tex = D3DXVECTOR2(g_nPatternAnim * 0.251f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_nPatternAnim * 0.251f + 0.251f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nPatternAnim * 0.251f, 0.51f);
			pVtx[3].tex = D3DXVECTOR2(g_nPatternAnim * 0.251f + 0.251f, 0.51f);

			if (g_player.bJump == false)
			{
				//スペースキーが押された時
				if (GetKeyboardTrigger(DIK_SPACE))
				{
					g_player.move.y -= VALUE_JUMP;	//ジャンプの強さ
				}
			}
		}
		else
		{
			g_player.bJump = false;
			// テクスチャ座標を更新
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.251f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.251f, 1.0f);
		}
		if (g_player.pos.y < SCREEN_HEIGHT)
		{
			HitPlayer(100);
		}

		//// Aのキーが押された時
		//if (GetKeyboardPress(DIK_A) && g_player.pos.x >= 0+50)
		//{
		//	g_player.pos.x -= VALUE_MOVE;	// 移動の速さ
		//}

		//// Dのキーが押された時
		//if (GetKeyboardPress(DIK_D) && g_player.pos.x <= SCREEN_WIDTH - 50)
		//{
		//	g_player.pos.x += VALUE_MOVE;	// 移動の速さ
		//}

		//// Wのキーが押された時
		//if (GetKeyboardPress(DIK_W) && g_player.pos.y >= 0 + 50)
		//{
		//	g_player.pos.y -= VALUE_MOVE;	// 移動の速さ
		//}

		//// Sのキーが押された時
		//if (GetKeyboardPress(DIK_S) && g_player.pos.y <= SCREEN_HEIGHT - 50)
		//{
		//	g_player.pos.y += VALUE_MOVE;	// 移動の速さ
		//}

		// 頂点座標の更新
		pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_SIZE / 2), g_player.pos.y - (PLAYER_SIZE / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_SIZE / 2), g_player.pos.y - (PLAYER_SIZE / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_SIZE / 2), g_player.pos.y + (PLAYER_SIZE / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_SIZE / 2), g_player.pos.y + (PLAYER_SIZE / 2), 0.0f);
	}
	// 頂点バッファをアンロック		最後に必要
	g_pVtxBuffPlayer->Unlock();
}

//****************************************************************
// 描画処理
//****************************************************************
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// ポリゴンの描画
	if (g_player.bUse == true)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,		// プリミティブの種類
			0,
			NUM_POLYGON);				// プリミティブの数
	}
}

//****************************************************************
//敵の取得
//****************************************************************
PLAYER*GetPlayer(void)
{
	return&g_player;
}

//****************************************************************
//ダメージ処理
//****************************************************************
void HitPlayer(int nDamage)
{
	VERTEX_2D*pVtx;//頂点情報のポインタ
	PLAYER*pPlayer = GetPlayer();//プレイヤーの情報を取得

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

	g_player.nLife -= nDamage;

	if (g_player.nLife <= 0)
	{
		g_aNumPlayer--;
		if (g_aNumPlayer <= 0)
		{
			SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 0, 0, 0.5f));
			g_player.bUse = true;
			SetGameState(GAMESTATE_END);

			////爆発生成
			//g_player.bUse = false;

			//// 頂点カラーの設定
			//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	else
	{
		//ダメージ状態へ
		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 5;
		if (g_player.state == PLAYERSTATE_DAMAGE)
		{
			////頂点カラーの設定
			//pVtx[0].col = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);
			//pVtx[1].col = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);
			//pVtx[2].col = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);
			//pVtx[3].col = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);
		}
	}

	// 頂点データをアンロックする
	g_pVtxBuffPlayer->Unlock();
}