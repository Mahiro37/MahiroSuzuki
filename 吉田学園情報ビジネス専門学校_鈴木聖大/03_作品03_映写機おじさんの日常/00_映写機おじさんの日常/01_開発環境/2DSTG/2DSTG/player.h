//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"
#include "item.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define PLAYER_TEXTURE			(1)										//テクスチャの種類
#define PLAYER_LIFE				(3)										//プレイヤーの残機数
#define PLAYER_SIZE				(D3DXVECTOR3(150.0f,150.0f,0.0f))		//プレイヤーのサイズ
#define PLAYER_COLLISION_SIZE	(D3DXVECTOR3(60.0f,100.0f,0.0f))		//プレイヤーの当たり判定サイズ
#define PLAYER_RADIUS			(45.0f)									//プレイヤーの半径

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CBarrier;
class CBullet;
class CEffect;
class CMessage;

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CPlayer :public CScene2D
{
public:
	//プレイヤーの状態の列挙型
	typedef enum
	{
		PLAYER_STATE_NONE = 0,		//通常
		PLAYER_STATE_INVINCIBLE,	//無敵
		PLAYER_STATE_DEATH,			//死亡
		PLAYER_STATE_MAX
	}PLAYER_STATE;
	
	CPlayer();
	~CPlayer();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void PlayerReset(void);

	void SetItemStock(CItem::ITEMTYPE ItemType);
	void SetPlayerAbility(void);
	void DeleteBarrierAbility(void);
	void SetLife(int nLife);
	void SetPlayerState(PLAYER_STATE state);

	D3DXVECTOR3 GetPos(void);
	CBarrier *GetBarrier(void);
	CBullet *GetBullet(void);
	int GetPlayerLife(void);
	int GetChargeSpeed(void);
	list<CItem::ITEMTYPE> GetStockItem(void);
	PLAYER_STATE GetPlayerState(void);
	bool GetChargeRelease(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[PLAYER_TEXTURE];	//テクスチャのポインタ配列
	D3DXVECTOR3 m_pos;										//位置
	static int m_nLife;										//ライフ
	float m_fPlayerSpeed;									//移動スピード
	int m_nChargeSpeed;										//チャージスピード

	static CBarrier *m_pBarrier;							//バリアのポインタ
	CBullet *m_pBullet;										//弾のポインタ
	CEffect *m_pEffect;										//エフェクトのポインタ
	CMessage *m_pMessage;									//メッセージのポインタ

	list<CItem::ITEMTYPE> m_StockItem;						//アイテムストックのリスト

	PLAYER_STATE m_PlayerState;								//プレイヤーの状態

	int m_nCntInvincible;									//無敵カウント
	int m_nInvincibleTime;									//無敵時間中の点滅回数
	int m_nCntPress;										//チャージのプレス時間
	int m_nCntCharge;										//マックスチャージ状態でのプレス時間
	static bool m_bRelease;									//チャージしているかの判定
};

#endif