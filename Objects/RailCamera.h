#pragma once

#include "WorldTransform.h"
#include "ViewProjection.h"

/// <summary>
/// レールカメラ
/// </summary>
class RailCamera {
private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	AffinMatrix mat;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const ViewProjection& viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 旋回
	/// </summary>
	void Rotate();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション（参照渡し）</param>
	// void Draw(const ViewProjection& viewProjection);
};