#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include <memory>
#include <list>

#include "EnemyBullet.h"

// 自機クラスの前方宣言
class Player;

/// <summary>
/// 敵
/// </summary>
class Enemy {
private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 行列計算用
	AffinMatrix mat;

	// 自キャラ
	Player* player_ = nullptr;

	// 行動フェーズ
	enum class Phase {
		Approach,	// 接近する
		Leave,		// 離脱する
	};

	// フェーズ
	Phase phase_ = Phase::Approach;

	// 速度
	Vector3 velocity_;

	// 弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	// 寿命<frm>
	static const int32_t kLifeTime = 60 * 5;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;

	// 発射タイマー
	int32_t fireTimer = 0;

public:
	// 発射間隔
	static const int kFireInterval = 60;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	void Initialize(Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション（参照渡し）</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// デスフラグのゲッター
	/// </summary>
	bool IsDead() const { return isDead_; }

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 接近
	/// </summary>
	void Approach();

	/// <summary>
	/// 接近フェーズ初期化
	/// </summary>
	void ApproachInitialize();

	/// <summary>
	/// 離脱
	/// </summary>
	void Leave();

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire();

	/// <summary>
	/// 自機クラスのセッター
	/// </summary>
	void SetPlayer(Player* player) { player_ = player; }

	/// <summary>
	/// 座標のゲッター
	/// </summary>
	Vector3 GetWorldPosition();
};