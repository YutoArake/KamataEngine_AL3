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
	worldTransform_.translation_ = { 0.0f, 1.0f, 20.0f };
	// 行列の計算
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);

	// 速度の設定
	velocity_ = { 0.0f, 0.0f, -0.1f };
}

void Enemy::Update() {

	// 移動処理
	Move();

	// 行列の計算
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
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

	// 移動（ベクトルを加算）
	worldTransform_.translation_ += approachVelocity;
	// 規定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave() {
	// 速度
	Vector3 leaveVelocity = { -0.2f, 0.2f, -0.1f };

	// 移動（ベクトルを加算）
	worldTransform_.translation_ += leaveVelocity;
}