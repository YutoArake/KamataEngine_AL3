#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include <cassert>

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

	// スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, { 100, 50 });

	// 3Dモデルの生成
	model_ = Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 960);

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	// ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	// サウンドデータの読み込み
	// soundDataHandle_ = audio_->LoadWave("mokugyo.wav");

	// 音声再生
	// audio_->PlayWave(soundDataHandle_);
	// voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
}

void GameScene::Update() {
	// デバックカメラの更新
	debugCamera_->Update();

	// スプライトの今の座標を取得
	Vector2 position = sprite_->GetPosition();
	// 座標を{ 2.0, 1.0 }移動
	position.x += 2.0f;
	position.y += 1.0f;
	// 移動した座標をスプライトに反映
	sprite_->SetPosition(position);

	// スペースキーを押した瞬間
	//if (input_->TriggerKey(DIK_SPACE)) {
	//	// 音声停止
	//	audio_->StopWave(voiceHandle_);
	//}

	// デバッグテキストの表示
	debugText_->Print("kaizokuou ni oreha naru", 50.0f, 50.0f, 1.0f);
	// 書式指定付き表示
	debugText_->SetPos(50.0f, 70.0f);
	debugText_->Printf("year:%d", 2003);

	// 変数の値をインクリメント
	value_++;
	// 値を含んだ文字列
	std::string strDebug = std::string("Value:") +
		std::to_string(value_);
	// デバッグテキストの表示
	debugText_->Print(strDebug, 50.0f, 90.0f, 1.0f);
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
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
	
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
	// debugText_->DrawAll(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
