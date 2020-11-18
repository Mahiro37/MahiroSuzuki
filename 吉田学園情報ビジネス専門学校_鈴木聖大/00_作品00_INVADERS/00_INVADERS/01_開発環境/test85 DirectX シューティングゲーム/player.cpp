//=====================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//=====================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"

//=====================================================
// グローバル変数
//=====================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	// 頂点バッファへのポインタ
PLAYER g_Player;									//プレイヤーの情報

//=====================================================
// 初期化処理
//=====================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_Player.pos = D3DXVECTOR3(PLAYER_POS_X, PLAYER_POS_Y, 0.0f);
	g_Player.nLife = 2;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "Textures/Player.png", &g_pTexturePlayer);

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
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_SIZE_X / 2), g_Player.pos.y - (PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_SIZE_X / 2), g_Player.pos.y - (PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_SIZE_X / 2), g_Player.pos.y + (PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_SIZE_X / 2), g_Player.pos.y + (PLAYER_SIZE_Y / 2), 0.0f);

	// rhwの設定(値は1.0で固定)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロックする
	g_pVtxBuffPlayer->Unlock();

	g_Player.bUse = true;
}

//=====================================================
// ポリゴン終了処理
//=====================================================
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

//=====================================================
// ポリゴン更新処理
//=====================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 移動の処理
	// Aのキーが押された時
	if (GetKeyboardPress(DIK_A))
	{
		g_Player.pos.x -= VALUE_MOVE;	// 移動の速さ
	}

	// Wのキーが押された時
	if (GetKeyboardPress(DIK_W))
	{
		g_Player.pos.y -= VALUE_MOVE;	// 移動の速さ
	}

	// Sのキーが押された時
	if (GetKeyboardPress(DIK_S))
	{
		g_Player.pos.y += VALUE_MOVE;	// 移動の速さ
	}

	// Dのキーが押された時
	if (GetKeyboardPress(DIK_D))
	{
		g_Player.pos.x += VALUE_MOVE;	// 移動の速さ
	}

	//スペースキーが押された時
#if 0
	if (GetKeyboardPress(DIK_SPACE))
	{
		g_Player.nCounterBullet++;

		if (g_Player.nCounterBullet == 10)
		{
			SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y - (PLAYER_SIZE_Y / 2), 0.0f), D3DXVECTOR3(0, -15, 0), BULLETTYPE_PLAYER, D3DXCOLOR(255, 255, 255, 255));
			g_Player.nCounterBullet = 0;
		}
	}
#elif 1
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y - (PLAYER_SIZE_Y / 2), 0.0f), D3DXVECTOR3(0, -15, 0), BULLETTYPE_PLAYER, D3DXCOLOR(255, 255, 255, 255));
	}
#endif

	// 頂点バッファのロック
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_SIZE_X / 2), g_Player.pos.y - (PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_SIZE_X / 2), g_Player.pos.y - (PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_SIZE_X / 2), g_Player.pos.y + (PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_SIZE_X / 2), g_Player.pos.y + (PLAYER_SIZE_Y / 2), 0.0f);

	// テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();
}

//=====================================================
// ポリゴン描画処理
//=====================================================
void DrawPlayer(void)
{
	if (g_Player.bUse == true)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);//（プリミティブの種類 , ０番目のポインタ , プリミティブの数）
	}
}

//=====================================================
//ダメージ処理
//=====================================================
void HitPlayer(int nDamage)
{
	VERTEX_2D*pVtx;//頂点情報のポインタ

	// 頂点データの範囲をロック
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	g_Player.nLife -= nDamage;//敵の体力を減らす

	if (g_Player.nLife <= 0)
	{
		g_Player.bUse = false;

		//爆発生成
		//SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 0, 0, 0.5f));

		SetMode(MODE_RESULT);

		g_Player.bUse = true;
	}
	else
	{
		//ダメージ状態へ
		g_Player.state = PLAYERSTATE_DAMAGE;
	}

	// 頂点データをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//=====================================================
//敵の取得
//=====================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}