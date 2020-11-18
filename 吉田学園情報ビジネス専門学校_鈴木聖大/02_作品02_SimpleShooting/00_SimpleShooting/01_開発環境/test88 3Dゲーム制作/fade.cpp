////=============================================================================
////
//// DirectX STG enemyの追加 [fade.cpp]
//// Author :峯山 拓己
////
////=============================================================================
//#include "main.h"
//#include "fade.h"
//
////=============================================================================
//// グローバル変数
////=============================================================================
//LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;//テクスチャへのポインタ
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;//頂点バッファへのポインタ
//
//FADE g_fade;//フェード状態
//MODE g_modeNext = MODE_TITLE;//次の画面(モード)
//D3DXCOLOR g_colorFade;//フェード色
//
////=============================================================================
//// 初期化処理
////=============================================================================
//void InitFade(MODE modeNext)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//
//
//	//頂点バッファ生成
//	pDevice->CreateVertexBuffer(
//		sizeof(VERTEX_2D)*NUM_VERTEX,//バッファサイズ
//		D3DUSAGE_WRITEONLY,//(固定)
//		FVF_VERTEX_2D,//頂点フォーマット
//		D3DPOOL_MANAGED,//(固定)
//		&g_pVtxBuffFade,//変数名が変わると変更が必要
//		NULL);
//
//	VERTEX_2D *pVtx;//頂点情報へのポインタ
//
//	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
//	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えないこと
//
//	//頂点座標の設定(右回りで設定)
//	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
//
//	//rhwの設定(値は1.0で固定)
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//
//	//頂点カラーの設定(0～255の数値で設定)
//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	//(r,g,b,a)は0～255の範囲で決めること
//	//r:レッド g:グリーン b:ブルー a:透明度 を表している
//
//	//テクスチャ座標の設定
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//	//頂点データをアンロックする
//	g_pVtxBuffFade->Unlock();
//
//	g_fade = FADE_OUT;
//	g_modeNext = modeNext;
//	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//黒い画面(不透明)
//
//}
//
////=============================================================================
//// 終了処理
////=============================================================================
//void UninitFade(void)
//{
//	////テクスチャの開放
//	//if (g_pTextureFade != NULL)
//	//{
//	//	g_pTextureFade->Release();
//	//	g_pTextureFade = NULL;
//	//}
//	////頂点バッファの開放
//	//if (g_pVtxBuffFade != NULL)
//	//{
//	//	g_pVtxBuffFade->Release();
//	//	g_pTextureFade = NULL;
//	//}
//}
//
////=============================================================================
//// 更新処理
////=============================================================================
//void UpdateFade(void)
//{
//	VERTEX_2D *pVtx;//頂点情報へのポインタ
//
//					//頂点データの範囲をロックし、頂点バッファへのポインタを取得
//	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えないこと
//
//	if (g_fade != FADE_NONE)
//	{//フェード処理中
//		if (g_fade == FADE_IN)
//		{//フェードイン処理
//			g_colorFade.a -= FADE_RATE;//a値を減算して後ろの画面を浮き上がらせる
//			if (g_colorFade.a <= 0.0f)
//			{
//				//フェード終了処理
//				g_colorFade.a = 0.0f;
//				g_fade = FADE_NONE;
//			}
//		}
//		else if (g_fade == FADE_OUT)
//		{//フェードアウト処理
//			g_colorFade.a += FADE_RATE;//a値を加算して後ろの画面を消していく
//			if (g_colorFade.a >= 1.0f)
//			{
//				//フェードイン処理
//				g_colorFade.a = 1.0f;
//				g_fade = FADE_IN;
//
//				//モードを設定
//				SetMode(g_modeNext);
//			}
//		}
//		//頂点カラーの更新
//		pVtx[0].col = g_colorFade;
//		pVtx[1].col = g_colorFade;
//		pVtx[2].col = g_colorFade;
//		pVtx[3].col = g_colorFade;
//	}
//	//頂点データをアンロックする
//	g_pVtxBuffFade->Unlock();
//}
//
////=============================================================================
//// 描画処理
////=============================================================================
//void DrawFade(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	//頂点バッファをデバイスのデータストリームにバインド
//	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));
//
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//	//テクスチャの設定
//	pDevice->SetTexture(0, 0);
//
//	//ポリゴンの描画
//	pDevice->DrawPrimitive(
//		D3DPT_TRIANGLESTRIP,
//		0,
//		NUM_PLAYER);
//}
//
////=============================================================================
//// フェードの状態設定
////=============================================================================
//void SetFade(MODE modeNext)
//{
//	g_fade = FADE_OUT;
//	g_modeNext = modeNext;
//	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//黒い画面(透明)
//}
//
////=============================================================================
//// フェードの状態取得
////=============================================================================
//FADE GetFade(void)
//{
//	return g_fade;
//}