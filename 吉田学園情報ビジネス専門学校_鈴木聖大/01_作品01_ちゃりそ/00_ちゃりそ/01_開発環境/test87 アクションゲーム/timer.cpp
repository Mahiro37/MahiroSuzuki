//================================================================
//
//DirectXシューティングゲーム
//Author:鈴木聖大
//
//================================================================

//****************************************************************
//インクルードファイル
//****************************************************************
#include "timer.h"

//****************************************************************
//グローバル変数宣言
//****************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;//頂点バッファへのポインタ
int g_nTimer;
int g_nCounterAnimTimer = 0, g_nPatternAnimTimer = 0;
bool g_TimerUse;

//****************************************************************
// 初期化処理
//****************************************************************
void InitTimer(void)
{
	//変数宣言
	VERTEX_2D*pVtx;//頂点情報のポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_nTimer = 0; //タイマーの初期化
	g_TimerUse = true;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/number.png", &g_pTextureTimer);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_TIMER, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTimer, NULL);

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えないこと

	for (int nScore = 0; nScore < MAX_TIMER; nScore++)
	{
		//座標の設定（右回りで設定する）
		pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH - (nScore*NUMBER_SIZE_X + NUMBER_SIZE_X / 2) - (NUMBER_SIZE_X / 2) - 595, (NUMBER_SIZE_Y / 2) - (NUMBER_SIZE_Y / 2) + 80.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH - (nScore*NUMBER_SIZE_X + NUMBER_SIZE_X / 2) + (NUMBER_SIZE_X / 2) - 595, (NUMBER_SIZE_Y / 2) - (NUMBER_SIZE_Y / 2) + 80.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH - (nScore*NUMBER_SIZE_X + NUMBER_SIZE_X / 2) - (NUMBER_SIZE_X / 2) - 595, (NUMBER_SIZE_Y / 2) + (NUMBER_SIZE_Y / 2) + 80.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH - (nScore*NUMBER_SIZE_X + NUMBER_SIZE_X / 2) + (NUMBER_SIZE_X / 2) - 595, (NUMBER_SIZE_Y / 2) + (NUMBER_SIZE_Y / 2) + 80.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 230);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 230);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 230);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 230);

		//テクスチャの座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//頂点データのポインタを4つ分進める
	}

	//頂点データアンロック
	g_pVtxBuffTimer->Unlock();

}

//****************************************************************
// 終了処理
//****************************************************************
void UninitTimer(void)
{
	//テクスチャの開放
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//****************************************************************
// 更新処理
//****************************************************************
void UpdateTimer(void)
{
	//変数宣言
	VERTEX_2D*pVtx;//頂点情報のポインタ
	float fIndex;  //指数　(スコア表示用)
	float fRadix = 10.0f; //基数　(スコア表示用)

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えないこと

	for (fIndex = 0; fIndex < MAX_TIMER; fIndex++)
	{
		int nScore = (int)powf(fRadix, MAX_TIMER - fIndex);
		int nScore2 = (int)powf(fRadix, MAX_TIMER - fIndex - 1);
		int nAnswer = g_nTimer % nScore / nScore2;

		//テクスチャの座標
		pVtx[8].tex = D3DXVECTOR2(0.0f + (0.1f* nAnswer), 0.0f);
		pVtx[9].tex = D3DXVECTOR2(0.1f + (0.1f* nAnswer), 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f + (0.1f* nAnswer), 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.1f + (0.1f* nAnswer), 1.0f);

		pVtx -= 4;//頂点データのポインタを4つ分進める

	}

	g_nCounterAnimTimer++;
	if (g_nCounterAnimTimer == 59) //フレーム
	{
		g_nCounterAnimTimer = 0;
		g_nPatternAnimTimer++;
		if (g_nPatternAnimTimer == 1) //1秒間経ったらタイム+1
		{
			if (g_TimerUse == true)
			{
				g_nTimer++;
			}
				g_nPatternAnimTimer = 0;
		}
	}

	//頂点データアンロック
	g_pVtxBuffTimer->Unlock();
}

//****************************************************************
// 描画処理
//****************************************************************
void DrawTimer(void)
{

	//頂点フォーマットの設定
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定

	//スコアの数字の描画
	for (int nScore = 0; nScore < MAX_TIMER; nScore++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTimer);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nScore * 4, NUM_POLYGON);
	}

}

//****************************************************************
// スコア情報の送信
//****************************************************************
int GetTimer(void)
{
	return g_nTimer;
}

//****************************************************************
//
//****************************************************************
void StopTimer(void)
{
	g_TimerUse = false;
}