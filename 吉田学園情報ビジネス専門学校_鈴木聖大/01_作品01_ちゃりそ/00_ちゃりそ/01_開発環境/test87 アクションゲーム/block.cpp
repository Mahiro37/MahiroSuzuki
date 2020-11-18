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
#include "block.h"
#include "player.h"

//****************************************************************
// マクロ定義
//****************************************************************
#define MAX_TYPE_BLOCK (3)
#define VALUE_MOVE (8.0f)

//****************************************************************
// グローバル変数
//****************************************************************
LPDIRECT3DTEXTURE9 g_pTextureBlock[MAX_TYPE_BLOCK] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// 頂点バッファへのポインタ
BLOCKSTATE g_BlockState;
BLOCK g_aBlock[MAX_BLOCK];//ブロックの情報

//****************************************************************
//初期化処理
//****************************************************************
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntBlock;

	//ブロックの情報の初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//g_moveBlock = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].bUse = false;
	}

	// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, "テクスチャ/b.png", &g_pTextureBlock[0]);
		D3DXCreateTextureFromFile(pDevice, "テクスチャ/yuka1.png", &g_pTextureBlock[1]);
		D3DXCreateTextureFromFile(pDevice, "テクスチャ/yuka2.png", &g_pTextureBlock[2]);

	// 頂点バッファ生成 
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX*MAX_BLOCK,	// バッファサイズ
		D3DUSAGE_WRITEONLY,				// (固定)
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,				// (固定)
		&g_pVtxBuffBlock,				// 変数名が変わると変更が必要
		NULL);

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

	//ブロックの数分
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_0 / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_0 / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_0 / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_0 / 2), 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	// 頂点データをアンロックする
	g_pVtxBuffBlock->Unlock(); 
}

//****************************************************************
//終了処理
//****************************************************************
void UninitBlock(void)
{
	// テクスチャの開放
	for (int nCountBlock = 0; nCountBlock < MAX_TYPE_BLOCK; nCountBlock++)
	{
		if (g_pTextureBlock[nCountBlock] != NULL)
		{
			g_pTextureBlock[nCountBlock]->Release();
			g_pTextureBlock[nCountBlock] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//****************************************************************
//更新処理
//****************************************************************
void UpdateBlock(void)
{
	// 頂点情報へのポインタ
	VERTEX_2D *pVtx;

	int nCntBlock;

	// 頂点バッファのロック
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock <= MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//移動
			g_aBlock[nCntBlock].pos += g_aBlock[nCntBlock].move;

			if (g_aBlock[nCntBlock].nType == 0)
			{
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_0 / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_0 / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_0 / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_0 / 2), 0.0f);

				if (g_aBlock[nCntBlock].pos.x < -(BLOCK_SIZE_X_0 / 2))
				{
					//g_aBlock[nCntBlock].bUse = false;
				}
			}
			if (g_aBlock[nCntBlock].nType == 1)
			{
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_1 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_1 / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_1 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_1 / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_1 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_1 / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_1 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_1 / 2), 0.0f);

				if (g_aBlock[nCntBlock].pos.x < -(BLOCK_SIZE_X_1 / 2))
				{
					g_aBlock[nCntBlock].bUse = false;
				}
			}
			if (g_aBlock[nCntBlock].nType == 2)
			{
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_2 / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_2 / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_2 / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_2 / 2), 0.0f);

				if (g_aBlock[nCntBlock].pos.x < -(BLOCK_SIZE_X_2 / 2))
				{
					g_aBlock[nCntBlock].bUse = false;
				}
			}
		}
		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffBlock->Unlock();
}

//****************************************************************
//
//****************************************************************
bool CollisionBlock(D3DXVECTOR3*pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3*pMove, D3DXVECTOR3 size)
{
	//VERTEX_2D *pVtx;						// 頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//宣言
	PLAYER*pPlayer = GetPlayer();			//敵の情報を取得
	bool bLand = false;
	int nCntBlock;
	int sizeX;
	int sizeY;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (g_aBlock[nCntBlock].nType == 0)
			{
				sizeX = BLOCK_SIZE_X_0;
				sizeY = BLOCK_SIZE_Y_0;
			}
			else if (g_aBlock[nCntBlock].nType == 1)
			{
				sizeX = BLOCK_SIZE_X_1;
				sizeY = BLOCK_SIZE_Y_1;
			}
			else if (g_aBlock[nCntBlock].nType == 2)
			{
				sizeX = BLOCK_SIZE_X_2;
				sizeY = BLOCK_SIZE_Y_2;
			}

			//ブロックの当たり判定
			if (pPlayer->pos.y<g_aBlock[nCntBlock].pos.y + (sizeY / 2) + (PLAYER_SIZE / 2) &&
				pPlayer->pos.y>g_aBlock[nCntBlock].pos.y - (sizeY / 2) - (PLAYER_SIZE / 2) &&
				pPlayer->pos.x<g_aBlock[nCntBlock].pos.x + (sizeX / 2) + (PLAYER_SIZE / 2) &&
				pPlayer->pos.x>g_aBlock[nCntBlock].pos.x - (sizeX / 2) - (PLAYER_SIZE / 2))
			{
				////下
				//if (pPlayer->pos.y < g_aBlock[nCntBlock].pos.y + (sizeY / 2) + (PLAYER_SIZE / 2) &&
				//	pPlayer->posOld.y >= g_aBlock[nCntBlock].pos.y + (sizeY / 2) + (PLAYER_SIZE / 2))
				//{
				//	pPos->y = g_aBlock[nCntBlock].pos.y + (sizeY / 2) + (PLAYER_SIZE / 2);
				//	pMove->y = 0;
				//}
				//上
				if (pPlayer->pos.y > g_aBlock[nCntBlock].pos.y - (sizeY / 2) - (PLAYER_SIZE / 2) &&
					pPlayer->posOld.y <= g_aBlock[nCntBlock].pos.y - (sizeY / 2) - (PLAYER_SIZE / 2))
				{
					pPos->y = g_aBlock[nCntBlock].pos.y - (sizeY / 2) - (PLAYER_SIZE / 2);
					pMove->y = 0;
					bLand = true;
					pPlayer->bJump = true;
				}
				////右
				//else if (pPlayer->pos.x <= g_aBlock[nCntBlock].pos.x + (sizeX / 2) + (PLAYER_SIZE) &&
				//	pPlayer->posOld.x >= g_aBlock[nCntBlock].pos.x + (sizeX / 2) + (PLAYER_SIZE / 2))
				//{
				//	pPos->x = g_aBlock[nCntBlock].pos.x + (sizeX / 2) + (PLAYER_SIZE / 2);
				//	pMove->x = 0.0f;
				//}
				//左
				else if (pPlayer->pos.x >= g_aBlock[nCntBlock].pos.x - (sizeX / 2) - (PLAYER_SIZE) &&
					pPlayer->pos.x < g_aBlock[nCntBlock].pos.x + (sizeX / 2) -(PLAYER_SIZE / 2))
				{
					pPos->x = g_aBlock[nCntBlock].pos.x - (sizeX / 2) - (PLAYER_SIZE / 2);
					pMove->x = 0.0f;
					HitPlayer(100);
				}
			}
		}
	}
	return bLand;
}

//****************************************************************
//描画処理
//****************************************************************
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntBlock;

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの描画
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			//ブロックが使用中なら描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}

//****************************************************************
//設定処理
//****************************************************************
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nType)
{
	VERTEX_2D*pVtx;
	int nCntBlock;
	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)//未使用の時
		{
			//位置設定
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].move = move;
			g_aBlock[nCntBlock].bUse = true;//使用している状態にする
			g_aBlock[nCntBlock].nType = nType;

			if (g_aBlock[nCntBlock].nType == 0)
			{
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_0 / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_0 / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_0 / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_0 / 2), 0.0f);
			}
			if (g_aBlock[nCntBlock].nType == 1)
			{
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_1 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_1 / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_1/ 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_1 / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_1 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_1 / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_1/ 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_1 / 2), 0.0f);
			}
			if (g_aBlock[nCntBlock].nType == 2)
			{
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_2 / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_2 / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_2 / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_2 / 2), 0.0f);
			}
			break;
		} 
		//頂点データのポインタを4つ分進める
		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//****************************************************************
//
//****************************************************************
BLOCK * GetBlock(int nCntBlock)
{
	return &g_aBlock[nCntBlock];
}
