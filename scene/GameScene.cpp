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

	// 範囲forで全てのワールドトランスフォームを順に処理する
	for (WorldTransform& worldTransform : worldTransforms_) {
		// ワールドトランスフォームの初期化
		worldTransform.Initialize();

		// X, Y, Z方向のスケーリングを設定
		worldTransform.scale_ = { 1.0f, 1.0f, 1.0f };
		// X, Y, Z軸周りの回転角を設定
		worldTransform.rotation_ = { distAngle(engine), distAngle(engine), distAngle(engine) };
		// X, Y, Z軸周りの平行移動を設定
		worldTransform.translation_ = { distPos(engine), distPos(engine), distPos(engine) };

		// WorldTransformの更新
		worldTransform.UpdateWorldTransform(worldTransform, mat);
	}

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
	for (WorldTransform& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, viewProjection_, textureHandle_);
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
