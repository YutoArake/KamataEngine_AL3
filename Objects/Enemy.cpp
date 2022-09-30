#include "Enemy.h"
#include "Player.h"
#include <cassert>

void Enemy::Initialize(Model* model, Model* modelB) {
	// NULLポインタチェック
	assert(model);

	// 引数で受け取ったのをメンバ変数に代入
	model_ = model;
	modelB_ = modelB;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("teki.png");

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// 初期座標をセット
	worldTransform_.translation_ = { 0.0f, 1.0f, 50.0f };
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
	model_->Draw(worldTransform_, viewProjection);

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
	// NULLポインタチェック
	assert(player_);

	// 弾の速度
	const float kBulletSpeed = 0.3f;

	// 自キャラと敵キャラの座標を得る
	Vector3 playerPos = player_->GetWorldPosition();
	Vector3 enemyPos = GetWorldPosition();

	// 差分ベクトルを求める
	Vector3 difVector;
	difVector.x = playerPos.x - enemyPos.x;
	difVector.y = playerPos.y - enemyPos.y;
	difVector.z = playerPos.z - enemyPos.z;

	// ベクトルの正規化
	Vector3 normal = MathUtility::Vector3Normalize(difVector);

	// ベクトルの長さを速度に合わせる
	Vector3 velocity(normal.x * kBulletSpeed, normal.y * kBulletSpeed, normal.z * kBulletSpeed);

	// 速度ベクトルを自キャラに合わせて回転させる
	velocity = MatrixCalculation(velocity, worldTransform_.matWorld_);

	// 弾を生成し、初期化する
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(modelB_, worldTransform_.translation_, velocity);

	// 弾を登録する
	bullets_.push_back(std::move(newBullet));
}

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::OnCollision() {
	isDead_ = true;
}