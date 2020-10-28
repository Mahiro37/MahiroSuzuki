//=============================================================================
//
// スコアアタック処理 [score_attack.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include <time.h>
#include "score_attack.h"
#include "manager.h"
#include "keyboard.h"
#include "controller.h"
#include "time.h"
#include "enemy.h"
#include "bg.h"
#include "player.h"
#include "score.h"
#include "life.h"
#include "sound.h"
#include "scene.h"
#include "ui.h"
#include "fade.h"
#include "ranking.h"
#include "message.h"
#include "pause.h"

//*****************************************************************************
//静的メンバ変数宣言
//*****************************************************************************
CScore *CScoreAttack::m_pScore = NULL;

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CScoreAttack::CScoreAttack()
{
	m_pMessage = NULL;
	m_pFade = NULL;
	m_bStartPush = false;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CScoreAttack::~CScoreAttack()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CScoreAttack::Init(void)
{
	//背景の生成
	CBg::Create();

	//ファーストボールの生成
	CEnemy::Create(D3DXVECTOR3(800.0f, 200.0f, 0.0f), FIRST_BALL_SIZE, D3DXVECTOR3(3.0f, -2.0f, 0.0f), CScene::OBJTYPE_FIRST_BALL);
	CEnemy::Create(D3DXVECTOR3(400.0f, 200.0f, 0.0f), FIRST_BALL_SIZE, D3DXVECTOR3(-3.0f, -2.0f, 0.0f), CScene::OBJTYPE_FIRST_BALL);

	//プレイヤーの生成
	CManager::CreatePlayer();

	//タイムの生成
	CManager::CreateTime(D3DXVECTOR3((SCREEN_WIDTH / 2) + 20.0f, 80.0f, 0.0f), D3DXVECTOR3(40.0f, 50.0f, 0.0f), TIME_START_NUM, CNumber::TYPE_2);
	CManager::GetTime()->SetTime(CManager::GetTime()->GetSaveTime());
	CManager::GetTime()->SetStopTime(false);

	//タイマーUIの生成
	CUi::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 70.0f, 0.0f), D3DXVECTOR3(110.0f, 130.0f, 0.0f), CUi::UI_TYPE_TIMER);

	//残機の生成
	CManager::CreateLife(D3DXVECTOR3(350.0f, 80.0f, 0.0f));
	int nLife = CManager::GetPlayer()->GetPlayerLife();
	CManager::GetLife()->SetLife(nLife);

	//残機UIの生成
	CUi::Create(D3DXVECTOR3(260.0f, 80.0f, 0.0f), D3DXVECTOR3(130.0f, 60.0f, 0.0f), CUi::UI_TYPE_ZANKI);

	if (m_pScore == NULL)
	{
		//スコアの生成
		m_pScore = CScore::Create(D3DXVECTOR3(1070.0f, 80.0f, 0.0f), D3DXVECTOR3(50.0f, 60.0f, 0.0f), 30.0f, 0, CNumber::TYPE_2);

		if (m_pScore != NULL)
		{
			//スコアの設定
			m_pScore->SetScore(m_pScore->GetScore());
		}
	}

	//スコアUIの生成
	CUi::Create(D3DXVECTOR3(880.0f, 80.0f, 0.0f), D3DXVECTOR3(90.0f, 50.0f, 0.0f), CUi::UI_TYPE_SCORE);

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CScoreAttack::Uninit(void)
{
	//BGMの停止
	CManager::GetSound()->Stop(CSound::SOUND_LABEL_BGM05);

	//全てのメモリの開放処理
	CScene::ReleaseAllOtherThanFade();

	if (m_pScore != NULL)
	{
		//スコアの終了処理
		m_pScore->Uninit();
		m_pScore = NULL;
	}

	if (m_pMessage != NULL)
	{
		m_pMessage = NULL;
	}

	if (m_pFade != NULL)
	{
		m_pFade = NULL;
	}
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CScoreAttack::Update(void)
{
	bool bPause = false;		//ポーズが生成されているかの判定
	bool bInstruction = false;	//操作説明が生成されているかの判定
	CPause *pPause = NULL;		//ポーズのポインタ
	CUi *pUi = NULL;			//UIのポインタ

	for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
	{
		//オブジェクトの取得
		CScene *pScene = CScene::GetScene(nCntScene);

		if (bPause == false)
		{ //ポーズが生成されていないとき
		  //ダイナミックキャスト
			pPause = dynamic_cast<CPause*>(pScene);

			if (pPause != NULL)
			{
				//フラグを立てる
				bPause = true;
			}
		}

		if (bInstruction == false)
		{ //操作説明が生成されていないとき
		  //ダイナミックキャスト
			pUi = dynamic_cast<CUi*>(pScene);

			if (pUi != NULL)
			{
				if (pUi->GetUiType() == CUi::UI_TYPE_DESCRIPTION)
				{
					//フラグを立てる
					bInstruction = true;
				}
			}
		}

		if (bPause == true && bInstruction == true)
		{ //ポーズと操作説明がどちらも生成されているとき
			break;
		}
	}

	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_P) || CManager::GetController()->GetJoypadTrigger(11))
	{ //Pを押したとき または スタートボタンを押したとき
		if (m_bStartPush == false && CManager::GetPlayer()->GetChargeRelease() == true)
		{ //スタートボタンを押していないとき かつ チャージしていないとき
			if (CScene::GetUpdateStop() == false)
			{ //CSceneの更新が止まっていないとき
				if (bPause == false && bInstruction == false)
				{ //ポーズと操作説明が生成されていないとき
				  //ポーズの生成
					CPause::Create();
				}
			}
			else
			{ //CSceneの更新が止まっているとき
				if (bPause == true && bInstruction == false)
				{ //ポーズが生成されていて、操作説明が生成されていないとき
					if (pPause != NULL)
					{
						//ポーズの終了処理
						pPause->Uninit();

						//シーンの更新を進める
						CScene::UpdateStop(false);
					}
				}
			}

			//スタートボタンのプッシュフラグを立てる
			m_bStartPush = true;
		}
	}

	if (CManager::GetKeyboard()->GetKeyboardRelease(DIK_P) || CManager::GetController()->GetJoypadRelease(11))
	{ //Pを離したとき または スタートボタンを離したとき
	  //スタートボタンのプッシュフラグを下げる
		m_bStartPush = false;
	}

	int nTimeNow = 0;	//今のタイム

	if (CManager::GetTime() != NULL)
	{
		//タイムの取得
		nTimeNow = CManager::GetTime()->GetTime();
	}

	if (nTimeNow != 0)
	{ //タイムが０ではないとき
		bool bEnemy = false;	//敵の有無判定

		for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
		{
			//オブジェクトの取得
			CScene *pScene = CScene::GetScene(nCntScene);

			//ダイナミックキャスト
			CEnemy *pEnemy = dynamic_cast<CEnemy*>(pScene);

			if (pEnemy != NULL)
			{ //敵がいるとき
				//判定をtrueにする
				bEnemy = true;

				break;
			}
		}

		if (bEnemy == false)
		{ //敵がいないとき
			//ファーストボールの生成
			CEnemy::Create(D3DXVECTOR3(640.0f, -100.0f, 0.0f), FIRST_BALL_SIZE, D3DXVECTOR3(3.0f, -2.0f, 0.0f), CScene::OBJTYPE_FIRST_BALL);
			CEnemy::Create(D3DXVECTOR3(640.0f, -100.0f, 0.0f), FIRST_BALL_SIZE, D3DXVECTOR3(-3.0f, -2.0f, 0.0f), CScene::OBJTYPE_FIRST_BALL);
		}

		bool bPlayer = false;	//プレイヤーの生存判定

		for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
		{
			//オブジェクトの取得
			CScene *pScene = CScene::GetScene(nCntScene);

			//ダイナミックキャスト
			CPlayer *pPlayer = dynamic_cast<CPlayer*>(pScene);

			if (pPlayer != NULL)
			{ //プレイヤーが生きているとき
				//判定をtrueにする
				bPlayer = true;

				break;
			}
		}

		if (bPlayer == false)
		{ //プレイヤーが死んでいるとき
			if (CManager::GetTime() != NULL)
			{
				//時間を止める
				CManager::GetTime()->SetStopTime(true);

				//時間の保管
				CManager::GetTime()->SaveTime(nTimeNow);
			}

			if (CManager::GetPlayer()->GetPlayerLife() >= 0)
			{ //残機が残っているとき
				if (m_pFade == NULL)
				{
					//フェードの生成
					m_pFade = CFade::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CManager::MODE_SCORE_ATTACK);
				}
			}
		}
	}
	else
	{
		//SEの停止
		CManager::GetSound()->Stop(CSound::SOUND_LABEL_CHARGE);

		if (m_pMessage == NULL)
		{
			//メッセージの生成
			m_pMessage = CMessage::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(400.0f, 200.0f, 0.0f), 60, CUi::UI_TYPE_FINISH, CManager::MODE_SCORE_SCREEN);
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CScoreAttack::Draw(void)
{
}

//*****************************************************************************
//スコアの加算処理
//*****************************************************************************
void CScoreAttack::AddScore(int nNum)
{
	m_pScore->AddScore(nNum);
}

//*****************************************************************************
//スコアの取得
//*****************************************************************************
CScore *CScoreAttack::GetScore(void)
{
	return m_pScore;
}