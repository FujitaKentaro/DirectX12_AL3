#include "Player.h"


void Player::Initialize(Model* model, uint32_t textureHandle) {
	//NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();


	   {
		// XYZの移動量を設定
		Vector3 move = {2, 2, 2};
		Vector3 rotatte = {45, 45, 45};
		Vector3 scale = {2, 2, 2};

		Matrix4 matWorld_= affin_.matUnit();

		matWorld_ = affin_.matWorld(move,rotatte,scale);

		worldTransform_.matWorld_ *= matWorld_;

		worldTransform_.TransferMatrix();
		}

}

/// <summary>
/// 更新
/// </summary>
void Player::Update(){


}

/// <summary>
/// 描画
/// </summary>
void Player::Draw(ViewProjection viewProjection){
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}

