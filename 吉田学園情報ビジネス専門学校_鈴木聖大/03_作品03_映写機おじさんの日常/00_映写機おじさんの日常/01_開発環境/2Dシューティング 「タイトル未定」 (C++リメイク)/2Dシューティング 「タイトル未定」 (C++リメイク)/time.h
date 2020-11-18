//=============================================================================
//
// タイム処理 [time.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

//*****************************************************************************
//ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "number.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define TIME_NUM			(2)			//タイムの桁数
#define TIME_START_NUM		(60)		//開始時のタイム

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CTime :public CScene
{
public:
	CTime();
	~CTime();
	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTime, CNumber::TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTime(int nTime);
	void SaveTime(int nTime);
	void SetStopTime(bool bTimeStop);
	void ResetTotalTime(void);

	int GetTime(void);
	int GetTotalTime(void);
	int GetSaveTime(void);

private:
	static CNumber *m_pNumber[TIME_NUM];	//数字のポインタ配列
	int m_nTime;							//タイム
	int m_nTotalTime;						//総合タイム
	int m_nSaveTime;						//保存したタイム
	int m_nTimeCounter;						//1秒をカウントする
	bool m_bTimeStop;						//タイムを進めるかの判定
};

#endif