#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);

	// 引数で受け取ったのをメンバ変数に代入
	model_ = model;
	textureHandle_ = textureHandle;

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Player::Update() {
	// キャラクターの移動処理
	Move();

#pragma region デバッグテキスト
	// player座標
	debugText_->SetPos(50.0f, 50.0f);
	debugText_->Printf("pos : (%f, %f, %f)", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
#pragma endregion
}

void Player::Draw(ViewProjection viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Player::Move() {
	// キャラクターの移動ベクトル
	Vector3 move = { 0.0f, 0.0f, 0.0f };

	// キャラクターの移動速さ
	const float kPlayerSpeed = 0.1f;

	// 左か右キーを押したらmoveを変化させる
	if (input_->PushKey(DIK_RIGHTARROW)) {
		move.x = kPlayerSpeed;
	}
	else if (input_->PushKey(DIK_LEFTARROW)) {
		move.x = -kPlayerSpeed;
	}
	if (input_->PushKey(DIK_UPARROW)) {
		move.y = kPlayerSpeed;
	}
	else if (input_->PushKey(DIK_DOWNARROW)) {
		move.y = -kPlayerSpeed;
	}

	// 移動量を加算
	worldTransform_.translation_ += move;

	//移動限界座標
	const float kMoveLimiteX = 34.0f;
	const float kMoveLimiteY = 18.0f;

	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimiteX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimiteX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimiteY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimiteY);

	// 更新
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);
}