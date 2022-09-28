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
	worldTransform_.translation_ = { 0.0f, 5.0f, 20.0f };
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
	// 座標を移動させる(1フレーム分の移動量を足し込む)
	worldTransform_.translation_ += velocity_;
}