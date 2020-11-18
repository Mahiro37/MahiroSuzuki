//================================================================
//
//DirectXシューティングゲーム
//Author:鈴木聖大
//
//================================================================

//****************************************************************
//インクルードファイル
//****************************************************************
#include "explosion.h"

//****************************************************************
//構造体定義
//****************************************************************
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXCOLOR col;//色
	int nCounterAnim;//カウンター
	int nPatternAnim;//パターンNO.
	bool bUse;//使用しているかどうか
}EXPLOSION;//爆発の情報

//****************************************************************
//グローバル変数
//****************************************************************
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
EXPLOSION g_aExplosion[MAX_EXPLOSION];//爆発の情報


//****************************************************************
//初期化処理
//****************************************************************
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntExplosion;

	//爆発情報の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/explosion000.png", &g_pTextureExplosion);

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX*MAX_EXPLOSION,	// バッファサイズ
		D3DUSAGE_WRITEONLY,				// (固定)
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,				// (固定)
		&g_pVtxBuffExplosion,				// 変数名が変わると変更が必要
		NULL);

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

	//弾の数分
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		// rhwの設定(値は1.0で固定)		/ あまり変えることはない
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		// 頂点カラーの設定(0～255の数値で設定)	/ 全体の色
		pVtx[1].col = D3DXCOLOR(0, 255, 255, 255);
		pVtx[2].col = D3DXCOLOR(0, 255, 255, 255);
		pVtx[3].col = D3DXCOLOR(0, 255, 255, 255);
		pVtx[0].col = D3DXCOLOR(0, 255, 255, 255);
		// テクスチャ座標の設定		画面に対しての分割数
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	// 頂点データをアンロックする
	g_pVtxBuffExplosion->Unlock();
}
//****************************************************************
//更新処理
//****************************************************************
void UpdateExplosion(void)
{

	VERTEX_2D*pVtx;
	int nCntExplosion;

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			g_aExplosion[nCntExplosion].nCounterAnim++;				// カウンター加算
			if (g_aExplosion[nCntExplosion].nCounterAnim == 1)		// 8fpsで次のアニメーション	＝ アニメーションの速さ
			{
				g_aExplosion[nCntExplosion].nCounterAnim = 0;			// カウンターを初期値に戻す
				g_aExplosion[nCntExplosion].nPatternAnim++;				//アニメを次のコマにする
				if (g_aExplosion[nCntExplosion].nPatternAnim == 8)	// アニメのコマが最後まで再生されたら
				{
					g_aExplosion[nCntExplosion].bUse = false;//爆発を使用しているかのスイッチをオフにする
				}
			}
		}

				//テクスチャ座標を更新
				pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim*0.126f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim*0.126f + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim*0.126f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim*0.126f + 0.125f, 1.0f);

				//頂点データのポインタを4つ分進める
				pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//****************************************************************
// 描画処理
//****************************************************************
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntExplosion;

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureExplosion);
	// ポリゴンの描画
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)//敵が使用中なら描画
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, NUM_POLYGON);
		}
	}
}

//****************************************************************
//終了処理
//****************************************************************
void UninitExplosion(void)
{
	// テクスチャの開放
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//****************************************************************
//爆発の設定
//****************************************************************
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	VERTEX_2D*pVtx;
	int nCntExplosion;
	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)//未使用の時
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			g_aExplosion[nCntExplosion].bUse = true;//使用している状態にする

			// 頂点カラーの設定(0～255の数値で設定)	/ 全体の色
			pVtx[1].col = D3DXCOLOR(100, 100, 100, 255);
			pVtx[2].col = D3DXCOLOR(100, 100, 100, 255);
			pVtx[3].col = D3DXCOLOR(100, 100, 100, 255);
			pVtx[0].col = D3DXCOLOR(100, 100, 100, 255);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (-EXPLOSION_SIZE / 2), g_aExplosion[nCntExplosion].pos.y + (-EXPLOSION_SIZE / 2),0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (EXPLOSION_SIZE / 2), g_aExplosion[nCntExplosion].pos.y + (-EXPLOSION_SIZE / 2),0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (-EXPLOSION_SIZE / 2), g_aExplosion[nCntExplosion].pos.y + (EXPLOSION_SIZE / 2),0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (EXPLOSION_SIZE / 2), g_aExplosion[nCntExplosion].pos.y + (EXPLOSION_SIZE / 2),0.0f);
			break;
		}
		//頂点データのポインタを4つ分進める
		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffExplosion->Unlock();
}