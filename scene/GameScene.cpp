#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "WinApp.h"
#include "AxisIndicator.h"
#include <iostream>
#include <algorithm>

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
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);



	// 3Dモデルの生成
	model_ = Model::Create();	


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

	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

		//自キャラの生成	
		player_ = new Player();
		//自キャラの初期化
		player_->Initialize(model_, textureHandle_);	

}

void GameScene::Update() {


	// デバッグテキストの表示

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_P)&& isDebugcameraActive_ == false) {
		isDebugcameraActive_ = true;	
	}else if (input_->TriggerKey(DIK_P) && isDebugcameraActive_ == true) {
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
