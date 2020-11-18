//=============================================================================
//
// スタート時のカウント処理 [start_count.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _START_COUNT_H_
#define _START_COUNT_H_

//*****************************************************************************
//ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CNumber;
class CUi;

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CStartCount :public CScene
{
public:
	CStartCount();
	~CStartCount();
	static CStartCount *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CNumber *m_pNumber;	//数字のポインタ
	CUi *m_pUi;			//UIのポインタ
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_size;	//サイズ
	int m_nStartNumber;	//開始の数字
	int m_nCounter;		//カウントのカウント
	int m_nCntStageNum;	//ステージ番号
};

#endif