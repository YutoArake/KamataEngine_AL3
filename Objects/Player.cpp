#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, Model* modelB, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);

	// 引数で受け取ったのをメンバ変数に代入
	model_ = model;
	modelB_ = modelB;
	textureHandle_ = textureHandle;

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Player::Update() {

	// デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	// キャラクターの回転処理
	Rotate();

	// キャラクターの移動処理
	Move();

	// キャラクターの攻撃処理
	Attack();

	// 弾を更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

#pragma region デバッグテキスト
	// player座標
	// debugText_->SetPos(50.0f, 50.0f);
	// debugText_->Printf("pos : (%f, %f, %f)", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
#pragma endregion
}

void Player::Draw(const ViewProjection& viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection);

	// 弾を描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
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

void Player::Rotate() {
	//押した方向で回転ベクトルを変更
	if (input_->PushKey(DIK_U)) {
		//胸パーツのY軸周りの角度を減少
		worldTransform_.rotation_ -= {0.0f, (PI / 180), 0.0f};
	}
	else if (input_->PushKey(DIK_I)) {
		//胸パーツのY軸周りの角度を減少
		worldTransform_.rotation_ += {0.0f, (PI / 180), 0.0f};
	}
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0.0f, 0.0f, kBulletSpeed);

		// 速度ベクトルを自キャラに合わせて回転させる
		velocity = MatrixCalculation(velocity, worldTransform_.matWorld_);

		// 弾を生成し、初期化する
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(modelB_, worldTransform_.translation_, velocity);

		// 弾を登録する
		bullets_.push_back(std::move(newBullet));
	}
}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::OnCollision() {

}