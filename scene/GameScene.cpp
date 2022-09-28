#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include <cassert>
#include <random>

#pragma region 乱数生成
//乱数シード生成器
std::random_device seed_gen;
//メルセンヌ・ツイスターの乱数エンジン
std::mt19937_64 engine(seed_gen());

//乱数範囲の設定(角度)
std::uniform_real_distribution<float> distAngle(0.0f, PI);

//乱数範囲の設定(座標)
std::uniform_real_distribution<float> distPos(-10.0f, 10.0f);
#pragma endregion

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete sprite_;
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");

	// 3Dモデルの生成
	model_ = Model::Create();

	// スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, { 100, 50 });

#pragma region ワールドトランスフォームの初期化

	//親(キャラクターの大元)
	worldTransforms_[kRoot].Initialize();
	//子(脊椎)
	worldTransforms_[kSpine].Initialize();
	worldTransforms_[kSpine].translation_ = { 0.0f, 0.0f, 0.0f };
	worldTransforms_[kSpine].parent_ = &worldTransforms_[kRoot];

	//子(上半身)
	//胸
	worldTransforms_[kChest].Initialize();
	worldTransforms_[kChest].translation_ = { 0.0f, 0.0f, 0.0f };
	worldTransforms_[kChest].parent_ = &worldTransforms_[kSpine];
	//頭
	worldTransforms_[kHead].Initialize();
	worldTransforms_[kHead].translation_ = { 0.0f, 3.0f, 0.0f };
	worldTransforms_[kHead].parent_ = &worldTransforms_[kChest];
	//左腕
	worldTransforms_[kArmL].Initialize();
	worldTransforms_[kArmL].translation_ = { -3.0f, 0.0f, 0.0f };
	worldTransforms_[kArmL].parent_ = &worldTransforms_[kChest];
	//右腕
	worldTransforms_[kArmR].Initialize();
	worldTransforms_[kArmR].translation_ = { 3.0f, 0.0f, 0.0f };
	worldTransforms_[kArmR].parent_ = &worldTransforms_[kChest];

	//子(下半身)
	//尻
	worldTransforms_[kHip].Initialize();
	worldTransforms_[kHip].translation_ = { 0.0f, -3.0f, 0.0f };
	worldTransforms_[kHip].parent_ = &worldTransforms_[kSpine];
	//左足
	worldTransforms_[kLegL].Initialize();
	worldTransforms_[kLegL].translation_ = { -3.0f, -3.0f, 0.0f };
	worldTransforms_[kLegL].parent_ = &worldTransforms_[kHip];
	//右足
	worldTransforms_[kLegR].Initialize();
	worldTransforms_[kLegR].translation_ = { 3.0f, -3.0f, 0.0f };
	worldTransforms_[kLegR].parent_ = &worldTransforms_[kHip];
#pragma endregion

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

#pragma region 軸
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

#pragma endregion

#pragma region 音

	// サウンドデータの読み込み
	// soundDataHandle_ = audio_->LoadWave("mokugyo.wav");

	// 音声再生
	// audio_->PlayWave(soundDataHandle_);
	// voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
#pragma endregion
}

void GameScene::Update() {
	// キャラクターの移動処理
	{
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

		// 移動量を加算
		worldTransforms_[kRoot].translation_ += move;

		// デバッグテキスト
		debugText_->SetPos(50.0f, 50.0f);
		debugText_->Printf("pos : (%f, %f, %f)", worldTransforms_[0].translation_.x, worldTransforms_[0].translation_.y, worldTransforms_[0].translation_.z);
	}

	//キャラクターの回転処理
	//上半身回転処理
	{
		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_U)) {
			//胸パーツのY軸周りの角度を減少
			worldTransforms_[kChest].rotation_ -= {0.0f, PI / 180, 0.0f};
		}
		else if (input_->PushKey(DIK_I)) {
			//胸パーツのY軸周りの角度を減少
			worldTransforms_[kChest].rotation_ += {0.0f, PI / 180, 0.0f};
		}
	}
	//下半身回転処理
	{
		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_J)) {
			//尻パーツのY軸周りの角度を減少
			worldTransforms_[kHip].rotation_ -= {0.0f, PI / 180, 0.0f};
		}
		else if (input_->PushKey(DIK_K)) {
			//尻パーツのY軸周りの角度を減少
			worldTransforms_[kHip].rotation_ += {0.0f, PI / 180, 0.0f};
		}
	}

	// 大元から順に更新していく
	for (int i = 0; i < kNumPartId; i++) {
		worldTransforms_[i].UpdateWorldTransform(worldTransforms_[i], mat);
	}

	// 視点移動処理
	viewProjection_.UpdateViewProjention(input_, debugText_);

	// デバックカメラの更新
	debugCamera_->Update();

#pragma region スプライト
	// スプライトの今の座標を取得
	Vector2 position = sprite_->GetPosition();
	// 座標を{ 2.0, 1.0 }移動
	position.x += 2.0f;
	position.y += 1.0f;
	// 移動した座標をスプライトに反映
	sprite_->SetPosition(position);
#pragma endregion

#pragma region 音
	// スペースキーを押した瞬間
	//if (input_->TriggerKey(DIK_SPACE)) {
	//	// 音声停止
	//	audio_->StopWave(voiceHandle_);
	//}
#pragma endregion

#pragma region デバッグテキスト
	// デバッグテキストの表示
	// debugText_->Print("debug", 50.0f, 50.0f, 1.0f);
	// 書式指定付き表示
	// debugText_->SetPos(50.0f, 70.0f);
	// debugText_->Printf("year:%d", 2003);

	// 変数の値をインクリメント
	// value_++;
	// 値を含んだ文字列
	// std::string strDebug = std::string("Value:") +
		// std::to_string(value_);
	// デバッグテキストの表示
	// debugText_->Print(strDebug, 50.0f, 90.0f, 1.0f);
#pragma endregion
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	// 3Dモデル描画
	// 大元から順に描画していく
	for (int i = 0; i < kNumPartId; i++) {
		model_->Draw(worldTransforms_[i], viewProjection_, textureHandle_);
	}

	// ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	// PrimitiveDrawer::GetInstance()->DrawLine3d();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理

	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// sprite_->Draw();

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
