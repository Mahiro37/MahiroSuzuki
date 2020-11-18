//=============================================================================
//
// スコア結果処理 [ScoreScreen.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SCORESCREEN_H_
#define _SCORESCREEN_H_

//*****************************************************************************
//ヘッダファイルのインクルード
//*****************************************************************************
#include "mode.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CScore;

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define SCORE_	(4)	//スコアの

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CScoreScreen :public CMode
{
public:
	//スコアの種類の列挙型
	typedef enum
	{
		SCORE_TYPE_0 = 0,	//ゲームスコア
		SCORE_TYPE_1,		//タイムボーナス
		SCORE_TYPE_2,		//残機ボーナス
		SCORE_TYPE_3,		//総合スコア
		SCORE_TYPE_MAX
	}SCORE_TYPE;

	CScoreScreen();
	~CScoreScreen();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SaveScore(int nScore);
	static void SaveTotalTime(int nTotalTime);
	static void SavePlayerLife(int nPlayerLife);

private:
	CScore *m_pScore[SCORE_TYPE_MAX];	//スコアのポインタ
	static int m_nScore;				//ゲームスコア
	static int m_nTotalTime;			//総合タイム
	static int m_nRanking;				//ランキング順位
	static int m_nScoreBonus;			//タイムボーナス
	static int m_nPlayerLife;			//プレイヤーの残機
	int m_nTotalScore;					//総合スコア
	int m_nPlayerLifeBonus;				//残機ボーナス
	float m_fAddNum;					//スコア加算の演出用カウント
	bool m_bSet[SCORE_TYPE_MAX];		//加算演出が終了したかの判定
};

#endif