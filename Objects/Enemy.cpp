#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	// 引数で受け取ったのをメンバ変数に代入
	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("teki.png");

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// 初期座標をセット
	worldTransform_.translation_ = { 20.0f, 1.0f, 20.0f };
	// 行列の計算
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);

	// 速度の設定
	velocity_ = { 0.0f, 0.0f, -0.1f };

	// 接近フェーズを初期化
	ApproachInitialize();
}

void Enemy::Update() {

	// デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
		});

	// 移動処理
	Move();

	// 行列の計算
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);

	// 弾を更新
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// 弾を描画
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Move() {
	// フェーズに合わせて座標を移動させる(1フレーム分の移動量を足し込む)
	switch (phase_) {
	case Phase::Approach:
	default:
		Approach();
		break;
	case Phase::Leave:
		Leave();
		break;
	}
}

void Enemy::Approach() {
	// 速度
	Vector3 approachVelocity = { 0.0f, 0.0f, -0.1f };

	// 発射タイマーをデクリメント
	fireTimer--;
	// 指定時間に達した
	if (fireTimer <= 0) {
		// 弾を発射
		Fire();
		// 発射タイマーを初期化
		fireTimer = kFireInterval;
	}

	// 移動（ベクトルを加算）
	worldTransform_.translation_ += approachVelocity;
	// 規定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::ApproachInitialize() {
	// 発射タイマーを初期化
	fireTimer = kFireInterval;
}

void Enemy::Leave() {
	// 速度
	Vector3 leaveVelocity = { -0.2f, 0.2f, -0.1f };

	// 移動（ベクトルを加算）
	worldTransform_.translation_ += leaveVelocity;
}

void Enemy::Fire() {
	// 弾の速度
	const float kBulletSpeed = -1.0f;
	Vector3 velocity(0.0f, 0.0f, kBulletSpeed);

	// 速度ベクトルを自キャラに合わせて回転させる
	velocity = MatrixCalculation(velocity, worldTransform_.matWorld_);

	// 弾を生成し、初期化する
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	// 弾を登録する
	bullets_.push_back(std::move(newBullet));
}