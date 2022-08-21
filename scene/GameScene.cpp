#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include "WinApp.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete sprite_;
	delete player_;
	delete enemy_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデルの生成
	model_ = Model::Create();

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.png");

	//スプライトの生成
	// sprite_ = Sprite::Create(textureHandle_, {100, 50});

	//サウンドデーターの読み込み
	soundDataHandle_ = audio_->LoadWave("fanfare.wav");
	//音声再生
	// voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);

	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initialize(model_, textureHandle_);

	//自キャラの生成
	enemy_ = new Enemy();
	//自キャラの初期化
	enemy_->Initialize(model_);
	enemy_->SetPlayer(player_);
}

void GameScene::Update() {

	// デバッグテキストの表示

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_P) && isDebugcameraActive_ == false) {
		isDebugcameraActive_ = true;
	} else if (input_->TriggerKey(DIK_P) && isDebugcameraActive_ == true) {
		isDebugcameraActive_ = false;
	}

#endif // _DEBUG

	// カメラの処理
	if (isDebugcameraActive_ == true) {
		//デバッグカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
		viewProjection_.TransferMatrix();
	}

	// 自キャラ更新
	player_->Update();
	enemy_->Update();
	CheckAllCollisions();
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
	// model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

	//自キャラ描画
	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);

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
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
/// <summary>
/// 衝突判定と応答
/// </summary>
void GameScene::CheckAllCollisions() {
	// 衝突判定ABの座標
	Vector3 posA, posB;

	// 自弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets_();

	// 敵弾リストを取得
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetBullets_();

#pragma region 自キャラと敵弾の当たり判定

	// 自キャラの座標
	posA = player_->GetWorldPosition();

	// 自キャラと敵弾すべての当たり判定
	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {
		//敵弾の座標
		posB = bullet.get()->GetWorldPosition();
		float a = std::pow(posB.x - posA.x, 2.0f) +
				  std::pow(posB.y - posA.y, 2.0f) +
		          std::pow(posB.z - posA.z, 2.0f);
		float lenR = std::pow(bullet.get()->r + player_->r, 2.0);
		// 球と球の交差判定
		if (a <= lenR) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			bullet.get()->OnCollision();
		}
	}

#pragma endregion

#pragma region 自弾と敵キャラの当たり判定

	posA = enemy_->GetWorldPosition();
	// 自球と敵すべての当たり判定
	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
		//自弾の座標
		posB = bullet.get()->GetWorldPosition();
		float a = std::pow(posB.x - posA.x, 2.0f) + std::pow(posB.y - posA.y, 2.0f) +
		          std::pow(posB.z - posA.z, 2.0f);
		float lenR = std::pow((bullet.get()->r + enemy_->r), 2.0);
		// 球と球の交差判定
		if (a <= lenR) {
			// キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();
			// 弾の衝突時コールバックを呼び出す
			bullet.get()->OnCollision();
		}
	}

#pragma endregion

#pragma region 自弾と敵弾の当たり判定

	for (const std::unique_ptr<PlayerBullet>& pBullet : playerBullets) {

		posA = pBullet.get()->GetWorldPosition();
		// 自球と敵弾すべての当たり判定
		for (const std::unique_ptr<EnemyBullet>& eBullet : enemyBullets) {
			//敵弾の座標
			posB = eBullet.get()->GetWorldPosition();
			float a = std::pow(posB.x - posA.x, 2.0f) + std::pow(posB.y - posA.y, 2.0f) +
			          std::pow(posB.z - posA.z, 2.0f);
			float lenR = std::pow((eBullet.get()->r + pBullet.get()->r), 2.0);
			// 球と球の交差判定
			if (a <= lenR) {
				// 自キャラの衝突時コールバックを呼び出す
				pBullet.get()->OnCollision();
				// 敵弾の衝突時コールバックを呼び出す
				eBullet.get()->OnCollision();
			}
		}
	}

#pragma endregion
}