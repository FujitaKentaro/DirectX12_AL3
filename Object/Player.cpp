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
	Move();
	Rotate();

	//行列更新
	MatUpdate(worldTransform_);

	//キャラ攻撃
	Attack();

	//弾更新
	for(std::unique_ptr<PlayerBullet>& bullet:bullets_) {
		bullet->Update();	
	}


	debugText_->SetPos(10, 10);
	debugText_->Printf(
	  "player : x,%f  y,%f z,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
	debugText_->SetPos(10, 30);
	debugText_->Printf(
	  "player : x,%f  y,%f z,%f", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	  worldTransform_.rotation_.z);

#pragma endregion
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//弾描画
	for(std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
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

/// <summary>
/// 動作
/// </summary>
void Player::Move() {
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// 平行移動
	{ // X方向
		if (input_->PushKey(DIK_D)) {
			move.x = 0.1;
		} else if (input_->PushKey(DIK_A)) {
			move.x = -0.1;
		}
		// Y方向
		if (input_->PushKey(DIK_W)) {
			move.y = 0.1;
		} else if (input_->PushKey(DIK_S)) {
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
}
/// <summary>
/// 回転移動
/// </summary>
void Player::Rotate() {
	Vector3 rotate = {0, 0, 0};

	// 回転
	{ // X方向
		if (input_->PushKey(DIK_Q)) {
			rotate.x = 1;
		} else if (input_->PushKey(DIK_E)) {
			rotate.x = -1;
		}
		// Y方向
		if (input_->PushKey(DIK_1)) {
			rotate.y = 1;
		} else if (input_->PushKey(DIK_2)) {
			rotate.y = -1;
		}
	}

	//移動限界座標
	const float kRotateLimitX = 80;
	const float kRotateLimitY = 80;

	//範囲を超えない処理
	worldTransform_.rotation_.x = max(worldTransform_.rotation_.x, -kRotateLimitX);
	worldTransform_.rotation_.x = min(worldTransform_.rotation_.x, +kRotateLimitX);
	worldTransform_.rotation_.y = max(worldTransform_.rotation_.y, -kRotateLimitY);
	worldTransform_.rotation_.y = min(worldTransform_.rotation_.y, +kRotateLimitY);

	worldTransform_.rotation_ += rotate;
}

/// <summary>
/// 攻撃
/// </summary>
void Player::Attack() {

	if (input_->TriggerKey(DIK_SPACE)) {

		// 弾を生成し、初期化
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_);

		// 弾を登録する
		bullets_.push_back(std::move(newBullet));
	}

}