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
	delete modelBullet_;
	delete modelSkydome_;
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
	model_ = Model::CreateFromOBJ("object", true);
	modelBullet_ = Model::CreateFromOBJ("bullet", true);
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	// スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, { 100, 50 });

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 自キャラの生成
	player_ = std::make_unique<Player>();
	// 自キャラの初期化
	player_->Initialize(model_, modelBullet_, textureHandle_);

	// 敵キャラの生成
	enemy_ = std::make_unique<Enemy>();
	// 敵キャラの初期化
	enemy_->Initialize(model_, modelBullet_);
	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_.get());

	// 天球の生成
	skydome_ = std::make_unique<Skydome>();
	// 天球の初期化
	skydome_->Initialize(modelSkydome_);

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

#pragma region 軸
	//軸方向表示の表示を有効にする
	// AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	// AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

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

	if (clear_ == true) {
		debugText_->SetPos(600.0f, 50.0f);
		debugText_->Printf("clear");
	}
	

	// 自機、敵、弾の当たり判定
	CheckAllCollisions();

	// 自キャラの更新
	player_->Update();

	// 敵キャラの更新
	enemy_->Update();

	// 天球の更新
	skydome_->Update();

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

#pragma region デバッグカメラ

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_TAB)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif // _DEBUG

	// デバックカメラの更新
	{
		if (isDebugCameraActive_) {
			debugCamera_->Update();
			viewProjection_.matView = debugCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
			viewProjection_.TransferMatrix();
		}
		else {
			viewProjection_.UpdateMatrix();
			viewProjection_.TransferMatrix();
		}
	}
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
 
	// 天球の描画
	skydome_->Draw(viewProjection_);
	
	// 自キャラの描画
	player_->Draw(viewProjection_);

	// 敵キャラの描画
	if (enemy_->IsDead() == false) {
		enemy_->Draw(viewProjection_);
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

void GameScene::CheckAllCollisions() {
	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	// 自キャラの座標
	posA = player_->GetWorldPosition();

	// 自キャラと敵弾全ての当たり判定
	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {
		// 敵弾の座標
		posB = bullet->GetWorldPosition();

		// 座標A,B間の距離を求める
		float lenAB = pow(posB.x - posA.x, 2.0f) + pow(posB.y - posA.y, 2.0f) + pow(posB.z - posA.z, 2.0f);
		// 足した半径の2乗を求める
		float lenR = pow(bullet->GetRadius() + player_->GetRadius(), 2.0f);

		// 球と球の交差判定
		if (lenAB <= lenR) {
			// 自キャラの衝突時コールバック関数を呼び出す
			player_->OnCollision();
			// 敵弾の衝突時コールバック関数を呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	// 敵キャラの座標
	posA = enemy_->GetWorldPosition();

	// 敵キャラと自弾全ての当たり判定
	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
		// 敵弾の座標
		posB = bullet->GetWorldPosition();

		// 座標A,B間の距離を求める
		float lenAB = pow(posB.x - posA.x, 2.0f) + pow(posB.y - posA.y, 2.0f) + pow(posB.z - posA.z, 2.0f);
		// 足した半径の2乗を求める
		float lenR = pow(bullet->GetRadius() + enemy_->GetRadius(), 2.0f);

		// 球と球の交差判定
		if (lenAB <= lenR) {
			// 敵キャラの衝突時コールバック関数を呼び出す
			enemy_->OnCollision();
			// 自弾の衝突時コールバック関数を呼び出す
			bullet->OnCollision();

			// クリア
			clear_ = true;
		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	// 敵弾と自弾全ての当たり判定
	for (const std::unique_ptr<PlayerBullet>& pBullet : playerBullets) {
		// 自弾の座標
		posA = pBullet->GetWorldPosition();
		for (const std::unique_ptr<EnemyBullet>& eBullet : enemyBullets) {
			// 敵弾の座標
			posB = eBullet->GetWorldPosition();

			// 座標A,B間の距離を求める
			float lenAB = pow(posB.x - posA.x, 2.0f) + pow(posB.y - posA.y, 2.0f) + pow(posB.z - posA.z, 2.0f);
			// 足した半径の2乗を求める
			float lenR = pow(pBullet->GetRadius() + eBullet->GetRadius(), 2.0f);

			// 球と球の交差判定
			if (lenAB <= lenR) {
				// 自弾の衝突時コールバック関数を呼び出す
				pBullet->OnCollision();
				// 敵弾の衝突時コールバック関数を呼び出す
				eBullet->OnCollision();
			}
		}
	}
#pragma endregion
}