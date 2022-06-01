#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "WinApp.h"

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete sprite_;
	delete player_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);



	// 3Dモデルの生成
	model_ = Model::Create();

	// X,Y,Z 方向のスケーリングを設定
	scale = { 5.0f, 5.0f, 5.0f };
	// X,Y,Z 軸回りの回転角を設定
	rotate = { XM_PI / 4.0f, XM_PI / 4.0f, 0.0f };
	// X,Y,Z 軸回りの平行移動を設定
	translation = { 10.0f, 10.0f, 10.0f };

	//ワールドトランスフォームの初期化
	//worldTransform_.Initialize();
	
	
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.png");

	//スプライトの生成
	//sprite_ = Sprite::Create(textureHandle_, {100, 50});

	//サウンドデーターの読み込み
	soundDataHandle_ = audio_->LoadWave("fanfare.wav");
	//音声再生
	//voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);

		//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initialize(model_, textureHandle_);

}

void GameScene::Update() {


	////デバッグテキストの表示
	//debugText_->SetPos(40, 50);
	//debugText_->Printf(
	//	"toranslation:(%f,%f,%f)\n", worldTransform_.scale_.x, worldTransform_.scale_.y,
	//	worldTransform_.scale_.z);
	//debugText_->SetPos(40, 70);
	//debugText_->Printf(
	//	"lotation:(%f,%f,%f)\n", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	//	worldTransform_.rotation_.z);
	//debugText_->SetPos(40, 90);
	//debugText_->Printf(
	//	"scale:(%f,%f,%f)\n", worldTransform_.translation_.x, worldTransform_.translation_.y,
	//	worldTransform_.translation_.z);

	//デバッグカメラの更新
	//debugCamera_->Update();

	//自キャラ更新
	player_->Update();

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
	//model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

	//自キャラ描画
	player_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//sprite_->Draw();

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
