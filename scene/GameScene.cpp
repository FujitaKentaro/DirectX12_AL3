#include "GameScene.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete debugCamera_;
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	// 3Dモデル
	model_ = Model::Create();
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	//ライン描画が参照するビュープロジェクションを指定する （アドレス渡し）
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.png");

	// 移動
	{
		for (int i = 0; i < 8; i++) { // 基準点を移動
			boxTrans[i].x = translation[0].x * box[i].x + translation[0].y * box[i].y +
			                translation[0].z * box[i].z + translation[0].w * 1;
			boxTrans[i].y = translation[1].x * box[i].x + translation[1].y * box[i].y +
			                translation[1].z * box[i].z + translation[1].w * 1;
			boxTrans[i].z = translation[2].x * box[i].x + translation[2].y * box[i].y +
			                translation[2].z * box[i].z + translation[2].w * 1;
		}
	}

	// 回転 (個々)
	{
		for (int i = 0; i < 8; i++) { // 回転 X
			rotateX1[i].x = rotateX[0].x * box[i].x + rotateX[0].y * box[i].y +
			                rotateX[0].z * box[i].z + rotateX[0].w * 1;
			rotateX1[i].y = rotateX[1].x * box[i].x + rotateX[1].y * box[i].y +
			                rotateX[1].z * box[i].z + rotateX[1].w * 1;
			rotateX1[i].z =
			  rotateX[2].x * box[i].x + rotateX[2].y * box[i].y + rotateX[2].z * box[i].z;
		}

		for (int i = 0; i < 8; i++) { // 回転 Y
			rotateY1[i].x = rotateY[0].x * box[i].x + rotateY[0].y * box[i].y +
			                rotateY[0].z * box[i].z + rotateY[0].w * 1;
			rotateY1[i].y = rotateY[1].x * box[i].x + rotateY[1].y * box[i].y +
			                rotateY[1].z * box[i].z + rotateY[1].w * 1;
			rotateY1[i].z =
			  rotateY[2].x * box[i].x + rotateY[2].y * box[i].y + rotateY[2].z * box[i].z;
		}

		for (int i = 0; i < 8; i++) { // 回転 Z
			rotateZ1[i].x = rotateZ[0].x * box[i].x + rotateZ[0].y * box[i].y +
			                rotateZ[0].z * box[i].z + rotateZ[0].w * 1;
			rotateZ1[i].y = rotateZ[1].x * box[i].x + rotateZ[1].y * box[i].y +
			                rotateZ[1].z * box[i].z + rotateZ[1].w * 1;
			rotateZ1[i].z =
			  rotateZ[2].x * box[i].x + rotateZ[2].y * box[i].y + rotateZ[2].z * box[i].z;
		}
	}

	// 回転 (Z-X-Y)
	{
		for (int i = 0; i < 8; i++) { // 回転 Z
			rotateZ2[i].x = rotateZ[0].x * box[i].x + rotateZ[0].y * box[i].y +
			                rotateZ[0].z * box[i].z + rotateZ[0].w * 1;
			rotateZ2[i].y = rotateZ[1].x * box[i].x + rotateZ[1].y * box[i].y +
			                rotateZ[1].z * box[i].z + rotateZ[1].w * 1;
			rotateZ2[i].z = rotateZ[2].x * box[i].x + rotateZ[2].y * box[i].y + 
				rotateZ[2].z * box[i].z;
		}

		for (int i = 0; i < 8; i++) { // 回転 X
			rotateX2[i].x = rotateX[0].x * rotateZ2[i].x + rotateX[0].y * rotateZ2[i].y +
			                rotateX[0].z * rotateZ2[i].z + rotateX[0].w * 1;
			rotateX2[i].y = rotateX[1].x * rotateZ2[i].x + rotateX[1].y * rotateZ2[i].y +
			                rotateX[1].z * rotateZ2[i].z + rotateX[1].w * 1;
			rotateX2[i].z = rotateX[2].x * rotateZ2[i].x + rotateX[2].y * rotateZ2[i].y +
			                rotateX[2].z * rotateZ2[i].z;
		}

		for (int i = 0; i < 8; i++) { // 回転 Y
			boxRotate[i].x = rotateY[0].x * rotateX2[i].x + rotateY[0].y * rotateX2[i].y +
			                rotateY[0].z * rotateX2[i].z + rotateY[0].w * 1;
			boxRotate[i].y = rotateY[1].x * rotateX2[i].x + rotateY[1].y * rotateX2[i].y +
			                rotateY[1].z * rotateX2[i].z + rotateY[1].w * 1;
			boxRotate[i].z = rotateY[2].x * rotateX2[i].x + rotateY[2].y * rotateX2[i].y +
			                rotateY[2].z * rotateX2[i].z;
		}
	}
	// 拡大
	{
		for (int i = 0; i < 8; i++) { // 基準点を拡大
			boxScale[i].x = scale[0].x * box[i].x + scale[0].y * box[i].y + scale[0].z * box[i].z +
			                scale[0].w * 1;
			boxScale[i].y = scale[1].x * box[i].x + scale[1].y * box[i].y + scale[1].z * box[i].z +
			                scale[1].w * 1;
			boxScale[i].z = scale[2].x * box[i].x + scale[2].y * box[i].y + scale[2].z * box[i].z +
			                scale[2].w * 1;
		}
	}
}

void GameScene::Update() { debugCamera_->Update(); }

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
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

	for (int i = 0; i < 12; i++) { //ワイヤーフレームボックス描画
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  box[edgeList[i][0]], box[edgeList[i][1]], coloer[WHITE]);
	}
	for (int i = 0; i < 12; i++) { // 拡大
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  boxScale[edgeList[i][0]], boxScale[edgeList[i][1]], coloer[GREEN]);
	}
	for (int i = 0; i < 12; i++) { // 回転
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  boxRotate[edgeList[i][0]], boxRotate[edgeList[i][1]], coloer[BLUE]);
	}
	for (int i = 0; i < 12; i++) { // 移動
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  boxTrans[edgeList[i][0]], boxTrans[edgeList[i][1]], coloer[RED]);
	}
	{
		//for (int i = 0; i < 12; i++) { // 回転
		//	PrimitiveDrawer::GetInstance()->DrawLine3d(
		//	  rotateX1[edgeList[i][0]], rotateX1[edgeList[i][1]], coloer[MAGENTA]);
		//}
		//for (int i = 0; i < 12; i++) { // 回転
		//	PrimitiveDrawer::GetInstance()->DrawLine3d(
		//	  rotateY1[edgeList[i][0]], rotateY1[edgeList[i][1]], coloer[YELLOW]);
		//}
		//for (int i = 0; i < 12; i++) { // 回転
		//	PrimitiveDrawer::GetInstance()->DrawLine3d(
		//	  rotateZ1[edgeList[i][0]], rotateZ1[edgeList[i][1]], coloer[CYAN]);
		//}
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

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
