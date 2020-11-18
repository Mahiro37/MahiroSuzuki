//=============================================================================
//
// PLASTIC TROOPERS [bullet.cpp]の処理 (弾)
// Author:後藤慎之助
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "bullet.h"
#include "wallblock.h"
#include "barrier.h"
#include "damageblock.h"
#include "collision.h"

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureBullet[BULLETTYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//頂点バッファへのポインタ
BULLET g_Bullet[MAX_BULLET];//アイテムの情報

//=============================================================================
//初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスの取得
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_Bullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//ポリゴンの位置
		g_Bullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//ポリゴンの移動量
		g_Bullet[nCntBullet].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//ポリゴンの大きさ
		g_Bullet[nCntBullet].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//ポリゴンの向き
		g_Bullet[nCntBullet].type = BULLETTYPE_PLAYER;
		g_Bullet[nCntBullet].nLife = 0;
		g_Bullet[nCntBullet].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,		//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffBullet,//変数名が変わると変更が必要
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/billboard.png", &g_pTextureBullet[0]);   //プレイヤーの弾
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/BulletType1.png", &g_pTextureBullet[1]);  //敵の弾(消える)
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/BulletType2.png", &g_pTextureBullet[2]);  //敵の弾(消えない)

	VERTEX_3D *pVtx;//頂点情報のポインタ

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えないこと

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定（右回りで設定する）
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//法線ベクトル
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点データアンロック
	g_pVtxBuffBullet->Unlock();

}

//=============================================================================
// アイテム終了処理
//=============================================================================
void UninitBullet(void)
{
	//テクスチャの開放
	for (int nCntBullet = 0; nCntBullet < BULLETTYPE_MAX; nCntBullet++)
	{
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();
			g_pTextureBullet[nCntBullet] = NULL;
		}
	}

	//頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
//更新処理
//=============================================================================
void UpdateBullet(void)
{
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == true)
		{
			//1F前の位置
			g_Bullet[nCntBullet].posOld = g_Bullet[nCntBullet].pos;

			//移動量を反映させる
			g_Bullet[nCntBullet].pos += g_Bullet[nCntBullet].move;

			//弾の射程を決める
			g_Bullet[nCntBullet].nLife--;

			//弾が壁に当たったら、弾のライフをなくす
			if (HitBlock(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posOld, D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE + 10, BULLET_SIZE))==true)
			{
				g_Bullet[nCntBullet].nLife = 0;
			}

			//弾がバリアに当たったら、弾のライフをなくす
			if (HitBarrier2(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posOld, D3DXVECTOR3(BARRIER_SIZE_X, BARRIER_SIZE_Y + 10, BARRIER_SIZE_Z)) == true)
			{
				g_Bullet[nCntBullet].nLife = 0;
			}

			//自機の弾が敵のオレンジの弾に当たったら、自機の弾のライフをなくす
			if (g_Bullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				if (CollisionBullet(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posOld, g_Bullet[nCntBullet].size, BULLETTYPE_ENEMY1) == true)
				{
					g_Bullet[nCntBullet].nLife = 0;
				}
			}

			//敵の弾がブロックに当たったら、敵の弾のライフをなくす
			if (g_Bullet[nCntBullet].type == BULLETTYPE_ENEMY1)
			{
				if (HitDamageblock2(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posOld, D3DXVECTOR3(BULLET_SIZE , BULLET_SIZE +10, BULLET_SIZE )) == true)
				{
					g_Bullet[nCntBullet].nLife = 0;
				}
			}
			if (g_Bullet[nCntBullet].type == BULLETTYPE_ENEMY2)
			{
				if (HitDamageblock2(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posOld, D3DXVECTOR3(BULLET_SIZE , BULLET_SIZE + 10, BULLET_SIZE )) == true)
				{
					g_Bullet[nCntBullet].nLife = 0;
				}
			}

			//ライフがなくなったら未使用に
			if (g_Bullet[nCntBullet].nLife <= 0)
			{
				g_Bullet[nCntBullet].bUse = false;	//使用しない状態にする
			}

			//頂点座標の初期化（右回りで設定する）
			pVtx[0].pos = D3DXVECTOR3(0.0f - g_Bullet[nCntBullet].size.x, g_Bullet[nCntBullet].size.y + g_Bullet[nCntBullet].size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f + g_Bullet[nCntBullet].size.x, g_Bullet[nCntBullet].size.y + g_Bullet[nCntBullet].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f - g_Bullet[nCntBullet].size.x, g_Bullet[nCntBullet].size.y - g_Bullet[nCntBullet].size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f + g_Bullet[nCntBullet].size.x, g_Bullet[nCntBullet].size.y - g_Bullet[nCntBullet].size.y, 0.0f);

		}
		pVtx += 4;
	}

	//頂点データをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
//描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスのポインタを取得
	D3DXMATRIX mtxRot, mtxTrans;//行列計算用のマトリクス

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//アルファテストの比較方法の設定（GREATERは基準値より大きい場合)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == true)
		{
			//ワールドマトリクスの初期化
			D3DXMatrixIdentity(&g_Bullet[nCntBullet].mtxWorld);
			//回転の逆行列を生成
			pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
			D3DXMatrixInverse(&g_Bullet[nCntBullet].mtxWorld, NULL, &mtxRot);
			g_Bullet[nCntBullet].mtxWorld._41 = 0;//移動はさせたくないので0を代入
			g_Bullet[nCntBullet].mtxWorld._42 = 0;//移動はさせたくないので0を代入
			g_Bullet[nCntBullet].mtxWorld._43 = 0;//移動はさせたくないので0を代入

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCntBullet].pos.x, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_Bullet[nCntBullet].mtxWorld, &g_Bullet[nCntBullet].mtxWorld, &mtxTrans);
			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCntBullet].mtxWorld);
			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));
			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet[g_Bullet[nCntBullet].type]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

			//テクスチャの設定の解除
			pDevice->SetTexture(0, NULL);
		}
	}

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
//バレットの設定
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXVECTOR3 moveDir, int nLife, BULLETTYPE type)
{
	int nCntBullet = 0;

	for (; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == false)
		{
			g_Bullet[nCntBullet].bUse = true;
			g_Bullet[nCntBullet].pos = pos;
			g_Bullet[nCntBullet].dir = moveDir;
			g_Bullet[nCntBullet].size = size;
			g_Bullet[nCntBullet].move = move;
			g_Bullet[nCntBullet].nLife = nLife;
			g_Bullet[nCntBullet].type = type;

			break;
		}

	}

}

//=============================================================================
//バレットの取得
//=============================================================================
BULLET*GetBullet(void)
{
	return &g_Bullet[0];
}

//=====================================================
// 当たり判定の設定
//=====================================================
bool CollisionBullet(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size, BULLETTYPE type)
{
	bool bHit = false;  //当たったかどうか

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// 弾が使われたら
		if (g_Bullet[nCntBullet].bUse == true)
		{
			//当たり判定を計算
			if (RectangleCollision(pPos, pPosOld, size, &g_Bullet[nCntBullet].pos, g_Bullet[nCntBullet].size) == true)
			{
				//タイプが同じなら
				if (g_Bullet[nCntBullet].type == type)
				{
					bHit = true;    //当たった
					g_Bullet[nCntBullet].bUse = false;  //当たったら未使用に
				}
			}
		}
	}

	return bHit;    //当たったかどうかを返す
}