#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"

#include "MathMyFunc.h"
using namespace MathMyFunc;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public:
	// パーツID
	enum PartId {
		kRoot,			//大元
		kSpine,			//脊椎
		kChest,			//胸
		kHead,			//頭
		kArmL,			//左腕
		kArmR,			//右腕
		kHip,				//尻
		kLegL,			//左足
		kLegR,			//右足

		kNumPartId
	};

 private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// 3Dモデル
	Model* model_ = nullptr;
	
	// スプライト
	Sprite* sprite_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransforms_[kNumPartId];
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	// サウンドデータハンドル
	uint32_t soundDataHandle_ = 0;

	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;

	// 値を表示したい変数
	int32_t value_ = 0;

	AffinMatrix mat;
};