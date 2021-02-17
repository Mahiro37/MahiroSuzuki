//=============================================================================
//
// パーティクル処理 [particle.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "particle.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define PARTICLE_GRAVITY (0.3f)
#define PARTICLE_DISTANCE (30)
#define PARTICLE_SIZE (D3DXVECTOR3(20.0f,20.0f,0.0f))
#define PARTICLE_MOVE (6)

//*****************************************************************************
//静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = {};

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CParticle::CParticle()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fGravity = 0.0f;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CParticle::~CParticle()
{
}

//*****************************************************************************
//パーティクルの生成(単体)
//*****************************************************************************
CParticle * CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CParticle *pParticle = new CParticle;

	//初期化処理
	pParticle->Init(pos, move);

	return pParticle;
}

//*****************************************************************************
//パーティクルの生成(複数)
//*****************************************************************************
void CParticle::Create(D3DXVECTOR3 pos, int nNum)
{
	for (int nCount = 0; nCount < nNum; nCount++)
	{
		//角度の計算
		float fAngle = D3DXToRadian(360 / nNum) * nCount;

		//距離の計算
		int nDistance = rand() % PARTICLE_DISTANCE + 1;

		//移動量の計算
		int nMove = rand() % PARTICLE_MOVE + 1;

		//パーティクルの生成(単体)
		Create(D3DXVECTOR3(pos.x + cosf(fAngle) * nDistance, pos.y + sinf(fAngle) * nDistance, 0.0f), D3DXVECTOR3(cosf(fAngle) * nMove, sinf(fAngle) * nMove, 0.0f));
	}
}

//*****************************************************************************
//ロード処理
//*****************************************************************************
HRESULT CParticle::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Textures/popcorn.png", &m_pTexture);

	return S_OK;
}

//*****************************************************************************
//アンロード処理
//*****************************************************************************
void CParticle::Unload(void)
{
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//シーン2Dの初期化
	CScene2D::Init();

	//位置の設定
	SetPos(pos);

	//移動量の設定
	m_move = move;

	//サイズの設定
	SetSize(PARTICLE_SIZE);

	//初期重力量の設定
	m_fGravity = PARTICLE_GRAVITY;

	//オブジェクトの種類の設定
	SetObjType(OBJTYPE_PARTICLE);

	//テクスチャの割り当て
	BindTexture(m_pTexture);

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CParticle::Uninit(void)
{
	//シーン2Dの終了処理
	CScene2D::Uninit();
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CParticle::Update(void)
{
	//シーン2Dの更新処理
	CScene2D::Update();

	//ポジションの取得
	D3DXVECTOR3 pos = GetPos();

	pos += m_move;

	//重力を加算
	m_fGravity += PARTICLE_GRAVITY;
	pos.y += m_fGravity;

	//回転処理
	Rotation(pos, PARTICLE_SIZE, ROTATION_RIGHT);

	//位置の更新
	SetPos(pos);

	//画面より下に出たとき
	if (pos.y >= SCREEN_HEIGHT + (PARTICLE_SIZE.y / 2))
	{
		//アイテムの終了処理
		Uninit();
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CParticle::Draw(void)
{
	//シーン2Dの描画処理
	CScene2D::Draw();
}