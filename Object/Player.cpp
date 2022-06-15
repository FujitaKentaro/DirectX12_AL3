#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// 親 大元
	worldTransform_[PartId::kRoot].Initialize();

	// 子 脊椎
	worldTransform_[PartId::kSpine].Initialize();
	worldTransform_[PartId::kSpine].translation_ = {0, 4.5f, 0};
	worldTransform_[PartId::kSpine].parent_ = &worldTransform_[PartId::kRoot];

	// 上半身
	// 胸
	worldTransform_[PartId::kChest].Initialize();
	worldTransform_[PartId::kChest].translation_ = {0, 0, 0};
	worldTransform_[PartId::kChest].parent_ = &worldTransform_[PartId::kSpine];
	// 頭
	worldTransform_[PartId::kHead].Initialize();
	worldTransform_[PartId::kHead].translation_ = {0, 4.5f, 0};
	worldTransform_[PartId::kHead].parent_ = &worldTransform_[PartId::kChest];
	// 左腕
	worldTransform_[PartId::kArmL].Initialize();
	worldTransform_[PartId::kArmL].translation_ = {-4.5f, 0, 0};
	worldTransform_[PartId::kArmL].parent_ = &worldTransform_[PartId::kChest];
	// 右腕
	worldTransform_[PartId::kArmR].Initialize();
	worldTransform_[PartId::kArmR].translation_ = {4.5f, 0, 0};
	worldTransform_[PartId::kArmR].parent_ = &worldTransform_[PartId::kChest];

	//下半身
	// 尻
	worldTransform_[PartId::kHip].Initialize();
	worldTransform_[PartId::kHip].translation_ = {0, -4.5f, 0};
	worldTransform_[PartId::kHip].parent_ = &worldTransform_[PartId::kSpine];
	// 左足
	worldTransform_[PartId::kLegL].Initialize();
	worldTransform_[PartId::kLegL].translation_ = {4.5f, -4.5f, 0};
	worldTransform_[PartId::kLegL].parent_ = &worldTransform_[PartId::kHip];

	// 右足
	worldTransform_[PartId::kLegR].Initialize();
	worldTransform_[PartId::kLegR].translation_ = {-4.5f, -4.5f, 0};
	worldTransform_[PartId::kLegR].parent_ = &worldTransform_[PartId::kHip];
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
		//回転
		{ //上半身
			if (input_->PushKey(DIK_U)) {
				worldTransform_[kChest].rotation_.y += 1;
			} else if (input_->PushKey(DIK_I)) {
				worldTransform_[kChest].rotation_.y += -1;
			}
			//下半身
			if (input_->PushKey(DIK_J)) {
				worldTransform_[kHip].rotation_.y += 1;
			} else if (input_->PushKey(DIK_K)) {
				worldTransform_[kHip].rotation_.y += -1;
			}
		}

		worldTransform_[0].translation_ += move;
		for (int i = 0; i < kNumPartId; i++) {
			PartUpdate(worldTransform_[i]);
		}
	}

#pragma endregion
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw(ViewProjection viewProjection) {
	for (int i = 0; i < kNumPartId; i++) {
		if (i < 2) {
			continue;
		}
		model_->Draw(worldTransform_[i], viewProjection, textureHandle_);
	}
}

void Player::PartUpdate(WorldTransform& worldTransform_) {

	// 子の更新
	
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