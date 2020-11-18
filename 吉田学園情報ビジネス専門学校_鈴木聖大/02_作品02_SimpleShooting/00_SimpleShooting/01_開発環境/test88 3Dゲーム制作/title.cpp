//=====================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//=====================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "controller.h"

//=====================================================
// グローバル変数
//=====================================================
LPDIRECT3DTEXTURE9 g_pTexturePolygonTitle = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonTitle = NULL;	// 頂点バッファへのポインタ
//int nCntState; //タイトル画面で操作を受け付けない時間

//=============================================================================
// 初期化処理
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//nCntState = 10;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/title.png",&g_pTexturePolygonTitle);

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// バッファサイズ
		D3DUSAGE_WRITEONLY,				// (固定)
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,				// (固定)
		&g_pVtxBuffPolygonTitle,		// 変数名が変わると変更が必要
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D * pVtx;

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffPolygonTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定( Zの形に配置する)  / 四角形の頂点の位置
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

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
	g_pVtxBuffPolygonTitle->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	// テクスチャの開放
	if (g_pTexturePolygonTitle != NULL)
	{
		g_pTexturePolygonTitle->Release();
		g_pTexturePolygonTitle = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffPolygonTitle != NULL)
	{
		g_pVtxBuffPolygonTitle->Release();
		g_pVtxBuffPolygonTitle = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	//nCntState--;

	//if (nCntState <= 0)
	//{
	if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(0) || GetJoypadTrigger(1) || GetJoypadTrigger(2) || GetJoypadTrigger(3) || GetJoypadTrigger(11))
	{
		SetMode(MODE_TUTORIAL);
	}
	//}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonTitle, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygonTitle);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,
		NUM_POLYGON);				// プリミティブの数
}