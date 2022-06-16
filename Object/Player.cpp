#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
}

/// <summary>
/// 更新
/// </summary>
void Player::Update() {
#pragma region キャラクター移動処理

	// キャラクター移動処理
	{
		//キャラクターの移動ベクトル
		Vector3 move = {0, 0, 0};
	
		// 平行移動
		{ // X方向
			if (input_->PushKey(DIK_RIGHT)) {
				move.x = 0.1;
			} else if (input_->PushKey(DIK_LEFT)) {
				move.x = -0.1;
			}
			// Y方向
			if (input_->PushKey(DIK_UP)) {
				move.y = 0.1;
			} else if (input_->PushKey(DIK_DOWN)) {
				move.y = -0.1;
			}
		}

		//移動限界座標
		const float kMoveLimitX = 35;
		const float kMoveLimitY = 19;

		//範囲を超えない処理
		worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
		worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
		worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
		worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

		worldTransform_.translation_ += move;
		//行列更新
		MatUpdate(worldTransform_);

		debugText_->SetPos(10,10);
		    debugText_->Printf(
		      "player : x,%f  y,%f z,%f", worldTransform_.translation_.x,
		      worldTransform_.translation_.y, worldTransform_.translation_.z);
	}

#pragma endregion
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw(ViewProjection viewProjection) {
	
		model_->Draw(worldTransform_, viewProjection, textureHandle_);
	
}

void Player::MatUpdate(WorldTransform& worldTransform_) {

	// パーツの更新
	
	// ３移動合成行列を計算
	worldTransform_.matWorld_ = Affin::matWorld(
	  worldTransform_.translation_, worldTransform_.rotation_, worldTransform_.scale_);
	
	// 親の行列を掛け算代入
	if (worldTransform_.parent_ != nullptr) {
		worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	}
	
	// 行列の転送
	worldTransform_.TransferMatrix();
}