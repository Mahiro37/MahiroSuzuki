//=====================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//=====================================================
// main.hとbg.hを引っ張ってくる
#include "main.h"
#include "bg.h"

//=====================================================
// グローバル変数
//=====================================================
//VERTEX_2D g_aVertex[NUM_VERTEX];					// 頂点情報格納
LPDIRECT3DTEXTURE9 g_pTexturePolygonBg = NULL;		// テクスチャへのポインタ		Bgに変更が必要
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonBg = NULL;	// 頂点バッファへのポインタ		Bgに変更が必要
int g_nCounterAnimBg;
int g_nPatternAnimBg;

//=============================================================================
// 初期化処理
//=============================================================================
void InitBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_nCounterAnimBg = 0;
	g_nPatternAnimBg = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "Textures/bg100.png",		// ファイルの名前
		&g_pTexturePolygonBg);	// 変数名が変わると変更

								// 頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// バッファサイズ
		D3DUSAGE_WRITEONLY,				// (固定)
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,				// (固定)
		&g_pVtxBuffPolygonBg,				// 変数名が変わると変更が必要
		NULL);
	VERTEX_2D * pVtx;		// 頂点情報へのポインタ

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffPolygonBg->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

	// 頂点座標の設定( Zの形に配置する)  / 四角形の頂点の位置
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
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

	// 頂点データをアンロックする
	g_pVtxBuffPolygonBg->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBg(void)
{
	// テクスチャの開放
	if (g_pTexturePolygonBg != NULL)
	{
		g_pTexturePolygonBg->Release();
		g_pTexturePolygonBg = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffPolygonBg != NULL)
	{
		g_pVtxBuffPolygonBg->Release();
		g_pVtxBuffPolygonBg = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBg(void)
{
	VERTEX_2D *pVtx;

	g_nCounterAnimBg++;

	if (g_nCounterAnimBg == 1)
	{
		g_nCounterAnimBg = 0;

		g_nPatternAnimBg++;

		if (g_nPatternAnimBg == 2000)
		{
			g_nPatternAnimBg = 0;
		}
	}

	// 頂点データの範囲をロック
	g_pVtxBuffPolygonBg->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, g_nPatternAnimBg * 0.996f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, g_nPatternAnimBg * 0.996f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, g_nPatternAnimBg * 0.996f + 0.996f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, g_nPatternAnimBg * 0.996f + 0.996f);

	// 頂点データをアンロック
	g_pVtxBuffPolygonBg->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonBg, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygonBg);
	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// プリミティブの種類
		0,
		NUM_POLYGON);				// プリミティブの数
}

/*
[初期化処理]頂点バッファの生成 → 頂点データの範囲をロックし、頂点バッファのポインタを取得 → 頂点座標の設定：rhwの設定：頂点カラー：テクスチャ座標の設定
[終了処理]テクスチャの開放 → 頂点バッファの開放
[更新処理]
[描画処理]頂点バッファをデバイスのデータストリームにバインド → 頂点フォーマット → テクスチャの設定 → ポリゴンの描画
*/