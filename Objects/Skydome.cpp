#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	// 引数で受け取ったのをメンバ変数に代入
	model_ = model;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// スケールを高くする
	worldTransform_.scale_ = { 100.0f, 100.0f, 100.0f };
	// 行列の計算、転送
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);
	// 転送
	worldTransform_.TransferMatrix();
}

void Skydome::Update() {

}

void Skydome::Draw(const ViewProjection& viewProjection) {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, viewProjection);
}