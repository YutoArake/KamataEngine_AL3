#include "RailCamera.h"

void RailCamera::Initialize(const ViewProjection& viewProjection) {
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ワールドトランスフォームの初期設定
	worldTransform_.translation_ = viewProjection.eye;
	worldTransform_.rotation_ = viewProjection.up;
	// farZの距離を適切な値にする
	// viewProjection_.farZ = 
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void RailCamera::Update() {
	// 角度
	Rotate();
	// 座標
	Move();

	// ビュープロジェクションに平行移動成分を代入
	viewProjection_.eye = worldTransform_.translation_;
	// ワールド前方ベクトル
	Vector3 forward(0.0f, 0.0f, 1.0f);
	// レールカメラの回転を反映
	forward = MatrixCalculation(forward, worldTransform_.matWorld_);
	// 視点から前方に適当な距離進んだ位置が注視点
	viewProjection_.target.x = viewProjection_.eye.x + forward.x;
	viewProjection_.target.y = viewProjection_.eye.y + forward.y;
	viewProjection_.target.z = viewProjection_.eye.z + forward.z;
	// ワールド上方向ベクトル
	Vector3 up(0.0f, 1.0f, 0.0f);
	// レールカメラの回転を反映（レールカメラの上方向ベクトル）
	viewProjection_.up = MatrixCalculation(up, worldTransform_.matWorld_);
	// ビュープロジェクションを更新と転送
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();

	// eye座標
	debugText_->SetPos(50.0f, 70.0f);
	debugText_->Printf("pos : (%f, %f, %f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
}

void RailCamera::Move() {
	// キャラクターの移動ベクトル
	Vector3 move = { 0.0f, 0.0f, 0.0f };

	// キャラクターの移動速さ
	const float kCameraSpeed = 0.1f;

	// 左か右キーを押したらmoveを変化させる
	if (input_->PushKey(DIK_D)) {
		move.x = kCameraSpeed;
	}
	else if (input_->PushKey(DIK_A)) {
		move.x = -kCameraSpeed;
	}
	if (input_->PushKey(DIK_W)) {
		move.z = kCameraSpeed;
	}
	else if (input_->PushKey(DIK_S)) {
		move.z = -kCameraSpeed;
	}

	// 移動量を加算
	worldTransform_.translation_ += move;

	// 更新
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);
}

void RailCamera::Rotate() {
	//押した方向で回転ベクトルを変更
	if (input_->PushKey(DIK_Q)) {
		//胸パーツのY軸周りの角度を減少
		worldTransform_.rotation_ -= {0.0f, (PI / 180), 0.0f};
	}
	else if (input_->PushKey(DIK_E)) {
		//胸パーツのY軸周りの角度を減少
		worldTransform_.rotation_ += {0.0f, (PI / 180), 0.0f};
	}
}