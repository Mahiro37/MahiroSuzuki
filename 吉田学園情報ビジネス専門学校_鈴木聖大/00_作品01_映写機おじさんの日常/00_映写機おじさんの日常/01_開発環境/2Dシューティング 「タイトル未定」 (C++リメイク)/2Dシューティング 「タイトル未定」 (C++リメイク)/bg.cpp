//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG_TEXTURE] = {};

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CBg::CBg()
{
	m_pScene2D = NULL;
	m_nAnimCounter = 0;
	m_nAnimPattern = 0;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CBg::~CBg()
{
}

//*****************************************************************************
//ロード処理
//*****************************************************************************
HRESULT CBg::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "Textures/bg/retrofilm00.jpg", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "Textures/bg/retrofilm01.jpg", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "Textures/bg/retrofilm02.jpg", &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "Textures/bg/retrofilm03.jpg", &m_apTexture[3]);
	D3DXCreateTextureFromFile(pDevice, "Textures/bg/retrofilm04.jpg", &m_apTexture[4]);
	D3DXCreateTextureFromFile(pDevice, "Textures/bg/retrofilm05.jpg", &m_apTexture[5]);
	D3DXCreateTextureFromFile(pDevice, "Textures/bg/retrofilm06.jpg", &m_apTexture[6]);
	D3DXCreateTextureFromFile(pDevice, "Textures/bg/retrofilm07.jpg", &m_apTexture[7]);
	D3DXCreateTextureFromFile(pDevice, "Textures/bg/retrofilm08.jpg", &m_apTexture[8]);
	D3DXCreateTextureFromFile(pDevice, "Textures/bg/retrofilm09.jpg", &m_apTexture[9]);
	D3DXCreateTextureFromFile(pDevice, "Textures/bg/retrofilm10.jpg", &m_apTexture[10]);

	return S_OK;
}

//*****************************************************************************
//アンロード処理
//*****************************************************************************
void CBg::Unload(void)
{
	for (int nCount = 0; nCount < MAX_BG_TEXTURE; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			//テクスチャの破棄
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//*****************************************************************************
//背景の生成
//*****************************************************************************
CBg *CBg::Create(void)
{
	//背景のメモリ確保
	CBg *pBg = new CBg;

	//背景の初期化
	pBg->Init();

	//オブジェクトタイプの設定
	pBg->SetObjType(OBJTYPE_BG);

	return pBg;
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CBg::Init(void)
{
	//シーン2Dのメモリ確保
	m_pScene2D = new CScene2D;

	if (m_pScene2D != NULL)
	{
		//オブジェクトの種類の設定
		m_pScene2D->SetObjType(OBJTYPE_BG);

		//サイズの設定
		m_pScene2D->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

		//シーン2Dの初期化処理
		m_pScene2D->Init();

		//テクスチャの設定
		m_pScene2D->BindTexture(m_apTexture[0]);
	}

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CBg::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		//シーン2Dの終了処理
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CBg::Update(void)
{
	//アニメーションカウントを進める
	m_nAnimCounter++;

	if (m_nAnimCounter == 2)
	{ //２フレーム経ったとき
		//カウントの初期化
		m_nAnimCounter = 0;

		if (m_pScene2D != NULL)
		{
			//アニメーションパターンを進める
			m_nAnimPattern++;

			if (m_nAnimPattern == MAX_BG_TEXTURE)
			{ //最後のパターンまでいったとき
				//パターンカウントの初期化
				m_nAnimPattern = 0;
			}

			//テクスチャの設定
			m_pScene2D->BindTexture(m_apTexture[m_nAnimPattern]);
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CBg::Draw(void)
{
}