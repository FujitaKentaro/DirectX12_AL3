#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "WinApp.h"
#include "AxisIndicator.h"

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete sprite_;
	for (int i = 0; i < 100; i++) {
		delete player_[i];
	}
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);



	// 3Dモデルの生成
	model_ = Model::Create();	

	//ワールドトランスフォームの初期化
	//worldTransform_.Initialize();
	
	// カメラ視点座標を設定
	//viewProjection_.eye = {0, 0, -10};
	// カメラ注視点座標を設定
	viewProjection_.target = {10, 0, 0};

	// カメラ上方向ベクトルを設定（右上４５度指定）
	viewProjection_.up = {cosf(Affin::PI / 4.0f), sinf(Affin::PI / 4.0f), 0};

	
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
	for (int i = 0; i < 100; i++) {
		player_[i] = new Player();
		//自キャラの初期化
		player_[i]->Initialize(model_, textureHandle_);
	
	}
	

}

void GameScene::Update() {


	//デバッグテキストの表示
	

	//デバッグカメラの更新
	//debugCamera_->Update();

#pragma region 視点移動処理

	{
		// 視点の移動ベクトル
		Vector3 move = MathUtility::Vector3Zero();

		// 視点の移動の速さ
		const float kEyeSpeed = 0.2f;

		// 押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_W)) {
			move.z += kEyeSpeed;
		} else if (input_->PushKey(DIK_S)) {
			move.z -= kEyeSpeed;
		}

		// 視点移動 (ベクトルの加算)
		viewProjection_.eye += move;

		// 行列の再計算
		viewProjection_.UpdateMatrix();

		// デバッグ用表示
		debugText_->SetPos(50, 50);
		debugText_->Printf(
		  "eye :%f,%f,%f", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);

	}

#pragma endregion

#pragma region 注視点移動処理

	{
		// 注視点の移動ベクトル
		Vector3 move = MathUtility::Vector3Zero();

		// 注視点の移動の速さ
		const float kEyeSpeed = 0.2f;

		// 押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_LEFT)) {
			move.z += kEyeSpeed;
		} else if (input_->PushKey(DIK_RIGHT)) {
			move.z -= kEyeSpeed;
		}

		// 注視点移動 (ベクトルの加算)
		viewProjection_.target += move;

		// 行列の再計算
		viewProjection_.UpdateMatrix();

		// デバッグ用表示
		debugText_->SetPos(50, 70);
		debugText_->Printf(
		  "eye :%f,%f,%f", viewProjection_.target.x, viewProjection_.target.y, viewProjection_.target.z);
	}

#pragma endregion

#pragma region 上方向回転処理

	{

		// 上方向の回転の速さ[ラジアン/frame]
		const float kUpRotSpeed = 0.05f;

		// 押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_SPACE)) {
			viewAngle += kUpRotSpeed;
			//2pi を超えたら0に戻す
			viewAngle = fmodf(viewAngle, Affin::PI * 2.0f);		
		}


		// 注視点移動 (ベクトルの加算)
		viewProjection_.up = {cosf(viewAngle), sinf(viewAngle),0.0f};

		// 行列の再計算
		viewProjection_.UpdateMatrix();

		// デバッグ用表示
		debugText_->SetPos(50, 90);
		debugText_->Printf(
		  "eye :%f,%f,%f", viewProjection_.up.x, viewProjection_.up.y,
		  viewProjection_.up.z);
	}

#pragma endregion
	//自キャラ更新
	for (int i = 0; i < 100; i++) {
		player_[i]->Update();
	}
	

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
	for (int i = 0; i < 100; i++) {
		player_[i]->Draw(viewProjection_);
	}


	

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
