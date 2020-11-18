//=====================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//=====================================================
#include "main.h"
#include "startlogo.h"
#include "input.h"
//#include "controller.h"

//=====================================================
// グローバル変数
//=====================================================
LPDIRECT3DTEXTURE9 g_pTexturePolygonStartlogo = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonStartlogo = NULL;	// 頂点バッファへのポインタ
STARTLOGO g_Startlogo[MAX_STARTLOGO];

//=============================================================================
// 初期化処理
//=============================================================================
void InitStartlogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/gamestart.png", &g_pTexturePolygonStartlogo);

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// バッファサイズ
		D3DUSAGE_WRITEONLY,				// (固定)
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,				// (固定)
		&g_pVtxBuffPolygonStartlogo,		// 変数名が変わると変更が必要
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D * pVtx;

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffPolygonStartlogo->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (STARTLOGO_SIZE_X / 2), (SCREEN_HEIGHT / 2) - (STARTLOGO_SIZE_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (STARTLOGO_SIZE_X / 2), (SCREEN_HEIGHT / 2) - (STARTLOGO_SIZE_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (STARTLOGO_SIZE_X / 2), (SCREEN_HEIGHT / 2) + (STARTLOGO_SIZE_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (STARTLOGO_SIZE_X / 2), (SCREEN_HEIGHT / 2) + (STARTLOGO_SIZE_Y / 2), 0.0f);

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

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロックする
	g_pVtxBuffPolygonStartlogo->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStartlogo(void)
{
	// テクスチャの開放
	if (g_pTexturePolygonStartlogo != NULL)
	{
		g_pTexturePolygonStartlogo->Release();
		g_pTexturePolygonStartlogo = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffPolygonStartlogo != NULL)
	{
		g_pVtxBuffPolygonStartlogo->Release();
		g_pVtxBuffPolygonStartlogo = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStartlogo(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStartlogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonStartlogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygonStartlogo);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,
		NUM_POLYGON);				// プリミティブの数
}

//=============================================================================
// エフェクトの設定
//=============================================================================
void SetStartlogo(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	int nCntBlock;				// ローカル変数

	for (nCntBlock = 0; nCntBlock < MAX_STARTLOGO; nCntBlock++)
	{
		// ブロックが使われてないとき
		if (g_Startlogo[nCntBlock].bUse == false)
		{
			g_Startlogo[nCntBlock].pos = pos;
			g_Startlogo[nCntBlock].size = size;
			g_Startlogo[nCntBlock].bUse = true;
			break;
		}
	}
}