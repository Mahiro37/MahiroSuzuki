//=====================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//=====================================================
#include "bullet.h"
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "explosion.h"

//=====================================================
//構造体定義
//=====================================================
//typedef struct
//{
//	D3DXVECTOR3 pos;//位置
//	D3DXVECTOR3 move;//移動量
//	int nLife;//寿命
//	bool bUse;//使用しているかどうか
//}BULLET;

//=====================================================
//グローバル変数
//=====================================================
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//頂点バッファへのポインタ
BULLET g_aBullet[MAX_BULLET];//弾の情報
bool g_bEnemyDamage = false;

//=====================================================
//初期化処理
//=====================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntBullet;
	
	//弾の情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3((BULLET_SIZE/2), (BULLET_SIZE / 2), 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 50;
		g_aBullet[nCntBullet].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "Textures/Bullet.png",&g_pTextureBullet);

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX*MAX_BULLET,	// バッファサイズ
		D3DUSAGE_WRITEONLY,				// (固定)
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,				// (固定)
		&g_pVtxBuffBullet,				// 変数名が変わると変更が必要
		NULL);

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

	//弾の数分
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// rhwの設定(値は1.0で固定)		/ あまり変えることはない
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定(0～255の数値で設定)	/ 全体の色
		pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);	// 左上頂点の色	透明度255
		pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);	// 右上頂点の色	透明度255
		pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);	// 左下頂点の色	透明度255
		pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);	// 右上頂点の色	透明度255

		// テクスチャ座標の設定		画面に対しての分割数
		pVtx[0].tex = D3DXVECTOR2(0,0);
		pVtx[1].tex = D3DXVECTOR2(1,0);
		pVtx[2].tex = D3DXVECTOR2(0,1);
		pVtx[3].tex = D3DXVECTOR2(1,1);

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	// 頂点データをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//=====================================================
//終了処理
//=====================================================
void UninitBullet(void)
{
	// テクスチャの開放
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	// 頂点情報へのポインタ		位置や色を入れるときの最初に入れる(&pVtx)
	VERTEX_2D *pVtx;

	ENEMY *apEnemy = GetEnemy();
	PLAYER *pPlayer = GetPlayer();

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)//弾が使用されている
		{
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			switch (g_aBullet[nCntBullet].nType)
			{
			case BULLETTYPE_PLAYER:

				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
				{
					if (apEnemy[nCntEnemy].bUse == true)
					{
						//当たり判定
						if (apEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2) <= g_aBullet[nCntBullet].pos.x&&
							apEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2) >= g_aBullet[nCntBullet].pos.x&&
							apEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE / 2) <= g_aBullet[nCntBullet].pos.y&&
							apEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2) >= g_aBullet[nCntBullet].pos.y)
						{//敵に弾が当たった時
							g_aBullet[nCntBullet].bUse = false;//弾を未使用状態にする
							HitEnemy(nCntEnemy, 1);
						}
					}
				}

				break;

			case BULLETTYPE_ENEMY:

					if (pPlayer->bUse == true)
					{
						//当たり判定(敵に弾が当たった時)
						if (pPlayer->pos.x - (PLAYER_SIZE_X / 2) <= g_aBullet[nCntBullet].pos.x&&
							pPlayer->pos.x + (PLAYER_SIZE_X / 2) >= g_aBullet[nCntBullet].pos.x&&
							pPlayer->pos.y - (PLAYER_SIZE_Y / 2) <= g_aBullet[nCntBullet].pos.y&&
							pPlayer->pos.y + (PLAYER_SIZE_Y / 2) >= g_aBullet[nCntBullet].pos.y)
						{
							g_aBullet[nCntBullet].bUse = false;	//弾を未使用状態にする
							HitPlayer(1);
							//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
						}
					}
			}

			// 頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y - (BULLET_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y - (BULLET_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE / 2), 0.0f);

			//画面外に出たら未使用に
			if (g_aBullet[nCntBullet].pos.x < 0 || g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH + (20 / 2))
			{
				g_aBullet[nCntBullet].nLife = 50;
				g_aBullet[nCntBullet].bUse = false;
			}
			else if (g_aBullet[nCntBullet].pos.y < 0 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT)
			{
				g_aBullet[nCntBullet].nLife = 50;
				g_aBullet[nCntBullet].bUse = false;
			}
		}
		pVtx += 4;//頂点データのポインタを4つ分進める
	}
	// 頂点データをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
//描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntBullet;

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	// ポリゴンの描画
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//弾が使用中なら描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}

//=============================================================================
//弾の設定処理
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType, D3DXCOLOR col)
{
	// 頂点情報へのポインタ		位置や色を入れるときの最初に入れる(&pVtx)
	VERTEX_2D *pVtx;

	int nCntBullet;
	
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)//弾が使用されていない場合
		{
			//位置を設定
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].nType = nType;
			g_aBullet[nCntBullet].col = col;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].bUse = true;//使用している状態にする

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y - (BULLET_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y - (BULLET_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE / 2), 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, 255);
			pVtx[1].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, 255);
			pVtx[2].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, 255);
			pVtx[3].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, 255);

			break;
		}

		pVtx += 4;	//頂点情報インクリメント
	}

	// 頂点データをアンロックする
	g_pVtxBuffBullet->Unlock();
}